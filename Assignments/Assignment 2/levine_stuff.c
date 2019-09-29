#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 30

typedef struct
{
   char time[100];
   float latitude;
   float longitude;
   float depth;
   float mag;
   char magType[5];
   char nst[5];
   int gap;
   float dmin;
   float rms;
   char net[5];
   char id[20];
   char updated[100];
   char place[200];
   char type[10];
   float horizontalError;
   float depthError;
   float magError;
   int magNst;
   char status[10];
   char locationSource[5];
   char magSource[5];
} earthquake_record;

//array to hold data
earthquake_record data[MAX_DAYS];

//function to read data from file
int read_file(char* filename)
{
   FILE* file = fopen(filename,"r");
   ssize_t flag;
   char* line;
   size_t sz=0;
   //check if file opened properly or not
   if(!file)
   {
       fprintf(stderr,"Unable to open or read file.\n");
       return -1;
   }
  
   //read file line by line
   getline(&line,&sz,file);
   int i=0;
   while((flag=getline(&line,&sz,file))!=-1)
   {
       char* token;
       token = strtok(line,",");
       strcpy(data[i].time,token);
       token = strtok(NULL,",");
       data[i].latitude = atof(token);
       token = strtok(NULL,",");
       data[i].longitude = atof(token);
       token = strtok(NULL,",");
       data[i].depth = atof(token);
       token = strtok(NULL,",");
       data[i].mag = atof(token);
       token = strtok(NULL,",");
       strcpy(data[i].magType,token);
       token = strtok(NULL,",");
       strcpy(data[i].nst,token);
       token = strtok(NULL,",");  
       data[i].gap = atoi(token);
       token = strtok(NULL,",");  
       data[i].dmin=atof(token);
       token = strtok(NULL,",");  
       data[i].rms=atof(token);
       token = strtok(NULL,",");  
       strcpy(data[i].net,token);
       token = strtok(NULL,",");  
       strcpy(data[i].id,token);
       token = strtok(NULL,",");  
       strcpy(data[i].updated,token);
       token = strtok(NULL,",");  
       strcpy(data[i].place,token);
       token = strtok(NULL,",");  
       strcpy(data[i].type,token);
       token = strtok(NULL,",");  
       data[i].horizontalError=atof(token);
       token = strtok(NULL,",");  
       data[i].depthError=atof(token);
       token = strtok(NULL,",");  
       data[i].magError=atof(token);
       token = strtok(NULL,",");  
       data[i].magNst=atoi(token);
       token = strtok(NULL,",");  
       strcpy(data[i].status,token);
       token = strtok(NULL,",");  
       strcpy(data[i].locationSource,token);
       token = strtok(NULL,",");  
       strcpy(data[i].magSource,token);
       if(i==MAX_DAYS)
           break;
       i++;
   }
   return 1;
}

//function to sort data based on latitude
void bubble_sort()
{
   int i, j;
   earthquake_record rec;
   for (i = 0; i < MAX_DAYS-1; i++)
   {
       for (j = 0; j < MAX_DAYS-i-1; j++)
       {
       if (data[j].latitude > data[j+1].latitude)
       {
           rec=data[j];
           data[j]=data[j+1];
           data[j+1]=rec;              
       }            
       }
   }         
}

//main function
int main()
{
   char* csv_filename = "./4.5_month.csv";  
   read_file(csv_filename);      
   bubble_sort();
   return EXIT_SUCCESS;
}