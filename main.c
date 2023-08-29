#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define clear() printf("\033[H\033[J")
#define LETTERS 15
#define COUNT 353

typedef struct relation {
    char source[LETTERS];
    char target[LETTERS];
    int weight;
} relation;

relation read_relation(FILE *file_ptr) {
    relation curr_relation;
    
    for (int n = 0; n < LETTERS; n++)
    {
        char c;

        fscanf(file_ptr, "%c", &c);
        
        if (c == ',') {
            curr_relation.source[n] = '\0';
            break;
        } else {
            curr_relation.source[n] = c;
        }
    }

    for (int n = 0; n < LETTERS; n++)
    {
        char c;

        fscanf(file_ptr, "%c", &c);
        
        if (c == ',') {
            curr_relation.target[n] = '\0';
            break;
        } else {
            curr_relation.target[n] = c;
        }
    }

    fscanf(file_ptr, "%i", &curr_relation.weight);

    fscanf(file_ptr, "\n");

    return curr_relation;
}

bool comp_str(char str1[LETTERS], char str2[LETTERS]) {
    for (int i = 0; i < LETTERS; i++)
    {
        if (str1[i] != str2[i]) {
            return false;
        } else if (str1[i] == '\0' && str2[i] == '\0') {
            return true;
        }
    }
    
    return false;
}

bool contains(char str[], char names[][LETTERS], int name_count) {
    for (int i = 0; i < name_count; i++)
    {
        if (comp_str(str, names[i])) {
            return true;
        }
    }
    
    return false;
}


void add_str(char str[], char names[][LETTERS], int *name_count) {
    for (int i = 0; i < LETTERS; i++)
    {
        names[*name_count][i] = str[i];
    }

    (*name_count)++;
}

void list(char names[][LETTERS], int name_count) {
    for (int i = 0; i < name_count; i++)
    {
        printf("%i: %s\n", i, names[i]);
    }
}

int main() {
    FILE *fptr = fopen("thrones.csv", "r");

    relation relations[COUNT];

    //Read all relations to array of structs
    for (int i = 0; i < COUNT; i++)
    {
        relations[i] = read_relation(fptr);
    }

    //Output
    /* for (int i = 0; i < 353; i++)
    {
        printf(
            "%i: %s, %s, %i\n",
            i,
            relations[i].source,
            relations[i].target,
            relations[i].weight
        );
    } */

    //Put all names in array
    char names[128][LETTERS];
    int name_count = 0;

    for (int i = 0; i < COUNT; i++)
    {
        relation rel = relations[i];

        if (!contains(rel.source, names, name_count)) {
            add_str(rel.source, names, &name_count);
        }

        if (!contains(rel.target, names, name_count)) {
            add_str(rel.target, names, &name_count);
        }
    }

    //Input
    bool loop = true;

    do
    {
        clear();
        puts("Welcome to database");
        puts("(L)ist");
        puts("(R)elations");
        puts("(Q)uit");

        char input;
        scanf("%c", &input);
        input = (char)toupper(input);

        switch (input)
        {
        case 'L':
            list(names, name_count);
            puts("Press any letter + enter to continue");
            scanf(" ");
            break;
        case 'R':
            
            break;
        case 'Q':
            loop = false;
            break;
        
        default:
            break;
        }

    } while (loop);
    
    puts("adios");
    return 0;
}