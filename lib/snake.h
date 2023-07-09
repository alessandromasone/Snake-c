#ifndef _SNAKESNAKE_H_
#define _SNAKESNAKE_H_

/* Assegnazione funzione clear in base al sistema operativa */
#ifdef WIN32
#define clear() (system("cls"))
#else                          
#define clear() (system("clear"))
#endif
/* WriteLog(Nome del file, stringa da scrivere sul file passato)*/
int WriteLog(char *name, char *string);
/* SetFullscreen() */
int FullScreen();
/* DisplayDimension(Assengna le colonne, Assegna le righe, reset vecchie colonne con le nuove, reset vecchie righe con le nuove, true = stampa false = no stampa) */
int DisplayDimension(int *columns, int *rows, int *old_columns, int *old_rows, bool x);
/* MusicPlayer(Nome del file musica, true = riproduci false = stop, true = loop false = single) */
int MusicPlayer(char *name, bool x, bool loop);
/* mvprint(coordinate x, coordinate y, stringa da stampare) */
int mvprint(int x, int y, char *string);
/* gotoxy(coordinate x, coordinate y) */
int gotoxy (short x, short y);
/* Hidecursor() */
int Hidecursor();
/* Responsitive(colonne del display, righe del display, vecchie colonne, vecchie righe, numero per breakpoint medio, numero breakpoint piccolo, true = stampa coordinate false = non stampa le coordinate) */
int Responsitive(int *columns, int *rows, int *old_columns, int *old_rows, int tablet, int mobile, bool x);
/* PrintBanner(File da cui prendere il banner, colonne del display, y che incrementano) */
int PrintBanner(char *file, int columns, int *y);
/* PrintMiddle(Stringa da stampare, colonne del display, y da incrementare, n di quanto incrementare la y prima della stampa) */
int PrintMiddle(char *name, int columns, int *y, int n);
/* PrintRowMenu(Numeno della scelta attuale del menu, scelte total del menu, stringa da stampare nel menu, colonne del display, y da incrementare, n di quanto incrementare la y prima della stampa) */
int PrintRowMenu(int *choice, int *CHOICE, char *stringa, int columns, int *y, int n);
/* PrintHorizontalChoice_FILE(Nome del file da cui prendere le scelte, colonne del display, y da incrementare di 1, scelta del menu orizzontale, nome della scelta, valore della scelta attuale, token del separatore di valori nel file passato, true = stampa false = non stampa) */
int PrintHorizontalChoice_FILE(char *name, int columns, int *y, int *choice, char *name_choice, int *value, char delim[], bool stampa);
/* RangeverticalMenu(Tasto premuto, numero di scelta, scelte massime) */
int RangeverticalMenu(int c, int *choice, int max);
/* ArrowUpMenu(Scelta del menu, massime scelte) */
int ArrowUpMenu(int *choice, int max);
/* ArrowDownMenu(Scelta del menu, massime scelte) */
int ArrowDownMenu(int *choice, int max);
/* ArrowLeftMenu(Scelta del menu, massime scelte) */
int ArrowLeftMenu(int *choice, int max);
/* ArrowRightMenu(Scelta del menu, massime scelte) */
int ArrowRightMenu(int *choice, int max);
/* RowFileTxt(Nome del file) */
int RowFileTxt(char *name);
/* PrintHorizontalChoiceLock_FILE(Nome del file, colonne del display, y da incrementare di 1, scelta del menu orizzontale, valori da asccociare ai valori contenuti nel file, ... , token separatore nel file txt, punti attuali del player, true = stampa false = non stampa) */
bool PrintHorizontalChoiceLock_FILE(char *name, int columns, int *y, int *choice, int *value1, int *value2, int *value3, int *value4, int *value5, int *value6, char delim[], int points, bool stampa);
/* file_exists(Nome del file) */
bool file_exists(char *filename);
/* PrintHorizontalChoiceWithColor_FILE(Nome del file, colonne del display, y da incrementare di 1, scelta attuale, nome della scelta, valore della scelta, token di separazione nel file txt, true = stampa false = non stampa) */
int PrintHorizontalChoiceWithColor_FILE(char *name, int columns, int *y, int *choice, char *name_choice, int *value, char delim[], bool stampa);
/* ColorElementGame(Valore colore, primo numero diverso, secondo numero diverso, terzo numero diverso, tasto cliccato, massimi valori) */ 
int ColorElementGame(int *color, int x, int y, int z, int a, int arrow, int max);
/* Coolor(color da impostare) */
int Coolor(int x);
/* Simulazione della pressione del tasto F11 */
int FullScreen()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    Sleep(100);
    return 0;
}
/* Scrittura di una stringa su un file txt */
int WriteLog(char *name, char *string)
{
    time_t t;
    time(&t);
    FILE *fd;
    fd=fopen(name, "a");
    if( fd==NULL )
    {
        exit(EXIT_FAILURE);
    } 
    fprintf(fd, "%s %s", string, ctime(&t));
    fclose(fd);
    Sleep(1);
    return 0;
}
/* Rilevazione dimensioni schermo, sostituzione delle vecchie se viene modificata la risoluzione, e stampa della risoluzione */
int DisplayDimension(int *columns, int *rows, int *old_columns, int *old_rows, bool x)
{
    char stringtemp[2^256] = {};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    if (old_columns != NULL)
    {
        (*old_columns) = (*columns);
    }
    if (old_rows != NULL)
    {
        (*old_rows) = (*rows);
    }
    if (x)
    {
        sprintf(stringtemp, "%ix%i", *columns, *rows);
        mvprint(0, 0, stringtemp);
    }
    return 0;
}
/* Thread per la musica in loop */
DWORD WINAPI ThreadFuncMusicStart(void* data)
{
    PlaySound(data, NULL, SND_LOOP | SND_ASYNC);
    return 0;
}
/* Thread stoppare la musica */
DWORD WINAPI ThreadFuncMusicStop(void* data)
{
    PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
    return 0;
}
/* Thread per la musica in single */
DWORD WINAPI ThreadFuncMusicStartSingle(void* data)
{
    PlaySound(data, NULL, SND_ASYNC);
    return 0;
}
/* Nome del file musica, true = start flase = stop, true = loop false = single */
int MusicPlayer(char *name, bool x, bool loop)
{
    HANDLE thread;
    DWORD dwVolume;
    if (x)
    {
        if (loop)
        {
            thread = CreateThread(NULL, 0, ThreadFuncMusicStart, name, 0, NULL);
        }   
        else
        {
            thread = CreateThread(NULL, 0, ThreadFuncMusicStartSingle, name, 0, NULL);
        } 
    }
    else
    {
        thread = CreateThread(NULL, 0, ThreadFuncMusicStop, name, 0, NULL);
    }
    return 0;
}
/* unione della funzione gotoxy e printf */
int mvprint(int x, int y, char *string)
{
    gotoxy(x, y);
    puts(string);
    return 0;
}
/* Cambiare posizione del cursore sulla console */
int gotoxy (short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), pos);
    Hidecursor();
    return 0;
}
/* Rendere invisibile il cursore */
int Hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
   return 0;
}
/* Assegnare una y di aprtenza della stampa in base alle dimensioni del monitor */
int Responsitive(int *columns, int *rows, int *old_columns, int *old_rows, int tablet, int mobile, bool x)
{
    int y = 0;
    DisplayDimension(columns, rows, NULL, NULL, x);
    if ((*old_columns) != (*columns) || (*old_rows) != (*rows))
    {
        *old_rows = (*rows);
        *old_columns = (*columns);
        clear();
    }
    if ((*rows) < 30 + 1)
    {
        y = 0;
    }
    else if ((*rows) < 40 + 1)
    {
        y = (*rows) - tablet;
    }
    else
    {
        y = mobile;
    }
    return y;
}
/* Stampa del contenuto di un file txt con incremnto delle y */
int PrintBanner(char *file, int columns, int *y)
{
    /* MA TU SAI CHI SONO IO?*/
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int temp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1)
    {
        PrintMiddle(line, columns, y, 1);
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }
    return 0;
}
/* Stampa una stringa centralemente */
int PrintMiddle(char *name, int columns, int *y, int n)
{
    int tempcoord = (columns/2) - (strlen(name)/2);
    *y += n;
    mvprint(tempcoord, *y, name);
    return 0;
}
/* Stampa le scelte dei menu verticali, se è selezionata l'opzione viene posta in eveidenza */
int PrintRowMenu(int *choice, int *CHOICE, char *stringa, int columns, int *y, int n)
{
    char stringtemp[2^256] = {};
    if (*choice == (*CHOICE)++)
    {
        sprintf(stringtemp, ">%s ", stringa);
    }
    else
    {
        sprintf(stringtemp, " %s ", stringa);
    }
    PrintMiddle(stringtemp, columns, y, n);
    return 0;
}
/* Stampa delle opzioni orizzontali prese da un file di testo con un valore, i dati vengono presi dalla stringa del txt e successivamente
   passano in un parser che separa le varie entità con l'utilizzo del token */
int PrintHorizontalChoice_FILE(char *name, int columns, int *y, int *choice, char *name_choice, int *value, char delim[], bool stampa)
{
    char stringtemp[2^256] = {};
    int tempcoord;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int init_size = 0;
    char *ptr;
    int j;
    int h;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    h = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        init_size = strlen(line);
        ptr = strtok(line, delim);
        j = 0;
        while (ptr != NULL)
        {
            if (h == (*choice))
            {
                if (j == 0)
                {
                    strcpy(name_choice, ptr);
                    if (stampa)
                    {
                        sprintf(stringtemp, "%s%s%s", "          ", ptr, "          ");
                        PrintMiddle(stringtemp, columns, y, 1);
                    }
                    
                }
                else if (j == 1)
                {
                    *value = atoi(ptr);
                }  
            }
            ptr = strtok(NULL, delim);
            j++;
        }
        h++;
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }
    return 0;
}
/* Scelte dei menu verticali */
int RangeverticalMenu(int c, int *choice, int max)
{
    if (c == 72)
    {
        ArrowUpMenu(choice, max);
    } 
    else if (c == 80)
    {
        ArrowDownMenu(choice, max);
    }  
    return 0;
}
/* Scelte massime per la freccia UP */
int ArrowUpMenu(int *choice, int max)
{
    if (*(choice) - 1 == -1)
    {
        (*choice) = max;
    } 
    else
    {
        (*choice)--;
    } 
    return 0;
}
/* Scelte massime per la freccia DOWN */
int ArrowDownMenu(int *choice, int max)
{
    if (*(choice) + 1 == max + 1)
    {
        (*choice) = 0;
    }
    else
    {
        (*choice)++;
    }
    return 0;
}
/* Scelte massime per la freccia LEFT */
int ArrowLeftMenu(int *choice, int max)
{
    if ((*choice) - 1 == -1)
    {
        (*choice) = max;
    }
    else
    {
        (*choice)--;
    }
    return 0;
}
/* Scelte massime per la freccia LEFT */
int ArrowRightMenu(int *choice, int max)
{
    if ((*choice) + 1 == max + 1)
    {
        (*choice) = 0;
    }
    else
    {
        (*choice)++;
    }
    return 0;
}
/* Ritorno delle righe di un file txt */
int RowFileTxt(char *name)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int n = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1)
    {
        n++;
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }   
    return n;
}
/* Stampa delle opzioni orizzontali prese da un file di testo con un valore, i dati vengono presi dalla stringa del txt e successivamente
   passano in un parser che separa le varie entità con l'utilizzo del token, con controllo per i punti sbloccati */
bool PrintHorizontalChoiceLock_FILE(char *name, int columns, int *y, int *choice, int *value1, int *value2, int *value3, int *value4, int *value5, int *value6, char delim[], int points, bool stampa)
{
    bool x;
    int j, h;
    int tempoint;
    char stringtemp[2^256] = {};
    char stringtemp2[2^256] = {};
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int init_size = 0;
    char *ptr;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    h = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        init_size = strlen(line);
        ptr = strtok(line, delim);
        j = 0;
        while (ptr != NULL)
        {
            if (h == (*choice))
            {
                if (value2 == NULL)
                {
                    if (j == 0)
                    {
                        sprintf(stringtemp, ptr);
                    }
                    else if (j == 1)
                    {
                        *value1 = atoi(ptr);
                    }
                    else if (j == 2)
                    {
                        tempoint = atoi(ptr);
                        if (stampa)
                        {
                            if (points > tempoint || points == -1)
                            {
                                sprintf(stringtemp2, "%s%s%s", "                     ", stringtemp, "                     ");
                                x = false;
                            }
                            else
                            {
                                sprintf(stringtemp2, "%s%s %i%s", "                      ", stringtemp, tempoint, " points to unlock  ");
                                x = true;
                            }
                            PrintMiddle(stringtemp2, columns, y, 1);
                        }
                    }
                }
                else
                {
                    if (j == 1)
                    {
                        sprintf(stringtemp, ptr);
                        *value1 = atoi(ptr);
                    }
                    else if (j == 3)
                    {
                        *value2 = atoi(ptr);
                    }
                    else if (j == 5)
                    {
                        *value3 = atoi(ptr);
                    }
                    else if (j == 7)
                    {
                        *value4 = atoi(ptr);
                    }
                    else if (j == 9)
                    {
                        *value5 = atoi(ptr);
                    }
                    else if (j == 11)
                    {
                        *value6 = atoi(ptr);
                    }
                    else if (j == 12)
                    {
                        char temp = atoi(stringtemp);
                        tempoint = atoi(ptr);
                        if (points > tempoint || points == -1)
                        {
                            sprintf(stringtemp2, "%s%c%s", "                     ", temp, "                     ");
                            x = 0;
                        }
                        else
                        {
                            sprintf(stringtemp2, "%s%c %i%s", "                        ", temp, tempoint, " points to unlock  ");
                            x = 1;
                        }
                        if (stampa)
                        {
                            PrintMiddle(stringtemp2, columns, y, 1);
                        }
                    }
                }
            }
            ptr = strtok(NULL, delim);
            j++;
        }
        h++;
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }
    return x;
}
/* Se un file esiste */
bool file_exists (char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}
/* Stampa delle opzioni orizzontali prese da un file di testo con un valore, i dati vengono presi dalla stringa del txt e successivamente
   passano in un parser che separa le varie entità con l'utilizzo del token, con l'aggiunta dei colori per rendere il tutto più unico */
int PrintHorizontalChoiceWithColor_FILE(char *name, int columns, int *y, int *choice, char *name_choice, int *value, char delim[], bool stampa)
{
    HANDLE hc = GetStdHandle ( STD_OUTPUT_HANDLE );
    char stringtemp[2^256] = {};
    int tempcoord;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int init_size = 0;
    char *ptr;
    int j;
    int h;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    h = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        init_size = strlen(line);
        ptr = strtok(line, delim);
        j = 0;
        while (ptr != NULL)
        {
            if (h == (*choice))
            {
                if (j == 0)
                {
                    strcpy(name_choice, ptr);
                    sprintf(stringtemp, "%s%s%s", "          ", ptr, " \x1a \xdb       ");
                }         
                else if (j == 1)
                {
                    *value = atoi(ptr);
                    if (stampa)
                    {
                        tempcoord = (columns/2) - (strlen(ptr)/2);
                        if ((*value) == 0)
                        {
                            SetConsoleTextAttribute(hc, 15);
                        }
                        else
                        {
                            SetConsoleTextAttribute(hc, (*value));
                        }
                        PrintMiddle(stringtemp, columns, y, 1);
                        SetConsoleTextAttribute(hc, 15);
                    }
                }
            }
            ptr = strtok(NULL, delim);
            j++;
        }
        h++;
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }
    return 0;
}
/* Controllo il valore x sia diverso dagli altri */
int ColorElementGame(int *color, int x, int y, int z, int a, int arrow, int max)
{
    int exit_color = 0;
    if (arrow == 75)
    {
        ArrowLeftMenu(color, max);
        do
        {
            if (x == -1)
            {
                if((*color) != y)
                {
                    exit_color = 1;
                }
                else
                {
                    (*color)--;
                }
            }
            else
            {
                if ((*color) != x && (*color) != y && (*color) != z && (*color) != a)
                {
                    exit_color = 1;
                }
                else
                {
                    (*color)--;
                }
            }
            if ((*color) < 0)
            {
                exit_color = 0;
                (*color) = max;
            }
        } while (exit_color == 0);
    }
    else if (arrow == 77)
    {
        ArrowRightMenu(color, max);
        do
        {
            if (x == -1)
            {
                if((*color) != y)
                {
                    exit_color = 1;
                }
                else
                {
                    (*color)++;
                }
            }
            else
            {
                if ((*color) != x && (*color) != y && (*color) != z && (*color) != a)
                {
                    exit_color = 1;
                }
                else
                {
                    (*color)++;
                }
            }
            if ((*color) > max)
            {
                exit_color = 0;
                (*color) = 0;
            }
        } while (exit_color == 0);
    }
    return 0;
}
/* Imposta colore */
int Coolor(int x)
{
    HANDLE hc = GetStdHandle ( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hc, x);
    return 0;
}

#endif