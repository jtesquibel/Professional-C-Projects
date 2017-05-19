/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TINTEGER = 258,
     TBOOLEAN = 259,
     TLBRACE = 260,
     TRBRACE = 261,
     TSEMI = 262,
     TLPAREN = 263,
     TRPAREN = 264,
     TMAIN = 265,
     TROTATE = 266,
     TFORWARD = 267,
     TISHUMAN = 268,
     TISZOMBIE = 269,
     TIF = 270,
     TELSE = 271,
     TATTACK = 272,
     TRANGEDATTACK = 273,
     TISRANDOM = 274,
     TISPASSABLE = 275
   };
#endif
/* Tokens.  */
#define TINTEGER 258
#define TBOOLEAN 259
#define TLBRACE 260
#define TRBRACE 261
#define TSEMI 262
#define TLPAREN 263
#define TRPAREN 264
#define TMAIN 265
#define TROTATE 266
#define TFORWARD 267
#define TISHUMAN 268
#define TISZOMBIE 269
#define TIF 270
#define TELSE 271
#define TATTACK 272
#define TRANGEDATTACK 273
#define TISRANDOM 274
#define TISPASSABLE 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "zompiler.y"
{
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}
/* Line 1529 of yacc.c.  */
#line 99 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE zompilerlval;

