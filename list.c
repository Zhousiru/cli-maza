#ifndef LIST_C
#define LIST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[20];
    int mode;
    int time;
} Record;

void getList()
{
    FILE *fp;
    char line[200];

    fp = fopen("list.txt", "r");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        Record *r = malloc(sizeof(Record));
        strcpy(r->name, strtok(line, ","));
        r->mode = aoti(strtok(NULL, ","));
        r->time = aoti(strtok(NULL, ","));
    }
}

#endif
