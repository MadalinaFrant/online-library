/* FRANT Madalina - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LMAX_TITLU 50
#define LMAX_AUTOR 40

typedef struct
{
    char* titlu;
    char* autor;
    int rating;
    int nr_pag;
} Carte;

Carte* InitCarte();

void AfiCarte(void* x, FILE* f);

void ElibCarte(void* x);

Carte* copieCarte(Carte* c);