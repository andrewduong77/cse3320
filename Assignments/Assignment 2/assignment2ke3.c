#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct eq_data {
    char time[27];
    float latitude;
    float longitude;
    float depth;
    float mag;
    char magType[5];
    int nst;
    float gap;
    float dmin;
    float rms;
    char net[5];
    char id[17];
    char updated[27];
    char place[77];
    char type[13];
    float horizontalError; 
    float depthError;
    float magError;
    float magNst;
    char status[12];
    char locationSource[5];
    char magSource[5];
};

int main() {

    int sz = 0, i, j;
    FILE* input_stream = fopen("all_month.csv", "r"), * output_stream = fopen("all_month_sorted.csv", "w");
    struct eq_data *eq_datas, tmp;
    eq_datas = (struct eq_data*)malloc(20000*sizeof(struct eq_data));
    char ret[1024];

    fgets(ret, 1024, input_stream);

    while (fgets(ret, 1024, input_stream)) {
        char* buf = strdup(ret);
        strcpy(eq_datas[sz].time, strsep(&buf, ",")); // char[]
        eq_datas[sz].latitude = atof(strsep(&buf, ",")); // float
        eq_datas[sz].longitude = atof(strsep(&buf, ",")); // float
        eq_datas[sz].depth = atof(strsep(&buf, ",")); // float
        eq_datas[sz].mag = atof(strsep(&buf, ",")); // float
        strcpy(eq_datas[sz].magType, strsep(&buf, ",")); // char[]
        eq_datas[sz].nst = atof(strsep(&buf, ",")); // int
        eq_datas[sz].gap = atof(strsep(&buf, ",")); // float
        eq_datas[sz].dmin = atof(strsep(&buf, ",")); // float
        eq_datas[sz].rms = atof(strsep(&buf, ",")); // float
        strcpy(eq_datas[sz].net, strsep(&buf, ",")); // char[]
        strcpy(eq_datas[sz].id, strsep(&buf, ",")); // char[]
        strcpy(eq_datas[sz].updated, strsep(&buf, ",")); // char[]
        strsep(&buf, "\"");
        strcpy(eq_datas[sz].place, strsep(&buf, "\"")); // char[]
        strsep(&buf, ",");
        strcpy(eq_datas[sz].type, strsep(&buf, ",")); // char[]
        eq_datas[sz].horizontalError = atof(strsep(&buf, ",")); // float
        eq_datas[sz].depthError = atof(strsep(&buf, ",")); // float
        eq_datas[sz].magError = atof(strsep(&buf, ",")); // float
        eq_datas[sz].magNst = atof(strsep(&buf, ",")); // float
        strcpy(eq_datas[sz].status, strsep(&buf, ",")); // char[]
        strcpy(eq_datas[sz].locationSource, strsep(&buf, ",")); // char[]
        strcpy(eq_datas[sz].magSource, strsep(&buf, ",")); // char[]
        sz++;
        free(buf);
    }

    for(i = 0; i < sz; i++) {
        for(j = i; j < sz; j++) {
            if(eq_datas[j].latitude < eq_datas[i].latitude) {
                tmp = eq_datas[j];
                eq_datas[j] = eq_datas[i];
                eq_datas[i] = tmp;
            }
        }
    }

    for(i = 0; i < sz; i++) {
        printf("%s,%f,%f,%f,%f,%s,%d,%f,%f,%f,%s,%s,%s,%s,%s,%f,%f,%f,%f,%s,%s,%s",
        eq_datas[i].time,
        eq_datas[i].latitude,
        eq_datas[i].longitude,
        eq_datas[i].depth,
        eq_datas[i].mag,
        eq_datas[i].magType,
        eq_datas[i].nst,
        eq_datas[i].gap,
        eq_datas[i].dmin,
        eq_datas[i].rms,
        eq_datas[i].net,
        eq_datas[i].id,
        eq_datas[i].updated,
        eq_datas[i].place,
        eq_datas[i].type,
        eq_datas[i].horizontalError,
        eq_datas[i].depthError,
        eq_datas[i].magError,
        eq_datas[i].magNst,
        eq_datas[i].status,
        eq_datas[i].locationSource,
        eq_datas[i].magSource);
    }

    fprintf(output_stream, "time,latitude,longitude,depth,mag,magType,nst,gap,dmin,rms,net,id,updated,place,type,horizontalError,depthError,magError,magNst,status,locationSource,magSource\n");

    for(i = 0; i < sz; i++) {
        fprintf(output_stream, "%s,%f,%f,%f,%f,%s,%d,%f,%f,%f,%s,%s,%s,\"%s\",%s,%f,%f,%f,%f,%s,%s,%s",
        eq_datas[i].time,
        eq_datas[i].latitude,
        eq_datas[i].longitude,
        eq_datas[i].depth,
        eq_datas[i].mag,
        eq_datas[i].magType,
        eq_datas[i].nst,
        eq_datas[i].gap,
        eq_datas[i].dmin,
        eq_datas[i].rms,
        eq_datas[i].net,
        eq_datas[i].id,
        eq_datas[i].updated,
        eq_datas[i].place,
        eq_datas[i].type,
        eq_datas[i].horizontalError,
        eq_datas[i].depthError,
        eq_datas[i].magError,
        eq_datas[i].magNst,
        eq_datas[i].status,
        eq_datas[i].locationSource,
        eq_datas[i].magSource);
    }

    return 0;
}
