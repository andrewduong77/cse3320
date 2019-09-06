#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
// #include <curses.h> 

void quicksort(int number[25],int first,int last);

int main(void)
{
    pid_t child;
    DIR * d;
    struct dirent * de;
    int i, c, k, dirs_count, files_count;
    char s[256], cmd[256], dirs[1024][2048], files[1024][2048]; /* fixed length buffers? */
    time_t t; 

    while (1)
    {
        t = time( NULL );
        printf( "Time: %s\n", ctime( &t ));

        getcwd(s, 200); /* why 200? What if bigger? Check for errors? */ printf( "\nCurrent Directory: %s \n", s); 

        d = opendir( "." ); /* errors? More below */
        c = 0;
        while ((de = readdir(d)))
        {
            if ((de->d_type) & DT_DIR)
            {
                strcpy(dirs[c], de->d_name);
                printf( " ( %d Directory: %s ) \n", c++, dirs[c]);
                // printf( " ( %d Directory: %s ) \n", c++, de->d_name);
            }
        }
        closedir( d );
        d = opendir( "." );
        dirs_count = c;
        c = 0;
        while ((de = readdir(d)))
        {
            if (((de->d_type) & DT_REG))
            {
                strcpy(files[c], de->d_name);
                printf( " ( %d File: %s ) \n", c++, files[c]);
                // printf( " ( %d File: %s ) \n", c++, de->d_name);
            }
            if ( ( c % 8 ) == 0 )
            {
                printf( "Hit N for Next\n" ); /* What if only subdirs? */
                k = getchar( );
            }
        }
        closedir( d );
        files_count = c;
        printf( "-----------------------------------------\n" );
        c = getchar( );
        getchar( );
        switch (c)
        {
            case 'q':
                exit(0); /* quit */
            case 'e':
                printf( "Edit what?:" );
                scanf( "%s", s );
                strcpy( cmd, "pico ");
                strcat( cmd, s );
                system( cmd ); /*this is bad, should use fork() then execv() or execl() */
                break;
            case 'r':
                printf( "Run what?:" );
                scanf( "%s", cmd );
                system( cmd );
                break;
            case 'c':
                printf( "Change To?:" );
                scanf( "%s", cmd );
                chdir( cmd ); /* what can go wrong ? */
                break;
            case 'd':
                printf( "Display what?:" );
                scanf( "%s", s );
                strcpy( cmd, "more ");
                strcat( cmd, s );
                system( cmd ); /*this is bad, should use fork() then execv() or execl() */
                break;
            case 's':
                // sort goes here
                break;
            case 't':
                printf( "Remove what?:" );
                scanf ( "%s", s );
                strcpy( cmd, "rm -r ");
                strcat( cmd, s );
                system( cmd );
                break;
            case 'm':
                // move goes here
                break;
            }
        }
    }

void quicksort(int number[25],int first,int last)
{
    int i, j, pivot, temp;
    if(first < last)
    {
        pivot = first;
        i = first;
        j = last;
        while(i < j)
        {
            while(number[i] <= number[pivot] && i<last)
                i++;
            while(number[j] > number[pivot])
                j--;
            if(i < j)
            {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }
        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;
        quicksort(number, first, j - 1);
        quicksort(number, j + 1, last);
    }
}