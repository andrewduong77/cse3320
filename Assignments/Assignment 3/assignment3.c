#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void error(char * message1, char * message2)
{
    fprintf(stderr, "Error: %s ", message1);
    perror(message2);
    exit(1);
}
int make_stat(char *filename)
{
    struct stat fileinfo;
    if(stat(filename, &fileinfo) >= 0)
        if(S_ISREG(fileinfo.st_mode))
            return 1;
    return 0;
}
int files_copy(char * source, char * destination)
{
    int input_directory, output_directory, count;
    char buffer[512];
    if((input_directory = open(source, O_RDONLY)) == -1)
        error("Cannot open ", source);
    if((output_directory = creat(destination, 512)) == -1)
        error("Cannot creat ", destination);
    while ((count = read(input_directory, buffer, 512)) > 0)
    {
        if(write(output_directory, buffer, count) != count)
            error("Write error to ", destination);
        if(count == -1)
            error("Read error from ", source);
    }
    if(close(input_directory) == -1 || close(output_directory) == -1)
        error("Error closing files", "");
    return 1;
}
int directory_copy(char * source, char * destination)
{
    DIR * dir = NULL;
    struct dirent * dirent_my;
    char temp_destination[strlen(destination) + 1];
    char temp_source[strlen(source) + 1];
    strcat(destination, "/");
    strcat(source, "/");
    strcpy(temp_destination, destination);
    strcpy(temp_source, source);
    if((dir = opendir(source)) == NULL)
    {
        fprintf(stderr, "cp1: cannot open %s for copying\n", source);
        return 0;
    }
    else
    {
        while((dirent_my = readdir(dir)))
            if(make_stat(dirent_my->d_name))
            {
                strcat(temp_destination, dirent_my->d_name);
                strcat(temp_source, dirent_my->d_name);
                files_copy(temp_source, temp_destination);
                strcpy(temp_destination, destination);
                strcpy(temp_source, source);
            }
        closedir(dir);
        return 1;
    }
}
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    }
    char * source = argv[0];
    char * destination = argv[1];
    if(source[0] != '/' && destination[0] != '/')
        files_copy(source, destination);
    else if(source[0] != '/' && destination[0] == '/')
    {
        int i;
        for (i = 1; i <= strlen(destination); i++)
            destination[(i - 1)] = destination[i];
        strcat(destination, "/");
        strcat(destination, source);
        files_copy(source, destination);
    }
    else if(source[0] == '/' && destination[0] == '/')
    {
        int i;
        for(i = 1; i <= strlen(destination); i++)
            destination[(i - 1)] = destination[i];
        for(i = 1; i <= strlen(source); i++)
            source[(i - 1)] = source[i];
        directory_copy(source, destination);
    }
    else
    {
        fprintf(stderr, "usage: cp1 source destination\n");
        exit(1);
    }
}