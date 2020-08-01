// cpp/options.yy.cpp generated by reflex 2.0.1 from cpp/options.l

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_dotall              true
#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "cpp/options.yy.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               OptionsLexer
#define REFLEX_OPTION_noline              true
#define REFLEX_OPTION_outfile             "cpp/options.yy.cpp"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


	// silence warnings from RE-flex
	#ifdef _MSC_VER
	#pragma warning(disable:4102)
	#pragma warning(disable:4800)
	#else
	#ifdef __GNUC__
	//#pragma GCC   diagnostic ignored "-Wignored-qualifiers"
	#else
	#ifdef __clang__
	//#pragma clang diagnostic ignored "-Wignored-qualifiers"
	#endif
	#endif
	#endif

	#include "Arch.h"
	#include "Cpu.h"
	#include "Options.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  ABSTRACT LEXER CLASS                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/abslexer.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class OptionsLexer : public reflex::AbstractLexer<reflex::Matcher> {
 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  OptionsLexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  virtual int lex();
  int lex(
      const reflex::Input& input,
      std::ostream        *os = NULL)
  {
    in(input);
    if (os)
      out(*os);
    return lex();
  }
};

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// z80asm restart
// Copyright (C) Paulo Custodio, 2011-2020
// License: The Artistic License 2.0, http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

extern void reflex_code_INITIAL(reflex::Matcher&);

int OptionsLexer::lex()
{
  static const reflex::Pattern PATTERN_INITIAL(reflex_code_INITIAL);
  if (!has_matcher())
  {
    matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
  }
  while (true)
  {
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
              return int();
            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 34: -v\z|--verbose\z :
{ theOptions.verbose = true; return true; }

            break;
          case 2: // rule at line 38: -\?\z|-h\z|--help\z :
{ ExitManual(); }

            break;
          case 3: // rule at line 41: -m=?z80\z|--cpu=?z80\z :
{ theCpu.Init(Cpu::Type::Z80); return true; }

            break;
          case 4: // rule at line 44: -m=?z80n\z|--cpu=?z80n\z :
{ theCpu.Init(Cpu::Type::Z80N); return true; }

            break;
          case 5: // rule at line 47: -m=?z180\z|--cpu=?z180\z :
{ theCpu.Init(Cpu::Type::Z180); return true; }

            break;
          case 6: // rule at line 50: -m=?r2k\z|--cpu=?r2k\z :
{ theCpu.Init(Cpu::Type::R2K); return true; }

            break;
          case 7: // rule at line 53: -m=?r3k\z|--cpu=?r3k\z :
{ theCpu.Init(Cpu::Type::R3K); return true; }

            break;
          case 8: // rule at line 56: -m=?8080\z|--cpu=?8080\z :
{ theCpu.Init(Cpu::Type::I8080); return true; }

            break;
          case 9: // rule at line 59: -m=?8085\z|--cpu=?8085\z :
{ theCpu.Init(Cpu::Type::I8085); return true; }

            break;
          case 10: // rule at line 62: -m=?gbz80\z|--cpu=?gbz80\z :
{ theCpu.Init(Cpu::Type::GBZ80); return true; }

            break;
          case 11: // rule at line 65: -m=?ti83\z|--cpu=?ti83\z :
{	theCpu.Init(Cpu::Type::Z80);
					theArch.Init(Arch::Type::TI83);
					return true; }

            break;
          case 12: // rule at line 70: -m=?ti83plus\z|--cpu=?ti83plus\z :
{
					theCpu.Init(Cpu::Type::Z80);
					theArch.Init(Arch::Type::TI83PLUS);
					return true; }

            break;
          case 13: // rule at line 76: -IXIY\z|--IXIY\z :
{ theOptions.swapIxIy = true; return true; }

            break;
          case 14: // rule at line 78: --opt=speed\z :
{ theOptions.optimizeSpeed = true; return true; }

            break;
          case 15: // rule at line 80: --debug\z :
{	theOptions.debugInfo = true;
					theOptions.doMapFile = true;
					return true; }

            break;
          case 16: // rule at line 84: -m\z :
          case 17: // rule at line 85: --map\z :
{ theOptions.doMapFile = true; return true; }

            break;
          case 18: // rule at line 87: -I=[\x00-\xff]+ :
{ theOptions.includePath.push_back(text() + 3);  return true; }
            break;
          case 19: // rule at line 88: -I[\x00-\xff]+ :
{ theOptions.includePath.push_back(text() + 2);  return true; }
            break;
          case 20: // rule at line 89: --inc-path=[\x00-\xff]+ :
{ theOptions.includePath.push_back(text() + 11); return true; }
            break;
          case 21: // rule at line 90: --inc-path[\x00-\xff]+ :
{ theOptions.includePath.push_back(text() + 10); return true; }

            break;
          case 22: // rule at line 92: -L=[\x00-\xff]+ :
{ theOptions.libraryPath.push_back(text() + 3);  return true; }
            break;
          case 23: // rule at line 93: -L[\x00-\xff]+ :
{ theOptions.libraryPath.push_back(text() + 2);  return true; }
            break;
          case 24: // rule at line 94: --lib-path=[\x00-\xff]+ :
{ theOptions.libraryPath.push_back(text() + 11); return true; }
            break;
          case 25: // rule at line 95: --lib-path[\x00-\xff]+ :
{ theOptions.libraryPath.push_back(text() + 10); return true; }

            break;
          case 26: // rule at line 97: -D=(?:[A-Z_a-z][0-9A-Z_a-z]*)\z :
{ theOptions.defines.push_back({ text() + 3, 1}); return true; }
            break;
          case 27: // rule at line 98: -D(?:[A-Z_a-z][0-9A-Z_a-z]*)\z :
{ theOptions.defines.push_back({ text() + 2, 1}); return true; }
            break;
          case 28: // rule at line 99: --define=(?:[A-Z_a-z][0-9A-Z_a-z]*)\z :
{ theOptions.defines.push_back({ text() + 9, 1}); return true; }
            break;
          case 29: // rule at line 100: --define(?:[A-Z_a-z][0-9A-Z_a-z]*)\z :
{ theOptions.defines.push_back({ text() + 8, 1}); return true; }

            break;
          case 30: // rule at line 102: [\x00-\xff] :
{ return false; }

            break;
        }
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  TABLES                                                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

#if defined(OS_WIN)
#pragma warning(disable:4101 4102)
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-label"
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-label"
#endif

void reflex_code_INITIAL(reflex::Matcher& m)
{
  int c0 = 0, c1 = 0;
  m.FSM_INIT(c1);

S0:
  m.FSM_FIND();
  c1 = m.FSM_CHAR();
  if (c1 == '-') goto S2;
  if (0 <= c1) goto S12;
  return m.FSM_HALT(c1);

S2:
  m.FSM_TAKE(30);
  c1 = m.FSM_CHAR();
  if (c1 == 'v') goto S14;
  if (c1 == 'm') goto S30;
  if (c1 == 'h') goto S28;
  if (c1 == 'L') goto S41;
  if (c1 == 'I') goto S38;
  if (c1 == 'D') goto S43;
  if (c1 == '?') goto S26;
  if (c1 == '-') goto S16;
  return m.FSM_HALT(c1);

S12:
  m.FSM_TAKE(30);
  return m.FSM_HALT();

S14:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(1, c1);
  }
  return m.FSM_HALT(c1);

S16:
  c1 = m.FSM_CHAR();
  if (c1 == 'v') goto S50;
  if (c1 == 'o') goto S58;
  if (c1 == 'm') goto S62;
  if (c1 == 'l') goto S66;
  if (c1 == 'i') goto S64;
  if (c1 == 'h') goto S52;
  if (c1 == 'd') goto S60;
  if (c1 == 'c') goto S54;
  if (c1 == 'I') goto S56;
  return m.FSM_HALT(c1);

S26:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(2, c1);
  }
  return m.FSM_HALT(c1);

S28:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(2, c1);
  }
  return m.FSM_HALT(c1);

S30:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(16, c1);
  }
  if (c1 == 'z') goto S70;
  if (c1 == 't') goto S80;
  if (c1 == 'r') goto S73;
  if (c1 == 'g') goto S78;
  if (c1 == '=') goto S84;
  if (c1 == '8') goto S76;
  return m.FSM_HALT(c1);

S38:
  c1 = m.FSM_CHAR();
  if (c1 == 'X') goto S90;
  if (c1 == '=') goto S93;
  if (0 <= c1) goto S95;
  return m.FSM_HALT(c1);

S41:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S97;
  if (0 <= c1) goto S99;
  return m.FSM_HALT(c1);

S43:
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S105;
  if (c1 == '_') goto S105;
  if ('A' <= c1 && c1 <= 'Z') goto S105;
  if (c1 == '=') goto S101;
  return m.FSM_HALT(c1);

S48:
  m.FSM_TAKE(1);
  return m.FSM_HALT();

S50:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S111;
  return m.FSM_HALT(c1);

S52:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S113;
  return m.FSM_HALT(c1);

S54:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S115;
  return m.FSM_HALT(c1);

S56:
  c1 = m.FSM_CHAR();
  if (c1 == 'X') goto S117;
  return m.FSM_HALT(c1);

S58:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S119;
  return m.FSM_HALT(c1);

S60:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S121;
  return m.FSM_HALT(c1);

S62:
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S124;
  return m.FSM_HALT(c1);

S64:
  c1 = m.FSM_CHAR();
  if (c1 == 'n') goto S126;
  return m.FSM_HALT(c1);

S66:
  c1 = m.FSM_CHAR();
  if (c1 == 'i') goto S128;
  return m.FSM_HALT(c1);

S68:
  m.FSM_TAKE(2);
  return m.FSM_HALT();

S70:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S130;
  if (c1 == '1') goto S132;
  return m.FSM_HALT(c1);

S73:
  c1 = m.FSM_CHAR();
  if (c1 == '3') goto S136;
  if (c1 == '2') goto S134;
  return m.FSM_HALT(c1);

S76:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S138;
  return m.FSM_HALT(c1);

S78:
  c1 = m.FSM_CHAR();
  if (c1 == 'b') goto S140;
  return m.FSM_HALT(c1);

S80:
  c1 = m.FSM_CHAR();
  if (c1 == 'i') goto S142;
  return m.FSM_HALT(c1);

S82:
  m.FSM_TAKE(16);
  return m.FSM_HALT();

S84:
  c1 = m.FSM_CHAR();
  if (c1 == 'z') goto S70;
  if (c1 == 't') goto S80;
  if (c1 == 'r') goto S73;
  if (c1 == 'g') goto S78;
  if (c1 == '8') goto S76;
  return m.FSM_HALT(c1);

S90:
  m.FSM_TAKE(19);
  c1 = m.FSM_CHAR();
  if (c1 == 'I') goto S144;
  if (0 <= c1) goto S95;
  return m.FSM_HALT(c1);

S93:
  m.FSM_TAKE(19);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S147;
  return m.FSM_HALT(c1);

S95:
  m.FSM_TAKE(19);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S95;
  return m.FSM_HALT(c1);

S97:
  m.FSM_TAKE(23);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S149;
  return m.FSM_HALT(c1);

S99:
  m.FSM_TAKE(23);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S99;
  return m.FSM_HALT(c1);

S101:
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S151;
  if (c1 == '_') goto S151;
  if ('A' <= c1 && c1 <= 'Z') goto S151;
  return m.FSM_HALT(c1);

S105:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(27, c1);
  }
  if ('a' <= c1 && c1 <= 'z') goto S105;
  if (c1 == '_') goto S105;
  if ('A' <= c1 && c1 <= 'Z') goto S105;
  if ('0' <= c1 && c1 <= '9') goto S105;
  return m.FSM_HALT(c1);

S111:
  c1 = m.FSM_CHAR();
  if (c1 == 'r') goto S159;
  return m.FSM_HALT(c1);

S113:
  c1 = m.FSM_CHAR();
  if (c1 == 'l') goto S161;
  return m.FSM_HALT(c1);

S115:
  c1 = m.FSM_CHAR();
  if (c1 == 'u') goto S163;
  return m.FSM_HALT(c1);

S117:
  c1 = m.FSM_CHAR();
  if (c1 == 'I') goto S170;
  return m.FSM_HALT(c1);

S119:
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S172;
  return m.FSM_HALT(c1);

S121:
  c1 = m.FSM_CHAR();
  if (c1 == 'f') goto S176;
  if (c1 == 'b') goto S174;
  return m.FSM_HALT(c1);

S124:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S178;
  return m.FSM_HALT(c1);

S126:
  c1 = m.FSM_CHAR();
  if (c1 == 'c') goto S180;
  return m.FSM_HALT(c1);

S128:
  c1 = m.FSM_CHAR();
  if (c1 == 'b') goto S182;
  return m.FSM_HALT(c1);

S130:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S184;
  return m.FSM_HALT(c1);

S132:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S187;
  return m.FSM_HALT(c1);

S134:
  c1 = m.FSM_CHAR();
  if (c1 == 'k') goto S189;
  return m.FSM_HALT(c1);

S136:
  c1 = m.FSM_CHAR();
  if (c1 == 'k') goto S191;
  return m.FSM_HALT(c1);

S138:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S193;
  return m.FSM_HALT(c1);

S140:
  c1 = m.FSM_CHAR();
  if (c1 == 'z') goto S196;
  return m.FSM_HALT(c1);

S142:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S198;
  return m.FSM_HALT(c1);

S144:
  m.FSM_TAKE(19);
  c1 = m.FSM_CHAR();
  if (c1 == 'Y') goto S200;
  if (0 <= c1) goto S95;
  return m.FSM_HALT(c1);

S147:
  m.FSM_TAKE(18);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S147;
  return m.FSM_HALT(c1);

S149:
  m.FSM_TAKE(22);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S149;
  return m.FSM_HALT(c1);

S151:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(26, c1);
  }
  if ('a' <= c1 && c1 <= 'z') goto S151;
  if (c1 == '_') goto S151;
  if ('A' <= c1 && c1 <= 'Z') goto S151;
  if ('0' <= c1 && c1 <= '9') goto S151;
  return m.FSM_HALT(c1);

S157:
  m.FSM_TAKE(27);
  return m.FSM_HALT();

S159:
  c1 = m.FSM_CHAR();
  if (c1 == 'b') goto S205;
  return m.FSM_HALT(c1);

S161:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S207;
  return m.FSM_HALT(c1);

S163:
  c1 = m.FSM_CHAR();
  if (c1 == 'z') goto S209;
  if (c1 == 't') goto S219;
  if (c1 == 'r') goto S212;
  if (c1 == 'g') goto S217;
  if (c1 == '=') goto S221;
  if (c1 == '8') goto S215;
  return m.FSM_HALT(c1);

S170:
  c1 = m.FSM_CHAR();
  if (c1 == 'Y') goto S227;
  return m.FSM_HALT(c1);

S172:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S229;
  return m.FSM_HALT(c1);

S174:
  c1 = m.FSM_CHAR();
  if (c1 == 'u') goto S231;
  return m.FSM_HALT(c1);

S176:
  c1 = m.FSM_CHAR();
  if (c1 == 'i') goto S233;
  return m.FSM_HALT(c1);

S178:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(17, c1);
  }
  return m.FSM_HALT(c1);

S180:
  c1 = m.FSM_CHAR();
  if (c1 == '-') goto S237;
  return m.FSM_HALT(c1);

S182:
  c1 = m.FSM_CHAR();
  if (c1 == '-') goto S239;
  return m.FSM_HALT(c1);

S184:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(3, c1);
  }
  if (c1 == 'n') goto S243;
  return m.FSM_HALT(c1);

S187:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S245;
  return m.FSM_HALT(c1);

S189:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(6, c1);
  }
  return m.FSM_HALT(c1);

S191:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(7, c1);
  }
  return m.FSM_HALT(c1);

S193:
  c1 = m.FSM_CHAR();
  if (c1 == '5') goto S253;
  if (c1 == '0') goto S251;
  return m.FSM_HALT(c1);

S196:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S255;
  return m.FSM_HALT(c1);

S198:
  c1 = m.FSM_CHAR();
  if (c1 == '3') goto S257;
  return m.FSM_HALT(c1);

S200:
  m.FSM_TAKE(19);
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(13, c1);
  }
  if (0 <= c1) goto S95;
  return m.FSM_HALT(c1);

S203:
  m.FSM_TAKE(26);
  return m.FSM_HALT();

S205:
  c1 = m.FSM_CHAR();
  if (c1 == 'o') goto S262;
  return m.FSM_HALT(c1);

S207:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(2, c1);
  }
  return m.FSM_HALT(c1);

S209:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S264;
  if (c1 == '1') goto S266;
  return m.FSM_HALT(c1);

S212:
  c1 = m.FSM_CHAR();
  if (c1 == '3') goto S270;
  if (c1 == '2') goto S268;
  return m.FSM_HALT(c1);

S215:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S272;
  return m.FSM_HALT(c1);

S217:
  c1 = m.FSM_CHAR();
  if (c1 == 'b') goto S274;
  return m.FSM_HALT(c1);

S219:
  c1 = m.FSM_CHAR();
  if (c1 == 'i') goto S276;
  return m.FSM_HALT(c1);

S221:
  c1 = m.FSM_CHAR();
  if (c1 == 'z') goto S209;
  if (c1 == 't') goto S219;
  if (c1 == 'r') goto S212;
  if (c1 == 'g') goto S217;
  if (c1 == '8') goto S215;
  return m.FSM_HALT(c1);

S227:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(13, c1);
  }
  return m.FSM_HALT(c1);

S229:
  c1 = m.FSM_CHAR();
  if (c1 == 's') goto S278;
  return m.FSM_HALT(c1);

S231:
  c1 = m.FSM_CHAR();
  if (c1 == 'g') goto S280;
  return m.FSM_HALT(c1);

S233:
  c1 = m.FSM_CHAR();
  if (c1 == 'n') goto S282;
  return m.FSM_HALT(c1);

S235:
  m.FSM_TAKE(17);
  return m.FSM_HALT();

S237:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S284;
  return m.FSM_HALT(c1);

S239:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S286;
  return m.FSM_HALT(c1);

S241:
  m.FSM_TAKE(3);
  return m.FSM_HALT();

S243:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(4, c1);
  }
  return m.FSM_HALT(c1);

S245:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(5, c1);
  }
  return m.FSM_HALT(c1);

S247:
  m.FSM_TAKE(6);
  return m.FSM_HALT();

S249:
  m.FSM_TAKE(7);
  return m.FSM_HALT();

S251:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(8, c1);
  }
  return m.FSM_HALT(c1);

S253:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(9, c1);
  }
  return m.FSM_HALT(c1);

S255:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S296;
  return m.FSM_HALT(c1);

S257:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(11, c1);
  }
  if (c1 == 'p') goto S300;
  return m.FSM_HALT(c1);

S260:
  m.FSM_TAKE(13);
  return m.FSM_HALT();

S262:
  c1 = m.FSM_CHAR();
  if (c1 == 's') goto S302;
  return m.FSM_HALT(c1);

S264:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S304;
  return m.FSM_HALT(c1);

S266:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S307;
  return m.FSM_HALT(c1);

S268:
  c1 = m.FSM_CHAR();
  if (c1 == 'k') goto S309;
  return m.FSM_HALT(c1);

S270:
  c1 = m.FSM_CHAR();
  if (c1 == 'k') goto S311;
  return m.FSM_HALT(c1);

S272:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S313;
  return m.FSM_HALT(c1);

S274:
  c1 = m.FSM_CHAR();
  if (c1 == 'z') goto S316;
  return m.FSM_HALT(c1);

S276:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S318;
  return m.FSM_HALT(c1);

S278:
  c1 = m.FSM_CHAR();
  if (c1 == 'p') goto S320;
  return m.FSM_HALT(c1);

S280:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(15, c1);
  }
  return m.FSM_HALT(c1);

S282:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S324;
  return m.FSM_HALT(c1);

S284:
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S329;
  return m.FSM_HALT(c1);

S286:
  c1 = m.FSM_CHAR();
  if (c1 == 'a') goto S331;
  return m.FSM_HALT(c1);

S288:
  m.FSM_TAKE(4);
  return m.FSM_HALT();

S290:
  m.FSM_TAKE(5);
  return m.FSM_HALT();

S292:
  m.FSM_TAKE(8);
  return m.FSM_HALT();

S294:
  m.FSM_TAKE(9);
  return m.FSM_HALT();

S296:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(10, c1);
  }
  return m.FSM_HALT(c1);

S298:
  m.FSM_TAKE(11);
  return m.FSM_HALT();

S300:
  c1 = m.FSM_CHAR();
  if (c1 == 'l') goto S335;
  return m.FSM_HALT(c1);

S302:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S337;
  return m.FSM_HALT(c1);

S304:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(3, c1);
  }
  if (c1 == 'n') goto S339;
  return m.FSM_HALT(c1);

S307:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S341;
  return m.FSM_HALT(c1);

S309:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(6, c1);
  }
  return m.FSM_HALT(c1);

S311:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(7, c1);
  }
  return m.FSM_HALT(c1);

S313:
  c1 = m.FSM_CHAR();
  if (c1 == '5') goto S345;
  if (c1 == '0') goto S343;
  return m.FSM_HALT(c1);

S316:
  c1 = m.FSM_CHAR();
  if (c1 == '8') goto S347;
  return m.FSM_HALT(c1);

S318:
  c1 = m.FSM_CHAR();
  if (c1 == '3') goto S349;
  return m.FSM_HALT(c1);

S320:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S352;
  return m.FSM_HALT(c1);

S322:
  m.FSM_TAKE(15);
  return m.FSM_HALT();

S324:
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S358;
  if (c1 == '_') goto S358;
  if ('A' <= c1 && c1 <= 'Z') goto S358;
  if (c1 == '=') goto S354;
  return m.FSM_HALT(c1);

S329:
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S364;
  return m.FSM_HALT(c1);

S331:
  c1 = m.FSM_CHAR();
  if (c1 == 't') goto S366;
  return m.FSM_HALT(c1);

S333:
  m.FSM_TAKE(10);
  return m.FSM_HALT();

S335:
  c1 = m.FSM_CHAR();
  if (c1 == 'u') goto S368;
  return m.FSM_HALT(c1);

S337:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(1, c1);
  }
  return m.FSM_HALT(c1);

S339:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(4, c1);
  }
  return m.FSM_HALT(c1);

S341:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(5, c1);
  }
  return m.FSM_HALT(c1);

S343:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(8, c1);
  }
  return m.FSM_HALT(c1);

S345:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(9, c1);
  }
  return m.FSM_HALT(c1);

S347:
  c1 = m.FSM_CHAR();
  if (c1 == '0') goto S370;
  return m.FSM_HALT(c1);

S349:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(11, c1);
  }
  if (c1 == 'p') goto S372;
  return m.FSM_HALT(c1);

S352:
  c1 = m.FSM_CHAR();
  if (c1 == 'e') goto S374;
  return m.FSM_HALT(c1);

S354:
  c1 = m.FSM_CHAR();
  if ('a' <= c1 && c1 <= 'z') goto S376;
  if (c1 == '_') goto S376;
  if ('A' <= c1 && c1 <= 'Z') goto S376;
  return m.FSM_HALT(c1);

S358:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(29, c1);
  }
  if ('a' <= c1 && c1 <= 'z') goto S358;
  if (c1 == '_') goto S358;
  if ('A' <= c1 && c1 <= 'Z') goto S358;
  if ('0' <= c1 && c1 <= '9') goto S358;
  return m.FSM_HALT(c1);

S364:
  c1 = m.FSM_CHAR();
  if (c1 == 'h') goto S384;
  return m.FSM_HALT(c1);

S366:
  c1 = m.FSM_CHAR();
  if (c1 == 'h') goto S386;
  return m.FSM_HALT(c1);

S368:
  c1 = m.FSM_CHAR();
  if (c1 == 's') goto S388;
  return m.FSM_HALT(c1);

S370:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(10, c1);
  }
  return m.FSM_HALT(c1);

S372:
  c1 = m.FSM_CHAR();
  if (c1 == 'l') goto S390;
  return m.FSM_HALT(c1);

S374:
  c1 = m.FSM_CHAR();
  if (c1 == 'd') goto S392;
  return m.FSM_HALT(c1);

S376:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(28, c1);
  }
  if ('a' <= c1 && c1 <= 'z') goto S376;
  if (c1 == '_') goto S376;
  if ('A' <= c1 && c1 <= 'Z') goto S376;
  if ('0' <= c1 && c1 <= '9') goto S376;
  return m.FSM_HALT(c1);

S382:
  m.FSM_TAKE(29);
  return m.FSM_HALT();

S384:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S396;
  if (0 <= c1) goto S398;
  return m.FSM_HALT(c1);

S386:
  c1 = m.FSM_CHAR();
  if (c1 == '=') goto S400;
  if (0 <= c1) goto S402;
  return m.FSM_HALT(c1);

S388:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(12, c1);
  }
  return m.FSM_HALT(c1);

S390:
  c1 = m.FSM_CHAR();
  if (c1 == 'u') goto S406;
  return m.FSM_HALT(c1);

S392:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(14, c1);
  }
  return m.FSM_HALT(c1);

S394:
  m.FSM_TAKE(28);
  return m.FSM_HALT();

S396:
  m.FSM_TAKE(21);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S410;
  return m.FSM_HALT(c1);

S398:
  m.FSM_TAKE(21);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S398;
  return m.FSM_HALT(c1);

S400:
  m.FSM_TAKE(25);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S412;
  return m.FSM_HALT(c1);

S402:
  m.FSM_TAKE(25);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S402;
  return m.FSM_HALT(c1);

S404:
  m.FSM_TAKE(12);
  return m.FSM_HALT();

S406:
  c1 = m.FSM_CHAR();
  if (c1 == 's') goto S414;
  return m.FSM_HALT(c1);

S408:
  m.FSM_TAKE(14);
  return m.FSM_HALT();

S410:
  m.FSM_TAKE(20);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S410;
  return m.FSM_HALT(c1);

S412:
  m.FSM_TAKE(24);
  c1 = m.FSM_CHAR();
  if (0 <= c1) goto S412;
  return m.FSM_HALT(c1);

S414:
  c1 = m.FSM_CHAR();
  if (m.FSM_META_EOB(c1)) {
    m.FSM_TAKE(12, c1);
  }
  return m.FSM_HALT(c1);
}

