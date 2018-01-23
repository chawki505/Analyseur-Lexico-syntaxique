%{
#include <stdio.h>
#include "analyseSyntaxique.tab.h"

void yyerror(const char * msg);
extern int numLigne;
%}

Lettre [a-zA-Z]
Chiffre [0-9]
Operateur [+|-]

%%
"programme" { return PROGRAMME; }
"debut"     { return DEBUT; }
"fin"       { return FIN; }

"si"        { return SI; }
"alors"     { return ALORS; }
"sinon"     { return SINON; }
"fsi"       { return FSI; }

"const"     { return CONST; }
"var"       { return VAR; }
"ent"       { return ENT; }
"bool"      { return BOOL; }
"vrai"      { return VRAI; }
"faux"      { return FAUX; }

{Operateur} { return OPERATEUR; }
"="         { return EGALE; }
":="        { return AFFECTATION; }
";"         { return SEPARATEUR_PV; }
","         { return SEPARATEUR_V; }
":"         { return SEPARATEUR_2P; }

{Lettre}    { yylval.let = yytext; return LETTRE; }
{Chiffre}   { yylval.num = atoi(yytext); return CHIFFRE; }

"\n"        { numLigne++; }
[ \t]+      ;

.           { char msg[0x20]; sprintf(msg,"Erreur Lexicale < %s >",yytext); yyerror(msg); return 1; }
%%
