/* FRANT Madalina - 315CB */

#include "trie.h"

int main(int argc, char *argv[])
{
    FILE *input, *output;
    size_t len = 0;
    char* line = NULL;

    input = fopen(argv[1], "r");
    if (input == NULL)
        return 0;
    output = fopen(argv[2], "w");
    if (output == NULL)
        return 0;

    Trie1* T1 = InitT1();
    Trie2* T2 = InitT2();

    // citeste fiecare linie din fisier
    while (getline(&line, &len, input) != -1)
    {
        if (line[0] == '\n') // daca linia contine doar '\n'
            continue;

        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        char* comanda = strtok(line, " ");

        if (strcmp(comanda, "add_book") == 0)
        {
            add_book(T1, T2);
        }

        if (strcmp(comanda, "search_book") == 0)
        {
            char* titlu = strtok(NULL, "");  
            if (titlu[strlen(titlu) - 1] == '~')
            {
                titlu[strlen(titlu) - 1] = '\0';
                autocomplete_book(T1, titlu, output);
            }
            else
            {
                search_book(T1, titlu, output);
            }
        }

        if (strcmp(comanda, "list_author") == 0)
        {
            char* autor = strtok(NULL, "");
            if (autor[strlen(autor) - 1] == '~')
            {
                autor[strlen(autor) - 1] = '\0';
                autocomplete_author(T2, autor, output);
            }
            else
            {
                list_author(T2, autor, output);
            }
        }

        if (strcmp(comanda, "search_by_author") == 0)
        {
            char* autor = strtok(NULL, ":");
            if (autor[strlen(autor) - 1] == '~')
            {
                autor[strlen(autor) - 1] = '\0';
                autocomplete_author(T2, autor, output);
            }
            else
            {
                search_by_author(T2, autor, output);
            }
        }

        if (strcmp(comanda, "delete_book") == 0)
        {
            delete_book(&T1, &T2, output);
        }
    }
    free(line);

    fclose(input);
    fclose(output);

    /* eliberare memorie */
    DistrT1(&T1);
    DistrT2(&T2);

    return 0;
}