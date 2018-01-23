%{
#include <stdio.h>
#include "tableSymbole.h"

void yyerror(const char * msg);
int yylex(void);

int numLigne;
liste table;


%}

%union{
  int num;
  char *let;
}

%token PROGRAMME DEBUT FIN
%token SI ALORS SINON FSI
%token CONST VAR ENT
%token BOOL FAUX VRAI
%token SEPARATEUR_PV SEPARATEUR_V SEPARATEUR_2P
%token OPERATEUR EGALE AFFECTATION

%token <let> LETTRE
%token <num> CHIFFRE

%left OPERATEUR

%type <let> Ident Lettre
%type <num> Chiffre

%start S

%%
S: PROGRAMME Ident SEPARATEUR_PV D DEBUT Inst FIN
 ;

D: C V
 ;

C: CONST Dec
 |
 ;

Dec: Ident EGALE Num SEPARATEUR_PV Dec
   | Ident EGALE Num
   ;

V: VAR Dev
 |
 ;

Dev: Ident M SEPARATEUR_2P Type SEPARATEUR_PV Dev
   | Ident M SEPARATEUR_2P Type
   ;

Type: ENT
    | BOOL
    ;

Inst: Instr
    |
    ;

Instr: Ident AFFECTATION Exp I
     | SI Ident ALORS Instr SINON Instr FSI
     | SI Ident ALORS Instr FSI
     ;

I: SEPARATEUR_PV Instr
 |
 ;

Exp: Exp OPERATEUR Exp
   | Ident
   | Cste
   ;

Ident: Lettre SuitL
     ;

SuitL: Lettre SuitL
     | Chiffre SuitL
     |
     ;

Lettre: LETTRE
      ;

Chiffre: CHIFFRE
       ;

Cste: Chiffre SuitC
    ;

SuitC: SuitC Chiffre
     |
     ;


M: SEPARATEUR_V Ident M
 |
 ;

Num: Cste
   | VRAI
   | FAUX
   ;
%%

void yyerror(const char * msg){
  printf("\n** ligne %d : %s **\n",numLigne,msg);
}

int main(){

  numLigne = 1;
  table=init(table);


  if(yyparse()==0){
     printf("\nGrammaire reconnue\n" );
     afficherTable(table);
     }
  else
     printf("\nGrammaire non reconnue\n" );


  printf("\nFin de l'analyse\n" );

  return 0;
}
