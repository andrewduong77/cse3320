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
    char magType[3]; // 2+1 for newline character
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

    char buffer[1024], sink[1024], *del = ",";
    while (fgets(buffer, 1024, stream))
    {
        // char* tmp = strdup(line);
        char* tmp;
        tmp = (char*)malloc(1024*sizeof(char));
        strcpy(tmp, buffer);
        // printf("%d would be %s\n", earthquakes_size++, getField(tmp, 2));

        strcpy(earthquakes[earthquakes_size].time, strtok(buffer, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].time);
        earthquakes[earthquakes_size].latitude = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].latitude);
        earthquakes[earthquakes_size].longitude = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].longitude);
        earthquakes[earthquakes_size].depth = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].depth);
        earthquakes[earthquakes_size].mag = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].mag);
        strcpy(earthquakes[earthquakes_size].magType, strtok(NULL, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].magType);
        earthquakes[earthquakes_size].nst = atof(strtok(NULL, del)); // int
        printf("%d|", earthquakes[earthquakes_size].nst);
        earthquakes[earthquakes_size].gap = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].gap);
        earthquakes[earthquakes_size].dmin = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].dmin);
        earthquakes[earthquakes_size].rms = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].rms);
        strcpy(earthquakes[earthquakes_size].net, strtok(NULL, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].net);
        strcpy(earthquakes[earthquakes_size].id, strtok(NULL, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].id);
        strcpy(earthquakes[earthquakes_size].updated, strtok(NULL, del)); // char[]
        // Could not use "\"" as delimiters
        strtok(NULL, "\"");
        printf("%s|", earthquakes[earthquakes_size].updated);
        strcpy(earthquakes[earthquakes_size].place, strtok(NULL, "\"")); // char[]
        strtok(NULL, del);
        printf("%s|", earthquakes[earthquakes_size].place);
        strcpy(earthquakes[earthquakes_size].type, strtok(NULL, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].type);
        earthquakes[earthquakes_size].horizontalError = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].horizontalError);
        earthquakes[earthquakes_size].depthError = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].depthError);
        earthquakes[earthquakes_size].magError = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].magError);
        earthquakes[earthquakes_size].magNst = atof(strtok(NULL, del)); // float
        printf("%f|", earthquakes[earthquakes_size].magNst);
        strcpy(earthquakes[earthquakes_size].status, strtok(NULL, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].status);
        strcpy(earthquakes[earthquakes_size].locationSource, strtok(NULL, del)); // char[]
        printf("%s|", earthquakes[earthquakes_size].locationSource);
        strcpy(earthquakes[earthquakes_size].magSource, strtok(NULL, del)); // char[]
        printf("%s\n", earthquakes[earthquakes_size].magSource);
        // str(NULL, del) triggers "Segmentation fault"
        earthquakes_size++;
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    // int i;
    // for(i = 0; i < earthquakes_size; i++)
    // {
    //     printf("%s %f %f %f %f %s %d %f %f %f %s %s %s %s %s %f %f %f %f %s %s %s\n",
    //     earthquakes[i].time,
    //     earthquakes[i].latitude,
    //     earthquakes[i].longitude,
    //     earthquakes[i].depth,
    //     earthquakes[i].mag,
    //     earthquakes[i].magType,
    //     earthquakes[i].nst,
    //     earthquakes[i].gap,
    //     earthquakes[i].dmin,
    //     earthquakes[i].rms,
    //     earthquakes[i].net,
    //     earthquakes[i].id,
    //     earthquakes[i].updated,
    //     earthquakes[i].place,
    //     earthquakes[i].type,
    //     earthquakes[i].horizontalError,
    //     earthquakes[i].depthError,
    //     earthquakes[i].magError,
    //     earthquakes[i].magNst,
    //     earthquakes[i].status,
    //     earthquakes[i].locationSource,
    //     earthquakes[i].magSource);
    // }
    // earthquakes = (Earthquake*)realloc(earthquakes_size*sizeof(Earthquake));
}
