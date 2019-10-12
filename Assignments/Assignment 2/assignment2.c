#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct earthquake
{
    char time[25]; // 24+1 for newline character
    float latitude;
    float longitude;
    float depth;
    float mag;
    char magType;
    int nst;
    float gap;
    float dmin;
    float rms;
    char net[3]; // 2+1 for newline character
    char id[15];
    char updated[25]; // 24+1 for newline character
    char place[75];
    char type[11]; // 10+1 for newline character
    float horizontalError; 
    float depthError;
    float magError;
    float magNst;
    char status[10]; // 9+1 for newline character
    char locationSource[3]; // 2+1 for newline character
    char magSource[3]; // 2+1 for newline character
}Earthquake;

const char* getField(char* line, int num)
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
    int earthquakes_size = 0;
    FILE* stream = fopen("all_month.csv", "r");
    Earthquake *earthquakes;
    // int n = 20000; // size of earthquakes data
    earthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        // char* tmp = strdup(line);
        char* tmp;
        tmp = (char*)malloc(1024*sizeof(char));
        strcpy(tmp, line);
        printf("%d would be %s\n", earthquakes_size++, getField(tmp, 2));
        earthquakes[earthquakes_size].time = getField(tmp, 1);
        earthquakes[earthquakes_size].longitude = getField(tmp, 2);
        earthquakes[earthquakes_size].latitude = getField(tmp, 3);
        earthquakes[earthquakes_size].depth = getField(tmp, 4);
        earthquakes[earthquakes_size].mag = getField(tmp, 5);
        earthquakes[earthquakes_size].magType = getField(tmp, 6);
        earthquakes[earthquakes_size].nst = getField(tmp, 7);
        earthquakes[earthquakes_size].gap = getField(tmp, 8);
        earthquakes[earthquakes_size].dmin = getField(tmp, 9);
        earthquakes[earthquakes_size].rms = getField(tmp, 10);
        earthquakes[earthquakes_size].net = getField(tmp, 11);
        earthquakes[earthquakes_size].id = getField(tmp, 12);
        earthquakes[earthquakes_size].updated = getField(tmp, 13);
        earthquakes[earthquakes_size].place = getField(tmp, 14);
        earthquakes[earthquakes_size].type = getField(tmp, 15);
        earthquakes[earthquakes_size].horizontalError = getField(tmp, 16);
        earthquakes[earthquakes_size].depthError = getField(tmp, 17);
        earthquakes[earthquakes_size].magError = getField(tmp, 18);
        earthquakes[earthquakes_size].magNst = getField(tmp, 19);
        earthquakes[earthquakes_size].status = getField(tmp, 20);
        earthquakes[earthquakes_size].locationSource = getField(tmp, 21);
        earthquakes[earthquakes_size].magSource = getField(tmp, 22);
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    earthquakes = (Earthquake*)realloc(earthquakes_size*sizeof(Earthquake));
}
