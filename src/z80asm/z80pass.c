/*
     ZZZZZZZZZZZZZZZZZZZZ    8888888888888       00000000000
   ZZZZZZZZZZZZZZZZZZZZ    88888888888888888    0000000000000
                ZZZZZ      888           888  0000         0000
              ZZZZZ        88888888888888888  0000         0000
            ZZZZZ            8888888888888    0000         0000       AAAAAA         SSSSSSSSSSS   MMMM       MMMM
          ZZZZZ            88888888888888888  0000         0000      AAAAAAAA      SSSS            MMMMMM   MMMMMM
        ZZZZZ              8888         8888  0000         0000     AAAA  AAAA     SSSSSSSSSSS     MMMMMMMMMMMMMMM
      ZZZZZ                8888         8888  0000         0000    AAAAAAAAAAAA      SSSSSSSSSSS   MMMM MMMMM MMMM
    ZZZZZZZZZZZZZZZZZZZZZ  88888888888888888    0000000000000     AAAA      AAAA           SSSSS   MMMM       MMMM
  ZZZZZZZZZZZZZZZZZZZZZ      8888888888888       00000000000     AAAA        AAAA  SSSSSSSSSSS     MMMM       MMMM

Copyright (C) Gunther Strube, InterLogic 1993-99
Copyright (C) Paulo Custodio, 2011-2015

$Header: /home/dom/z88dk-git/cvs/z88dk/src/z80asm/z80pass.c,v 1.137 2015-02-13 00:05:18 pauloscustodio Exp $
*/

#include "directives.h"
#include "codearea.h"
#include "errors.h"
#include "expr.h"
#include "fileutil.h"
#include "hist.h"
#include "listfile.h"
#include "model.h"
#include "modlink.h"
#include "options.h"
#include "parse.h"
#include "scan.h"
#include "srcfile.h"
#include "strutil.h"
#include "sym.h"
#include "symbol.h"
#include "z80asm.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* external functions */

/* local functions */
void Z80pass2( void );
void WriteSymbolTable( char *msg, SymbolHash *symtab );

void
Z80pass2( void )
{
	ExprListElem *iter;
    Expr *expr, *expr2;
    long value;
	Bool do_patch, do_store;

	/* compute all dependent expressions */
	compute_equ_exprs( CURRENTMODULE->exprs, FALSE, TRUE );

	iter = ExprList_first( CURRENTMODULE->exprs );
	while ( iter != NULL )
	{
		expr = iter->obj;

        /* set error location */
		set_error_null();
        set_error_file( expr->filename );
        set_error_line( expr->line_nr );

		/* Define code location; BUG_0048 */
		set_cur_section( expr->section );
		set_PC( expr->asmpc );		

		/* try to evaluate expression to detect missing symbols */
		value = Expr_eval( expr );

		/* check if expression is stored in object file or computed and patched */
		do_patch = TRUE;
		do_store = FALSE;

		if ( expr->result.undefined_symbol ) 
		{
			error_not_defined();
			do_patch = FALSE;
		}
		else if ( expr->range == RANGE_JR_OFFSET )
		{
			if ( expr->result.extern_symbol )
			{
				error_jr_not_local();	/* JR must be local */
				do_patch = FALSE;
			}
		}
		else if ( ( (expr->sym_type >= TYPE_ADDRESS) || expr->result.extern_symbol ) )
		{
			do_patch = FALSE;
			do_store = TRUE;            /* store expression in relocatable file */
		}
		else if ( expr->result.not_evaluable )
		{
			error_not_defined();
			do_patch = FALSE;
		}

        if ( do_patch )
        {
            switch ( expr->range )
            {
            case RANGE_JR_OFFSET:
                value -= get_PC() + 2;		/* get module PC at JR instruction */

                if ( value >= -128 && value <= 127 )
                {
					patch_byte(expr->code_pos, (Byte)value);
                    /* opcode is stored, now store relative jump */
                }
                else
                {
                    error_int_range( value );
                }
                break;

			case RANGE_BYTE_UNSIGNED:
                if ( value < -128 || value > 255 )
                    warn_int_range( value );

				patch_byte(expr->code_pos, (Byte)value);
                break;

            case RANGE_BYTE_SIGNED:
                if ( value < -128 || value > 127 )
                    warn_int_range( value );

				patch_byte(expr->code_pos, (Byte)value);
                break;

            case RANGE_WORD:
                if ( value < -32768 || value > 65535 )
                    warn_int_range( value );

				patch_word(expr->code_pos, (int)value);
                break;

            case RANGE_DWORD:
                if ( value < LONG_MIN || value > LONG_MAX )
                    warn_int_range( value );

				patch_long(expr->code_pos, value);
                break;

			default:
				assert(0);
            }
        }

		if ( opts.list )
			list_patch_data( expr->listpos, value, range_size( expr->range ) );
			
		/* continue loop - delete expression unless needs to be stored in object file */
		if ( do_store )
			iter = ExprList_next( iter );
		else
		{
			/* remove current expression, advance iterator */
			expr2 = ExprList_remove( CURRENTMODULE->exprs, &iter );
			assert( expr == expr2 );

			OBJ_DELETE( expr );	
		}
    }

    /* clean error location */
    set_error_null();
    //set_error_module( CURRENTMODULE->modname );

	/* create object file */
	if ( ! get_num_errors() )
		write_obj_file( CURRENTMODULE->filename );

    if ( ! get_num_errors() && opts.symtable )
    {
        WriteSymbolTable( "Local Module Symbols:", CURRENTMODULE->local_symtab );
        WriteSymbolTable( "Global Module Symbols:", global_symtab );
    }
}


Bool Pass2infoExpr(range_t range, Expr *expr)
{
	int list_offset;

	if (expr != NULL)
	{
		expr->range = range;
		expr->code_pos = get_cur_module_size();			/* update expression location */
		list_offset = expr->code_pos - get_PC();

		if (opts.cur_list)
			expr->listpos = list_patch_pos(list_offset);	/* now calculated as absolute file pointer */
		else
			expr->listpos = -1;

		ExprList_push(&CURRENTMODULE->exprs, expr);
	}

	/* reserve space */
	append_defs(range_size(range), 0);

	return expr == NULL ? FALSE : TRUE;
}

Bool Pass2info(range_t range)
{
	Expr *expr;
	
	/* Offset of (ix+d) should be optional; '+' or '-' are necessary */
	if (range == RANGE_BYTE_SIGNED)
	{
		switch (sym.tok)
		{
		case TK_RPAREN:
			append_byte(0);		/* offset zero */
			return TRUE;		/* OK, zero already stored */

		case TK_PLUS:
		case TK_MINUS:          /* + or - expected */
			break;				/* proceed to evaluate expression */

		default:                /* Syntax error, e.g. (ix 4) */
			error_syntax();
			return FALSE;		/* FAIL */
		}

	}

	expr = expr_parse();

	if (range == RANGE_BYTE_SIGNED && sym.tok != TK_RPAREN)
	{
		error_syntax();
		return FALSE;		/* FAIL */
	}

	return Pass2infoExpr(range, expr);
}


void
WriteSymbolTable( char *msg, SymbolHash *symtab )
{
    SymbolHashElem *iter;
    Symbol         *sym;

    /* dump all symbols sorted by name */
    list_start_table( msg );

    SymbolHash_sort( symtab, SymbolHash_by_name );

    for ( iter = SymbolHash_first( symtab ); iter; iter = SymbolHash_next( iter ) )
    {
        sym = ( Symbol * )iter->value;

        if ( sym->module == CURRENTMODULE )
        {
            /* Write only symbols related to current module */
            if ( ( sym->sym_type_mask & SYM_LOCAL ) || ( sym->sym_type_mask & SYM_PUBLIC ) )
            {
                if ( ( sym->sym_type_mask & SYM_TOUCHED ) )
                {
                    list_symbol( sym->name, sym->value, sym->references );
                }
            }
        }

    }
}
