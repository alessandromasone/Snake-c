#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define LOG_FILE "log/log.snake"

int ExistFile(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else  
        return 0;
}

int RowTxt(char *name)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int n = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1)
        n++;
    fclose(fp);
    if (line)
        free(line);
    return n;
}

void RowPrint(char *name, int row)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int n = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1)
		if (row == n++)
			fputs(line, stdout);
    fclose(fp);
    if (line)
        free(line);
    return;
}

int main(int argc, char const *argv[])
{
	int old_row = RowTxt(LOG_FILE);
	int row = RowTxt(LOG_FILE);
	int i = row;
	do
	{
		row = RowTxt(LOG_FILE);
		if (row != old_row)
		{
			old_row = row;
			RowPrint(LOG_FILE, i++);
		}	
	} while (ExistFile("log.dll"));
	return 0;
}