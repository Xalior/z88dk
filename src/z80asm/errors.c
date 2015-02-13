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

Error handling.

$Header: /home/dom/z88dk-git/cvs/z88dk/src/z80asm/errors.c,v 1.56 2015-02-13 00:05:13 pauloscustodio Exp $
*/

#include "errors.h"
#include "fileutil.h"
#include "options.h"
#include "srcfile.h"
#include "strpool.h"
#include "strutil.h"
#include "strhash.h"
#include "types.h"
#include "init.h"
#include <stdio.h>
#include <sys/stat.h>

static void file_error( char *filename, Bool writing );

/*-----------------------------------------------------------------------------
*   Singleton data
*----------------------------------------------------------------------------*/
typedef struct Errors
{
    int			 count;				/* total errors */
    char		*filename;			/* location of error: name of source file */
    char		*module;			/* location of error: name of module */
    int			 line;				/* location of error: line number */
} Errors;

static Errors errors;				/* count errors and locations */


typedef struct ErrorFile
{
    FILE		*file;				/* currently open error file */
    char		*filename;			/* name of error file */
} ErrorFile;

static ErrorFile error_file;		/* currently open error file */

/*-----------------------------------------------------------------------------
*   Initialize and Terminate module
*----------------------------------------------------------------------------*/
DEFINE_init_module()
{
	strpool_init();					/* make sure strpool is removed last */

    /* init Errors */
    reset_error_count();			/* clear error count */
    set_error_null();               /* clear location of error messages */

	/* init file error handling */
	set_ferr_callback( file_error );
	set_incl_recursion_err_cb( error_include_recursion );
}

DEFINE_dtor_module()
{
    /* close error file, delete it if no errors */
    close_error_file();
}

void errors_init( void ) 
{
	init_module();
}

/*-----------------------------------------------------------------------------
*	define the next FILE, LINENO, MODULE to use in error messages
*	error_xxx(), fatal_xxx(), warn_xxx()
*----------------------------------------------------------------------------*/
void set_error_null( void )
{
    init_module();
    errors.filename = errors.module = NULL;
    errors.line = 0;
}

void set_error_file( char *filename )
{
    init_module();
    errors.filename = strpool_add( filename );	/* may be NULL */
}

void set_error_module( char *modulename )
{
    init_module();
    errors.module = strpool_add( modulename );	/* may be NULL */
}

void set_error_line( int lineno )
{
    init_module();
    errors.line = lineno;
}

char *get_error_file(void)
{
	init_module();
	return errors.filename;
}

int get_error_line(void)
{
	init_module();
	return errors.line;
}

/*-----------------------------------------------------------------------------
*	reset count of errors and return current count
*----------------------------------------------------------------------------*/
void reset_error_count( void )
{
    init_module();
    errors.count = 0;
}

int get_num_errors( void )
{
    init_module();
    return errors.count;
}

/*-----------------------------------------------------------------------------
*	Open file to receive all errors / warnings from now on
*	File is appended, to allow assemble	and link errors to be joined in the same file.
*----------------------------------------------------------------------------*/
void open_error_file( char *src_filename )
{
	char *filename = get_err_filename( src_filename );

    init_module();

    /* close current file if any */
    close_error_file();

    error_file.filename = strpool_add( filename );
	error_file.file = myfopen(error_file.filename, "a");
}

void close_error_file( void )
{
	struct stat st;
	int stat_res;

    init_module();

    /* close current file if any */
	if (error_file.file != NULL)
	{
		myfclose(error_file.file);

		/* delete file if no errors found */
		if (error_file.filename != NULL)
		{
			stat_res = stat(error_file.filename, &st);
			if (stat_res == 0 && st.st_size == 0)
				remove(error_file.filename);
		}
	}

    /* reset */
    error_file.file		= NULL;
    error_file.filename	= NULL;        /* filename kept in strpool, no leak */
}

static void puts_error_file( char *string )
{
    init_module();

    if ( error_file.file != NULL )
        fputs( string, error_file.file );
}

/*-----------------------------------------------------------------------------
*   Output error message
*----------------------------------------------------------------------------*/
static void do_error( enum ErrType err_type, char *message )
{
    DEFINE_STR( msg, MAXLINE );
    size_t len_at, len_prefix;

    init_module();

    /* init empty message */
    Str_clear( msg );

    /* Information messages have no prefix */
    if ( err_type != ErrInfo )
    {
        Str_append( msg, err_type == ErrWarn ? "Warning" : "Error" );

        /* prepare to remove " at" if no prefix */
        len_at = msg->len;
        Str_append( msg, " at" );
        len_prefix = msg->len;

        /* output filename */
        if ( errors.filename && *errors.filename )
            Str_append_sprintf( msg, " file '%s'", errors.filename );

        /* output module */
        if ( errors.module != NULL && *errors.module )
            Str_append_sprintf( msg, " module '%s'", errors.module );

        /* output line number */
        if ( errors.line > 0 )
            Str_append_sprintf( msg, " line %d", errors.line );

        /* remove at if no prefix */
        if ( len_prefix == msg->len )	/* no prefix loaded to string */
        {
            msg->str[ len_at ] = '\0';	/* go back 3 chars to before at */
            Str_sync_len( msg );
        }

        Str_append( msg, ": " );
    }

    /* output error message */
    Str_append( msg, message );
    Str_append_char( msg, '\n' );

    /* CH_0001 : Assembly error messages should appear on stderr */
    fputs( msg->str, stderr );

    /* send to error file */
    puts_error_file( msg->str );

    if ( err_type == ErrError )
        errors.count++;		/* count number of errors */
}

/*-----------------------------------------------------------------------------
*   define error functions
*----------------------------------------------------------------------------*/
#define ERR(err_type,func,args)	\
	void func \
	{ \
		DEFINE_STR( msg, MAXLINE ); \
		\
		init_module(); \
		Str_append_sprintf( msg, args ); \
		do_error( err_type, msg->str ); \
	}
#include "errors_def.h"
#undef ERR

/*-----------------------------------------------------------------------------
*   file error handling
*----------------------------------------------------------------------------*/
static void file_error( char *filename, Bool writing )
{
	init_module();
	
	if ( writing )
		error_write_file( filename );
	else
		error_read_file( filename );
}
