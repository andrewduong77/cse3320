/* Driver Program
 */
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


const char* getfield(char* line,int num)
{

	const char* tok;
	for(tok = strtok(line, ",");
		tok && *tok;
		tok = strtok(NULL, ",\n"))

	{
		if(!--num)
		return tok;
	}
	return NULL;

}

int main(void) {
time_t t;
char s[256];
int i, j,c;
pid_t p,pp;

FILE* read = fopen("months.csv","r");

	char line[1024];
	while(fgets(line, 1024, read));
	{
		char* tmp = strdup(line);
		printf(">>> %s\n", getfield(tmp,2));
		
	free(tmp);		
	}
	



     /* t = time(NULL);
printf( "Driver Time: %s\n", ctime(&t));
p = getpid();
pp  = getppid();
printf("Driver PID: %d   Driver PPID: %d \n", p, pp);
p = fork();
if (p == 0) {
/* child 
printf( "child");
execv("./u", NULL); }
if (p == 0) {
printf("Driver after fork, child: %d\n", p); 
      } else {
printf("Driver after fork, parent: %d\n", p);
}
sleep(10);
            t = time(NULL);
printf( "Driver Time again: %s\n", ctime(&t));
exit(0);*/
}
