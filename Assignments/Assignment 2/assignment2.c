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
void printEarthquakesToScreen(Earthquake* theEarthquakes, int theEarthquakesSize)
{
    int i;
    for(i = 0; i < theEarthquakesSize; i++)
    {
        printf("%s|%f|%f|%f|%f|%s|%d|%f|%f|%f|%s|%s|%s|%s|%s|%f|%f|%f|%f|%s|%s|%s\n",
        theEarthquakes[i].time,
        theEarthquakes[i].latitude,
        theEarthquakes[i].longitude,
        theEarthquakes[i].depth,
        theEarthquakes[i].mag,
        theEarthquakes[i].magType,
        theEarthquakes[i].nst,
        theEarthquakes[i].gap,
        theEarthquakes[i].dmin,
        theEarthquakes[i].rms,
        theEarthquakes[i].net,
        theEarthquakes[i].id,
        theEarthquakes[i].updated,
        theEarthquakes[i].place,
        theEarthquakes[i].type,
        theEarthquakes[i].horizontalError,
        theEarthquakes[i].depthError,
        theEarthquakes[i].magError,
        theEarthquakes[i].magNst,
        theEarthquakes[i].status,
        theEarthquakes[i].locationSource,
        theEarthquakes[i].magSource);
    }
}
int main()
{
    int earthquakesSize = 0;
    FILE* inStream = fopen("all_month.csv", "r");
    FILE* outStream = fopen("all_month_sorted.csv", "w");
    Earthquake *earthquakes, *sortedEarthquakes;
    earthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
    sortedEarthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
    char retreive[1024], *del = ",";
    fgets(retreive, 1024, inStream);
    while (fgets(retreive, 1024, inStream))
    {
        char* buffer = strdup(retreive);
        strcpy(earthquakes[earthquakesSize].time, strsep(&buffer, del)); // char[]
        earthquakes[earthquakesSize].latitude = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].longitude = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].depth = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].mag = atof(strsep(&buffer, del)); // float
        strcpy(earthquakes[earthquakesSize].magType, strsep(&buffer, del)); // char[]
        earthquakes[earthquakesSize].nst = atof(strsep(&buffer, del)); // int
        earthquakes[earthquakesSize].gap = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].dmin = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].rms = atof(strsep(&buffer, del)); // float
        strcpy(earthquakes[earthquakesSize].net, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakesSize].id, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakesSize].updated, strsep(&buffer, del)); // char[]
        strsep(&buffer, "\"");
        strcpy(earthquakes[earthquakesSize].place, strsep(&buffer, "\"")); // char[]
        strsep(&buffer, del);
        strcpy(earthquakes[earthquakesSize].type, strsep(&buffer, del)); // char[]
        earthquakes[earthquakesSize].horizontalError = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].depthError = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].magError = atof(strsep(&buffer, del)); // float
        earthquakes[earthquakesSize].magNst = atof(strsep(&buffer, del)); // float
        strcpy(earthquakes[earthquakesSize].status, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakesSize].locationSource, strsep(&buffer, del)); // char[]
        strcpy(earthquakes[earthquakesSize].magSource, strsep(&buffer, del)); // char[]
        earthquakesSize++;
        free(buffer);
    }
    sortedEarthquakes = earthquakes;
    sortEarthquakes(sortedEarthquakes, earthquakesSize);
    printEarthquakesToScreen(sortedEarthquakes, earthquakesSize);
}
