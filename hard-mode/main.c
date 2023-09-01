#include <stdio.h>

int main()
{
    char str[16];

    FILE *fptr = fopen("advance.json", "r");

    fscanf(fptr, "[ { \"name\": \"%s\"", str);
    printf("%s", str);
    
    return 0;
}