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
    int earthquakesSize = 0, i, j;
    FILE* inStream = fopen("all_month.csv", "r"), * outStream = fopen("all_month_sorted.csv", "w");
    Earthquake *earthquakes, tmp;
    earthquakes = (Earthquake*)malloc(20000*sizeof(Earthquake));
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
    for(i = 0; i < earthquakesSize; i++) {
        for(j = i; j < earthquakesSize; j++) {
            if(earthquakes[j].latitude < earthquakes[i].latitude) {
                tmp = earthquakes[j];
                earthquakes[j] = earthquakes[i];
                earthquakes[i] = tmp;
            }
        }
    }
    printf("%s", earthquakes[0].time);
    for(i = 0; i < earthquakesSize; i++) {
        printf("|%f|%f|%f|%f|%s|%d|%f|%f|%f|%s|%s|%s|%s|%s|%f|%f|%f|%f|%s|%s|%s",
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
    fprintf(outStream, "time,latitude,longitude,depth,mag,magType,nst,gap,dmin,rms,net,id,updated,place,type,horizontalError,depthError,magError,magNst,status,locationSource,magSource\n");
    fprintf(outStream, "%s", earthquakes[0].time);
    for(i = 0; i < earthquakesSize; i++)
    {
        fprintf(outStream, ",%f,%f,%f,%f,%s,%d,%f,%f,%f,%s,%s,%s,%s,%s,%f,%f,%f,%f,%s,%s,%s",
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
}
