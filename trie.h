/* FRANT Madalina - 315CB */

#include "carte.h"

#define NR_MAX_DESCENDENTI 68

typedef struct CelTrie1
{
    struct CelTrie1** descendenti;
    Carte* carte;
} Trie1;

typedef struct CelTrie2
{
    struct CelTrie2** descendenti;
    Trie1* trie; // arbore cu toate cartile scrise de un autor
} Trie2;

Trie1* InitT1();

Trie2* InitT2();

void DistrT1(Trie1** t);

void DistrT2(Trie2** t);

int CharToIndex(char c);

char IndexToChar(int i);

void add_bookT1(Trie1* t, Carte* c);

void add_bookT2(Trie2* t, Carte* c);

void add_book(Trie1* T1, Trie2* T2);

Carte* find_book(Trie1* t, char* titlu);

Trie1* find_author(Trie2* t, char* autor);

void search_book(Trie1* t, char* titlu, FILE* f);

void search_by_author(Trie2* t, char* autor, FILE* f);

void print_book(Trie1* t, int* printed, int max, FILE* f);

void print_author(Trie2* t, char* str, int* printed, int max, FILE* f);

void autocomplete_book(Trie1* t, char* titlu, FILE* f);

void autocomplete_author(Trie2* t, char* autor, FILE* f);

void list_author(Trie2* t, char* autor, FILE* f);

int AreCarti(Trie1* t);

int AreDescendentiT1(Trie1* t);

int AreDescendentiT2(Trie2* t);

void delete_bookT1(Trie1** t, char* titlu, int k);

void delete_authorT2(Trie2** t, char* autor, int k);

void delete_book(Trie1** T1, Trie2** T2, FILE* f);