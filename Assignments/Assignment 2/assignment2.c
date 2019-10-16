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
void earthquakesCopy(Earthquake* a, Earthquake* b, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        strcpy(a[i].time, b[i].time);
        a[i].latitude = b[i].latitude;
        a[i].longitude = b[i].longitude;
        a[i].depth = b[i].depth;
        a[i].mag = b[i].mag;
        strcpy(a[i].magType, b[i].magType);
        a[i].nst = b[i].nst;
        a[i].gap = b[i].gap;
        a[i].dmin = b[i].dmin;
        a[i].rms = b[i].rms;
        strcpy(a[i].net, b[i].net);
        strcpy(a[i].id, b[i].id);
        strcpy(a[i].updated, b[i].updated);
        strcpy(a[i].place, b[i].place);
        strcpy(a[i].type, b[i].type);
        a[i].horizontalError = b[i].horizontalError;
        a[i].depthError = b[i].depthError;
        a[i].magError = b[i].magError;
        a[i].magNst = b[i].magNst;
        strcpy(a[i].status, b[i].status);
        strcpy(a[i].locationSource, b[i].locationSource);
        strcpy(a[i].magSource, b[i].magSource);
    }
}
void earthquakesSwap(Earthquake* a, Earthquake* b)
{
    Earthquake* tmp;
    *tmp = *a;
    *a = *b;
    *b = *tmp;
}
void earthquakesSort(Earthquake* theEarthquakes, int theEarthquakesSize)
{
    int i, j;
    for(i = 0; i < theEarthquakesSize; i++)
        for(j = i; j < theEarthquakesSize; j++)
            if(theEarthquakes[j].latitude < theEarthquakes[i].latitude)
                earthquakesSwap(&theEarthquakes[j], &theEarthquakes[i]);
}
void printEarthquakesToScreen(Earthquake* theEarthquakes, int theEarthquakesSize)
{
    int i;
    for(i = 0; i < theEarthquakesSize; i++)
    {
        printf("%s|%f|%f|%f|%f|%s|%d|%f|%f|%f|%s|%s|%s|%s|%s|%f|%f|%f|%f|%s|%s|%s",
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
void printEarthquakesToFile(Earthquake* theEarthquakes, int theEarthquakesSize)
{
    FILE* outStream = fopen("all_month_sorted.csv", "w");
    int i;
    fprintf(outStream, "time,latitude,longitude,depth,mag,magType,nst,gap,dmin,rms,net,id,updated,place,type,horizontalError,depthError,magError,magNst,status,locationSource,magSource\n");
    for(i = 0; i < theEarthquakesSize; i++)
    {
        fprintf(outStream, "%s,%f,%f,%f,%f,%s,%d,%f,%f,%f,%s,%s,%s,%s,%s,%f,%f,%f,%f,%s,%s,%s",
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
    Earthquake *earthquakes, *earthquakesSorted;
    earthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
    earthquakesSorted = (Earthquake*)malloc(20000*sizeof(Earthquake));
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
    earthquakesCopy(earthquakesSorted, earthquakes, earthquakesSize);
    earthquakesSort(earthquakesSorted, earthquakesSize);
    printEarthquakesToScreen(earthquakesSorted, earthquakesSize);
    // printEarthquakesToFile(earthquakesSorted, earthquakesSize);
}
