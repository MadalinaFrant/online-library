/* FRANT Madalina - 315CB */

#include "trie.h"

Trie1* InitT1()
{
    Trie1* T1 = (Trie1* )malloc(sizeof(Trie1));
    if (T1 == NULL)
        return NULL;

    T1->descendenti = malloc(NR_MAX_DESCENDENTI * sizeof(Trie1));
    if (T1->descendenti == NULL)
        return NULL;

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
        T1->descendenti[i] = NULL;

    T1->carte = NULL;

    return T1;
}

Trie2* InitT2()
{
    Trie2* T2 = (Trie2* )malloc(sizeof(Trie2));
    if (T2 == NULL)
        return NULL;

    T2->descendenti = malloc(NR_MAX_DESCENDENTI * sizeof(Trie2));
    if (T2->descendenti == NULL)
        return NULL;

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
        T2->descendenti[i] = NULL;

    T2->trie = NULL;

    return T2;
}

void DistrT1(Trie1** T1)
{
    if (*T1 == NULL)
        return;

    if ((*T1)->carte != NULL)
    {
        ElibCarte((*T1)->carte);
        (*T1)->carte = NULL;
    }

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if ((*T1)->descendenti[i] != NULL)
            DistrT1(&((*T1)->descendenti[i]));
    }

    free((*T1)->descendenti);
    free(*T1);
    *T1 = NULL;
}

void DistrT2(Trie2** T2)
{
    if (*T2 == NULL)
        return;

    if ((*T2)->trie != NULL)
    {
        DistrT1(&((*T2)->trie));
        (*T2)->trie = NULL;
    }

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if ((*T2)->descendenti[i] != NULL)
            DistrT2(&((*T2)->descendenti[i]));
    }

    free((*T2)->descendenti);
    free(*T2);
    *T2 = NULL;
}

int CharToIndex(char c)
{
    int i;

    if (c >= 'a' && c <= 'z')
            i = c - 97;
    if (c >= 'A' && c <= 'Z')
            i = c - 39;
    if (c >= '0' && c <= '9')
            i = c + 4;
    if (c == '.')
            i = c + 16;
    if (c == '-')
            i = c + 18;
    if (c == '\'')
            i = c + 25;
    if (c == '?')
            i = c + 2;
    if (c == '!')
            i = c + 33;
    if (c == ' ')
            i = c + 35;

    return i;
}

char IndexToChar(int i)
{
    char str[] =
     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    return str[i];
}

void add_bookT1(Trie1* t, Carte* c)
{
    int niv, i, lg;
    lg = strlen(c->titlu);
    Trie1* aux = t;
    for (niv = 0; niv < lg; niv++)
    {
        i = CharToIndex(c->titlu[niv]);
        if (aux->descendenti[i] == NULL)
            aux->descendenti[i] = InitT1();

        aux = aux->descendenti[i];
    }

    if (aux->carte == NULL)
        aux->carte = copieCarte(c);
}

void add_bookT2(Trie2* t, Carte* c)
{
    int niv, i, lg;
    lg = strlen(c->autor);
    Trie2* aux = t;
    for (niv = 0; niv < lg; niv++)
    {
        i = CharToIndex(c->autor[niv]);
        if (aux->descendenti[i] == NULL)
            aux->descendenti[i] = InitT2();

        aux = aux->descendenti[i];
    }

    if (aux->trie == NULL)
        aux->trie = InitT1();
    
    // adauga cartea in arborele aferent autorului
    add_bookT1(aux->trie, c);
}

void add_book(Trie1* T1, Trie2* T2)
{
    char* titlu = strtok(NULL, ":");
    char* autor = strtok(NULL, ":");
    int rating = atoi(strtok(NULL, ":"));
    int nr_pag = atoi(strtok(NULL, ":"));

    Carte* carte = InitCarte();
    if (carte == NULL)
        return;

    strcpy(carte->titlu, titlu);
    strcpy(carte->autor, autor);
    carte->rating = rating;
    carte->nr_pag = nr_pag;

    add_bookT1(T1, carte);
    add_bookT2(T2, carte);

    Carte *c = carte;
    ElibCarte(c);
}

Carte* find_book(Trie1* t, char* titlu)
{
    int niv, i, lg;
    lg = strlen(titlu);
    Trie1* aux = t;
    for (niv = 0; niv < lg; niv++)
    {
        i = CharToIndex(titlu[niv]);
        if (aux->descendenti[i] == NULL) // litera nu exista in arbore
            return NULL;

        aux = aux->descendenti[i];
    }

    if (aux == NULL)
        return NULL;
    else if (aux->carte == NULL) // nu este sfarsit de titlu
        return NULL;

    return aux->carte;
}

Trie1* find_author(Trie2* t, char* autor)
{
    int niv, i, lg;
    lg = strlen(autor);
    Trie2* aux = t;
    for (niv = 0; niv < lg; niv++)
    {
        i = CharToIndex(autor[niv]);
        if (aux->descendenti[i] == NULL) // litera nu exista in arbore
            return NULL;

        aux = aux->descendenti[i];
    }

    if (aux == NULL)
        return NULL;
    else if (aux->trie == NULL) // nu este sfarsit de nume de autor
        return NULL;

    return aux->trie;
}

void print_book(Trie1* t, int* printed, int max, FILE* f)
{
    if (t == NULL)
        return;

    if ((t->carte != NULL) && (*printed < max))
    {
        fprintf(f, "%s\n", t->carte->titlu);
        (*printed)++;
    }

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if (t->descendenti[i] != NULL)
            print_book(t->descendenti[i], printed, max, f);
    }
}

void print_author(Trie2* t, char* str, int* printed, int max, FILE* f)
{
    if (t == NULL)
        return;

    if ((t->trie != NULL) && (*printed < max))
    {
        (*printed)++;
        fprintf(f, "%s\n", str);
    }

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if (t->descendenti[i] != NULL)
        {
            char* c = calloc(2, sizeof(char));
            c[0] = IndexToChar(i);
            strcat(str, c); // adauga caracterul curent la sir
            free(c);

            print_author(t->descendenti[i], str, printed, max, f);

            /* dupa printarea tuturor cuvintelor existente cu un
            anumit prefix */
            str[strlen(str) - 1] = '\0';
        }
    }
}

void autocomplete_book(Trie1* t, char* titlu, FILE* f)
{
    int niv, i, lg, ok = 1;
    lg = strlen(titlu);
    Trie1* aux = t;
    for (niv = 0; niv < lg; niv++)
    {
        i = CharToIndex(titlu[niv]);
        if (aux->descendenti[i] == NULL)
        {
            ok = 0;
            break;
        }
        aux = aux->descendenti[i];
    }

    if (aux == NULL)
        ok = 0;

    if (ok == 0)
    {
        fprintf(f, "Nicio carte gasita.\n");
        return;
    }

    int p = 0;
    print_book(aux, &p, 3, f); // afiseaza primele maxim 3 titluri
}

void autocomplete_author(Trie2* t, char* autor, FILE* f)
{
    int niv, i, lg, ok = 1;
    lg = strlen(autor);
    Trie2* aux = t;
    for (niv = 0; niv < lg; niv++)
    {
        i = CharToIndex(autor[niv]);
        if (aux->descendenti[i] == NULL)
        {
            ok = 0;
            break;
        }
        aux = aux->descendenti[i];
    }

    if (aux == NULL)
        ok = 0;

    if (ok == 0)
    {
        fprintf(f, "Niciun autor gasit.\n");
        return;
    }

    int p = 0;
    print_author(aux, autor, &p, 3, f); // afiseaza primii maxim 3 autori
}

void search_book(Trie1* t, char* titlu, FILE* f)
{
    Carte* carte = find_book(t, titlu);
    if (carte == NULL)
    {
        fprintf(f, "Cartea %s nu exista in recomandarile tale.\n", titlu);
    }
    else
    { 
        fprintf(f, "Informatii recomandare: ");
        AfiCarte(carte, f);
    }
}

void search_by_author(Trie2* T2, char* autor, FILE* f)
{
    char* titlu = strtok(NULL, "");
    Trie1* T1 = find_author(T2, autor);
    if (T1 == NULL)
    {
        fprintf(f, "Autorul %s nu face parte din recomandarile tale.\n", autor);
        return;
    }
    // daca autorul exista cauta cartea in arborele cartilor scrise de acesta
    if (titlu[strlen(titlu) - 1] == '~')
    {
        titlu[strlen(titlu) - 1] = '\0';
        autocomplete_book(T1, titlu, f);
    }
    else
    {
        search_book(T1, titlu, f);
    }
}

void list_author(Trie2* t2, char* autor, FILE* f)
{
    int p = 0;
    Trie1* t1 = find_author(t2, autor);
    if (t1 == NULL)
        fprintf(f, "Autorul %s nu face parte din recomandarile tale.\n", autor);
    else
        print_book(t1, &p, NR_MAX_DESCENDENTI, f);
}

int AreCarti(Trie1* t)
{
    if (t == NULL)
        return 0;

    if (t->carte != NULL)
        return 1;

    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if (t->descendenti[i] != NULL)
            if (AreCarti(t->descendenti[i]) == 1)
                return 1;
    }
    return 0;
}

int AreDescendentiT1(Trie1* t)
{
    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if (t->descendenti[i] != NULL)
            return 1;
    }

    return 0;
}

int AreDescendentiT2(Trie2* t)
{
    int i;
    for (i = 0; i < NR_MAX_DESCENDENTI; i++)
    {
        if (t->descendenti[i] != NULL)
            return 1;
    }

    return 0;
}

void delete_bookT1(Trie1** t, char* titlu, int k)
{
    if (*t == NULL)
        return;

    if (k == strlen(titlu))
    {
        if (AreDescendentiT1(*t) == 0)
        {
            DistrT1(t);
        }
        // litera la care se afla pointerul este continuta in alt cuvant
        else if ((*t)->carte != NULL)
        {
            ElibCarte((*t)->carte);
            (*t)->carte = NULL;
        }

        return;
    }

    int i = CharToIndex(titlu[k]);
    delete_bookT1(&((*t)->descendenti[i]), titlu, k + 1);

    if ((AreDescendentiT1(*t) == 0) && ((*t)->carte == NULL) && (k != 0))
        DistrT1(t);

}

void delete_authorT2(Trie2** t, char* autor, int k)
{
    if (*t == NULL)
        return;

    if (k == strlen(autor))
    {
        if (AreDescendentiT2(*t) == 0)
        {
            DistrT2(t);
        }
        // litera la care se afla pointerul este continuta in alt cuvant
        else if ((*t)->trie != NULL)
        {
            DistrT1(&((*t)->trie));
            (*t)->trie = NULL;
        }

        return;
    }

    int i = CharToIndex(autor[k]);
    delete_authorT2(&((*t)->descendenti[i]), autor, k + 1);

    if ((AreDescendentiT2(*t) == 0) && ((*t)->trie == NULL) && (k != 0))
        DistrT2(t);

}

void delete_book(Trie1** T1, Trie2** T2, FILE* f)
{   
    char* titlu = strtok(NULL, "");
    Carte* c = find_book(*T1, titlu);
    if (c == NULL)
    {
        fprintf(f, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return;
    }
    char* autor = malloc(LMAX_AUTOR * sizeof(char) + 1);
    strcpy(autor, c->autor);

    // elimina cartea din T1
    delete_bookT1(T1, titlu, 0);

    // elimina cartea din arborele aferent autorului
    Trie1* t = find_author(*T2, autor);
    delete_bookT1(&t, titlu, 0);

    // elimina autorul din T2 daca nu mai are alte carti
    if (AreCarti(t) == 0)
        delete_authorT2(T2, autor, 0);

    free(autor);
}