#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
// #include <curses.h> 

int main(void)
{
    pid_t child;
    DIR * d;
    struct dirent * de;
    int i, c, k;
    char s[256], cmd[256]; /* fixed length buffers? */
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
                printf( " ( %d Directory: %s ) \n", c++, de->d_name);
        }
        closedir( d );
        d = opendir( "." );
        c = 0;
        while ((de = readdir(d)))
        {
            if (((de->d_type) & DT_REG))
                printf( " ( %d File: %s ) \n", c++, de->d_name);
            if ( ( c % 8 ) == 0 )
            {
                printf( "Hit N for Next\n" ); /* What if only subdirs? */
                k = getchar( );
            }
        }
        closedir( d );
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
            }
        }
    }