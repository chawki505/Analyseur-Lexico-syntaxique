#ifndef SYMBOLE_TABLE
#define SYMBOLE_TABLE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*code =
1 : constant
2 : variable ent
3 : variable bool */

/*declaration linkedList
[code , le nom de la variable , le suivant dans la table ]*/
typedef struct maillon maillon;
struct maillon
{
  int code;
  char *ID;
  struct maillon *suivant;
};
typedef maillon *liste;

/*fonction pour rechercher un symbole existant dans la table
@return 0 si exite pas dans la table
@return -1 si existe dans la table
@return 1 si la liste est vide
*/
int rechercher(char *ident, liste tableSymbole)
{
  //test si la list est vide (aucune adresse)
  if (tableSymbole == NULL)
  {
    return 1;
  }
  //creation maillon tmp pour le parcour
  maillon *tmp = tableSymbole;
  //boucle de parcour
  while (tmp != NULL)
  {
    if (strcmp(tmp->ID, ident) == 0)
    {
      return -1;
    }
    else
    {
      tmp = tmp->suivant;
    }
  }
  return 0;
}

//fonction init une liste linked
liste init(liste tableSymbole)
{
  tableSymbole = NULL;
  return tableSymbole;
}

/*fonction d'insertion en fin de liste*/
liste insertionFin(int code, char *ident, liste tableSymbole)
{
  //creation maillon et inialisation des donnees
  maillon *newMaillon = (maillon *)malloc(sizeof(maillon));
  newMaillon->code = code;
  newMaillon->ID = ident;
  newMaillon->suivant = NULL;
  //test si la list est vide
  if (tableSymbole == NULL)
  {
    return newMaillon;
  }
  else
  {
    maillon *tmp = tableSymbole;
    while (tmp->suivant != NULL)
    {
      tmp = tmp->suivant;
    }
    tmp->suivant = newMaillon;
    return tableSymbole;
  }
}

/*fonction d'insertion en tete de liste*/
liste insertionDebut(int code, char *ident, liste tableSymbole)
{
  //creation maillon et inialisation des donnees
  maillon *newMaillon = (maillon *)malloc(sizeof(maillon));
  newMaillon->code = code;
  newMaillon->ID = ident;
  newMaillon->suivant = tableSymbole;
  return newMaillon;
}

/*fonction pour tester si le id en entrer nest pas un mot cle
@return 0 si cest pas un mot cle
@return -1 si cest un mot cle */
int isMotCle(char *ident)
{
  char *motCle[] = {"programme", "debut", "fin",
                    "var", "const", "bool", "ent",
                    "si", "alors", "sinon", "fsi",
                    "vrai", "faux",
                    "+", ",", ":", ":=", "=", ";"};
  int tailleTab = 19;

  for (int i = 0; i < tailleTab; i++)
  {
    if (strcmp(motCle[i], ident) == 0)
    {
      return -1;
    }
  }
  return 0;
}

//fonction a utiliser dans le fichier yacc(bison) pour linsertion dans la table des symbole
liste insertion(int code, char *ident, liste tableSymbole)
{
  if (isMotCle(ident) == 0)
  {
    if (rechercher(ident, tableSymbole) == 0)
    {
      tableSymbole = insertionFin(code, ident, tableSymbole);
    }
    if (rechercher(ident, tableSymbole) == 1)
    {
      tableSymbole = insertionDebut(code, ident, tableSymbole);
    }
  }
  return tableSymbole;
}

//fonction pour afficher notre table des symboles
void afficherTable(liste tableSymbole)
{
  maillon *tmp = tableSymbole;
  printf(" ID           Type\n");

  while (tmp != NULL)
  {
    if (tmp->code == 1)
      printf("- %s      Constant \n", tmp->ID);
    if (tmp->code == 2)
      printf("- %s      Variable ent \n", tmp->ID);
    if (tmp->code == 3)
      printf("- %s      Variable bool \n", tmp->ID);

    tmp = tmp->suivant;
  }
}
#endif