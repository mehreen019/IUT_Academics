/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_VALIDATOR_TAB_H_INCLUDED
# define YY_YY_VALIDATOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    HTML_OPEN = 258,               /* HTML_OPEN  */
    HTML_CLOSE = 259,              /* HTML_CLOSE  */
    HEAD_OPEN = 260,               /* HEAD_OPEN  */
    HEAD_CLOSE = 261,              /* HEAD_CLOSE  */
    TITLE_OPEN = 262,              /* TITLE_OPEN  */
    TITLE_CLOSE = 263,             /* TITLE_CLOSE  */
    BODY_OPEN = 264,               /* BODY_OPEN  */
    BODY_CLOSE = 265,              /* BODY_CLOSE  */
    H1_OPEN = 266,                 /* H1_OPEN  */
    H1_CLOSE = 267,                /* H1_CLOSE  */
    H2_OPEN = 268,                 /* H2_OPEN  */
    H2_CLOSE = 269,                /* H2_CLOSE  */
    P_OPEN = 270,                  /* P_OPEN  */
    P_CLOSE = 271,                 /* P_CLOSE  */
    DIV_OPEN = 272,                /* DIV_OPEN  */
    DIV_CLOSE = 273,               /* DIV_CLOSE  */
    B_OPEN = 274,                  /* B_OPEN  */
    B_CLOSE = 275,                 /* B_CLOSE  */
    I_OPEN = 276,                  /* I_OPEN  */
    I_CLOSE = 277,                 /* I_CLOSE  */
    TEXT_CONTENT = 278             /* TEXT_CONTENT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_VALIDATOR_TAB_H_INCLUDED  */
