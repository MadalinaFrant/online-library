/* FRANT Madalina - 315CB */

#include "carte.h"

Carte* InitCarte()
{
    Carte* carte = (Carte* )malloc(sizeof(Carte));
    if (carte == NULL)
        return NULL;

    carte->titlu = (char* )malloc(LMAX_TITLU * sizeof(char) + 1);
    if (carte->titlu == NULL)
        return NULL;

    carte->autor = (char* )malloc(LMAX_AUTOR * sizeof(char) + 1);
    if (carte->autor == NULL)
        return NULL;

    return carte;
}

void AfiCarte(void* x, FILE* f)
{
    Carte* carte = (Carte* )x;
    fprintf(f, "%s, %s, %d, %d\n", 
     carte->titlu, carte->autor, carte->rating, carte->nr_pag);
}

void ElibCarte(void* x)
{
    Carte* carte = (Carte* )x;
    free(carte->autor);
    free(carte->titlu);
    free(carte);
}

Carte* copieCarte(Carte* c)
{
    Carte* carte = InitCarte();
    if (carte == NULL)
        return NULL;
    
    strcpy(carte->titlu, c->titlu);
    strcpy(carte->autor, c->autor);
    carte->rating = c->rating;
    carte->nr_pag = c->nr_pag;

    return carte;
}