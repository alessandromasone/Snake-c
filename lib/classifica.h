#ifndef _SNAKECLASSIFICA_H_
#define _SNAKECLASSIFICA_H_

int ClassificaMenu()
{
    clear();
    MainClassifica();
    getch();
    clear();
    return 0;
}

int MainClassifica()
{
    bool exit = true;
    PrintClassifica();
    return 0;
}

/* Stampa a video della classifica con fetch dal file txt attraverso un parser della riga */
int PrintClassifica()
{
    char s[WORD] = {};
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int init_size = 0;
    char *ptr;
    int x;
    fp = fopen(CLASSIFICA_FILE, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    PrintMiddle("Press a button to go back", columns, &y, 1);
    PrintBanner(LOGO_FILE, columns, &y);
    while ((read = getline(&line, &len, fp)) != -1)
    {
        init_size = strlen(line);
        ptr = strtok(line, ";");
        while (ptr != NULL)
        {
            strcpy(s, ptr);
            PrintMiddle(ptr, columns, &y, 1);
            ptr = strtok(NULL, ";");
            
        }
        x = strlen(s);
        gotoxy(((columns/2) - (x/2))-4, y-2);
        printf(" o__");
        gotoxy(((columns/2) - (x/2))-4, y-1);
        printf("<|");
        gotoxy(((columns/2) - (x/2))-4, y);
        printf("/ \\");
        gotoxy((columns/2)+(x/2), y-2);
        printf("__o");
        gotoxy((columns/2)+(x/2)+1, y-1);
        printf(" |>");
        gotoxy((columns/2)+(x/2)+1, y);
        printf("/ \\");
        y++;
    }
    fclose(fp);
    return 0;
}

#endif