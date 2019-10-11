#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct earthquake
{
    
};

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int main()
{
    int a = 1;
    FILE* stream = fopen("all_month.csv", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        printf("%d would be %s\n", a++, getfield(tmp, 2));
        // NOTE strtok clobbers tmp
	
        free(tmp);
        // a++;
    }
}
