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
void swap(Earthquake* a, Earthquake* b)
{
    Earthquake* tmp;
    *tmp = *a;
    *a = *b;
    *b = *tmp;
}
void sortEarthquakes(Earthquake* theEarthquakes, int theEarthquakesSize)
{
    int i, j;
    for(i = 0; i < theEarthquakesSize; i++)
        for(j = i; j < theEarthquakesSize; j++)
            if(theEarthquakes[j].latitude < theEarthquakes[i].latitude)
                swap(&theEarthquakes[j], &theEarthquakes[i]);
}
int main()
{
    int earthquakes_size = 0;
    FILE* stream = fopen("all_month.csv", "r");
    Earthquake *earthquakes, *sortedEarthquakes;
    earthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
    sortedEarthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
    char retreive[1024], *del = ",";
    fgets(retreive, 1024, stream);
    while (fgets(retreive, 1024, stream))
    {
        char* buffer = strdup(retreive);
        strcpy(earthquakes[earthquakes_size].time, strsep(&buffer, del)); // char[]
        earthquakes[earthquakes_size].latitude = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].longitude = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].depth = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].mag = atof(strsep(&buffer, del)); // float
        strcpy(earthquakes[earthquakes_size].magType, strsep(&buffer, del)); // char[]
        earthquakes[earthquakes_size].nst = atof(strsep(&buffer, del)); // int
        earthquakes[earthquakes_size].gap = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].dmin = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].rms = atof(strsep(&buffer, del)); // float
        strcpy(earthquakes[earthquakes_size].net, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakes_size].id, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakes_size].updated, strsep(&buffer, del)); // char[]
        strsep(&buffer, "\"");
        strcpy(earthquakes[earthquakes_size].place, strsep(&buffer, "\"")); // char[]
        strsep(&buffer, del);
        strcpy(earthquakes[earthquakes_size].type, strsep(&buffer, del)); // char[]
        earthquakes[earthquakes_size].horizontalError = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].depthError = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].magError = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakes_size].magNst = atof(strsep(&buffer, del)); // float
        strcpy(earthquakes[earthquakes_size].status, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakes_size].locationSource, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakes_size].magSource, strsep(&buffer, del)); // char[]
        earthquakes_size++;
        free(buffer);
    }
    int i;
    sortedEarthquakes = earthquakes;
    sortEarthquakes(sortedEarthquakes, earthquakes_size);
    for(i = 0; i < earthquakes_size; i++)
    {
        printf("%s|%f|%f|%f|%f|%s|%d|%f|%f|%f|%s|%s|%s|%s|%s|%f|%f|%f|%f|%s|%s|%s\n",
        sortedEarthquakes[i].time,
        sortedEarthquakes[i].latitude,
        sortedEarthquakes[i].longitude,
        sortedEarthquakes[i].depth,
        sortedEarthquakes[i].mag,
        sortedEarthquakes[i].magType,
        sortedEarthquakes[i].nst,
        sortedEarthquakes[i].gap,
        sortedEarthquakes[i].dmin,
        sortedEarthquakes[i].rms,
        sortedEarthquakes[i].net,
        sortedEarthquakes[i].id,
        sortedEarthquakes[i].updated,
        sortedEarthquakes[i].place,
        sortedEarthquakes[i].type,
        sortedEarthquakes[i].horizontalError,
        sortedEarthquakes[i].depthError,
        sortedEarthquakes[i].magError,
        sortedEarthquakes[i].magNst,
        sortedEarthquakes[i].status,
        sortedEarthquakes[i].locationSource,
        sortedEarthquakes[i].magSource);
    }
}
