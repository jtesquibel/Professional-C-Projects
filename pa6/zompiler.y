%{
#include "node.h"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* g_MainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

%error-verbose

/* Terminal symbols */
%token <string> TINTEGER TBOOLEAN
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN
%token <token> TMAIN TROTATE TFORWARD TISHUMAN TISZOMBIE TIF TELSE TATTACK TRANGEDATTACK TISRANDOM TISPASSABLE

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate forward attack ranged_attack ifelse if else
 
/* Expressions */
%type <numeric> numeric

%type <boolean> boolean is_human is_zombie is_passable is_random

// %type <string> if else

%%

main_loop	: TMAIN TLBRACE block TRBRACE { std::cout << "Main entry point found!" << std::endl; g_MainBlock = $3; g_MainBlock->SetMainBlock(); }
;

block		: block statement { std::cout << "Multiple statement" << std::endl; $$->AddStatement($2); }
            | statement { std::cout << "Single statement" << std::endl; $$ = new NBlock(); $$->AddStatement($1); }
            
;
/* TODO: Add support for multiple statements in a block */

statement	: rotate TSEMI | forward TSEMI | attack TSEMI | ranged_attack TSEMI | if | else | ifelse
;

boolean     : is_human | is_zombie | is_passable | is_random
;

ifelse      : if TLBRACE block TRBRACE else TLBRACE block TRBRACE { $$ = new NIfElse($1, $3, $7); }
;

if          : TIF TLPAREN boolean TRPAREN { std::cout << "If statement" << std::endl; $$ = new NIf($3); }
;

else        : TELSE { std::cout << "Else statement" << std::endl; $$ = new NElse(); }
;
			
rotate		: TROTATE TLPAREN numeric TRPAREN { std::cout << "Rotate command" << std::endl; $$ = new NRotate($3); }
;

forward     : TFORWARD TLPAREN TRPAREN { std::cout << "Forward command" << std::endl; $$ = new NForward(); }
;

is_human    : TISHUMAN TLPAREN numeric TRPAREN { std::cout << "Is human bool command" << std::endl; $$ = new NIsHuman($3); }
;

is_zombie   : TISZOMBIE TLPAREN numeric TRPAREN { std::cout << "Is zombie bool command" << std::endl; $$ = new NIsZombie($3); }
;

is_passable : TISPASSABLE TLPAREN TRPAREN { std::cout << "Is passable bool command" << std::endl; $$ = new NIsPassable(); }
;

is_random   : TISRANDOM TLPAREN TRPAREN { std::cout << "Is random bool command" << std::endl; $$ = new NIsRandom(); }
;

attack      : TATTACK TLPAREN TRPAREN { std::cout << "Attack command" << std::endl; $$ = new NAttack(); }
;

ranged_attack : TRANGEDATTACK TLPAREN TRPAREN { std::cout << "Ranged attack command" << std::endl; $$ = new NRangedAttack(); }
;

numeric		: TINTEGER { std::cout << "Numeric value of " << *($1) << std::endl; $$ = new NNumeric(*$1); }
;



%%
