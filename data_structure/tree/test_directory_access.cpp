// test access file/directory name and check file or directory

// gcc -g -O0 test_directory_access.cpp -o test_directory_access.out

// ./test_directory_access.out ../
// list path ../:
// name:tree directory
// name:stack directory
// name:queue directory
// name:list directory
// name:array directory

// ./test_directory_access.out ./
// list path ./:
// name:test_directory_access.out file
// name:test_directory_access.cpp file

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// check file or directory
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// check directory elements
#include <dirent.h>

char* concat(char* s1, char* s2)
{
    char* s = (char*)malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(s, s1);
    strcat(s, s2);
    return s;
}

int is_directory(char* path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
    {
        return -1;
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        return 1;
    }

    return 0;
}

void read_dir(char* path)
{
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
        exit (1);
    }

    while (n--)
    {
        // print the file or directory without "." and "../"
        if (strcmp(namelist[n]->d_name, ".") && strcmp(namelist[n]->d_name, ".."))
        {
            // check file or directory
            char* full_path = concat(path, namelist[n]->d_name);
            // printf("full path name: %s\n", full_path);
            int is_dir = is_directory(full_path);
            printf("name:%s %s\n", namelist[n]->d_name, ((is_dir == 1) ? "directory" : "file"));
        }
        free(namelist[n]);
    }
    free(namelist);
}

int main(int argc, char *argv[])
{
    char* path;

    if (argc < 2)
    {
        path = strdup("./");
    }
    else
    {
        path = strdup(argv[1]);
    }
    printf("list path %s:\n", path);

    // access the root path
    read_dir(path);

    free(path);

    return 0;
}
