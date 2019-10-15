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
int main()
{
    int earthquakes_size = 0;
    FILE* stream = fopen("all_month.csv", "r");
    Earthquake *earthquakes;
    earthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
    char retreive[1024], *del = ",";
    fgets(retreive, 1024, stream);
    while (fgets(retreive, 1024, stream))
    {
        char* buffer = strdup(retreive);
        strcpy(earthquakes[earthquakes_size].time, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].time);
        earthquakes[earthquakes_size].latitude = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].latitude);
        earthquakes[earthquakes_size].longitude = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].longitude);
        earthquakes[earthquakes_size].depth = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].depth);
        earthquakes[earthquakes_size].mag = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].mag);
        strcpy(earthquakes[earthquakes_size].magType, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].magType);
        earthquakes[earthquakes_size].nst = atof(strsep(&buffer, del)); // int
        // printf("%d|", earthquakes[earthquakes_size].nst);
        earthquakes[earthquakes_size].gap = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].gap);
        earthquakes[earthquakes_size].dmin = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].dmin);
        earthquakes[earthquakes_size].rms = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].rms);
        strcpy(earthquakes[earthquakes_size].net, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].net);
        strcpy(earthquakes[earthquakes_size].id, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].id);
        strcpy(earthquakes[earthquakes_size].updated, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].updated);
        strsep(&buffer, "\"");
        strcpy(earthquakes[earthquakes_size].place, strsep(&buffer, "\"")); // char[]
        // printf("%s|", earthquakes[earthquakes_size].place);
        strsep(&buffer, del);
        strcpy(earthquakes[earthquakes_size].type, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].type);
        earthquakes[earthquakes_size].horizontalError = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].horizontalError);
        earthquakes[earthquakes_size].depthError = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].depthError);
        earthquakes[earthquakes_size].magError = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].magError);
        earthquakes[earthquakes_size].magNst = atof(strsep(&buffer, del)); // float
        // printf("%f|", earthquakes[earthquakes_size].magNst);
        strcpy(earthquakes[earthquakes_size].status, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].status);
        strcpy(earthquakes[earthquakes_size].locationSource, strsep(&buffer, del)); // char[]
        // printf("%s|", earthquakes[earthquakes_size].locationSource);
        strcpy(earthquakes[earthquakes_size].magSource, strsep(&buffer, del)); // char[]
        // printf("%s", earthquakes[earthquakes_size].magSource);
        earthquakes_size++;
        free(buffer);
    }
    int i;
    for(i = 0; i < earthquakes_size; i++)
    {
        printf("%s|%f|%f|%f|%f|%s|%d|%f|%f|%f|%s|%s|%s|%s|%s|%f|%f|%f|%f|%s|%s|%s\n",
        earthquakes[i].time,
        earthquakes[i].latitude,
        earthquakes[i].longitude,
        earthquakes[i].depth,
        earthquakes[i].mag,
        earthquakes[i].magType,
        earthquakes[i].nst,
        earthquakes[i].gap,
        earthquakes[i].dmin,
        earthquakes[i].rms,
        earthquakes[i].net,
        earthquakes[i].id,
        earthquakes[i].updated,
        earthquakes[i].place,
        earthquakes[i].type,
        earthquakes[i].horizontalError,
        earthquakes[i].depthError,
        earthquakes[i].magError,
        earthquakes[i].magNst,
        earthquakes[i].status,
        earthquakes[i].locationSource,
        earthquakes[i].magSource);
    }
    // earthquakes = (Earthquake*)realloc(earthquakes_size*sizeof(Earthquake));
}
