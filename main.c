#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define clear() printf("\033[H\033[J")
#define LETTERS 15
#define COUNT 353

typedef struct relation {
    char source[LETTERS];
    char target[LETTERS];
    int weight;
} relation;

typedef struct target_relation {
    char person[LETTERS];
    int weight;
} target_relation;

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

bool contains(char str[], char names[][LETTERS], int name_count) {
    for (int i = 0; i < name_count; i++)
    {
        if (strcmp(str, names[i]) == 0) {
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

void set_str(char target[], char source[]) {
    for (int i = 0; i < LETTERS; i++)
    {
        target[i] = source[i];
    }
}

//Adds the alphabetically first name from original_names to sorted_names, marks the added name as empty
void add_best_name(int i, int count, char original_names[][LETTERS], char sorted_names[][LETTERS]) {
    char prev_name[LETTERS] = "@";
    if (i > 0) set_str(prev_name, sorted_names[i - 1]);

    char best_name[LETTERS] = "|bad|";
    int best_i;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(original_names[i], "-empty-") == 0) continue;
        
        if (strcmp(original_names[i], best_name) < 0) {
            set_str(best_name, original_names[i]);
            best_i = i;
        }
    }
    
    set_str(sorted_names[i], best_name);
    set_str(original_names[best_i], "-empty-");
}

void add_best_relation(int i, int count, target_relation original_rels[], target_relation sorted_rels[]) {
    int prev_weight = 256;
    if (i > 0) prev_weight = sorted_rels[i - 1].weight;

    int best_weight = -256;
    int best_i;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(original_rels[i].person, "-empty-") == 0) continue;
        
        if (original_rels[i].weight > best_weight) {
            best_weight = original_rels[i].weight;
            best_i = i;
        }
    }
    
    sorted_rels[i] = original_rels[best_i];
    set_str(original_rels[best_i].person, "-empty-");
}

void list(char names[][LETTERS], int name_count, relation relations[], bool show_rels) {
    for (int i = 0; i < name_count; i++)
    {
        printf("%i: %s\n", i, names[i]);
        if (!show_rels) continue;

        //Handle relations
        target_relation rels[64];
        int rel_count = 0;

        for (int n = 0; n < COUNT; n++)
        {
            if (strcmp(relations[n].source, names[i]) != 0) continue;

            target_relation rel;
            set_str(rel.person, relations[n].target); 
            rel.weight = relations[n].weight;

            rels[rel_count] = rel;
            rel_count++;
        }

        for (int n = 0; n < COUNT; n++)
        {
            if (strcmp(relations[n].target, names[i]) != 0) continue;

            target_relation rel;
            set_str(rel.person, relations[n].source); 
            rel.weight = relations[n].weight;

            rels[rel_count] = rel;
            rel_count++;
        }

        //Sort relations
        target_relation sorted_rels[rel_count];

        for (int i = 0; i < rel_count; i++)
        {
            add_best_relation(i, rel_count, rels, sorted_rels);
        }

        //Print relations
        for (int i = 0; i < rel_count; i++)
        {
            printf("\t%s: %i\n", sorted_rels[i].person, sorted_rels[i].weight);
        }
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

    char sorted_names[name_count][LETTERS];

    for (int i = 0; i < name_count; i++)
    {
        add_best_name(i, name_count, names, sorted_names);
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
            clear();
            list(sorted_names, name_count, relations, false);
            puts("Press any letter + enter to continue");
            scanf(" ");
            break;
        case 'R':
            clear();
            list(sorted_names, name_count, relations, true);
            puts("Press any letter + enter to continue");
            scanf(" ");
            break;
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