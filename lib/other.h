#ifndef _SNAKEOTHER_H_
#define _SNAKEOTHER_H_

/* Inizializzazione delle variabili e del programma */
int Initialize(int argc, char const *argv[])
{
    InitLog(LOG_FILE);
    if(file_exists("preference.bin"))
    {
        RestoreVar();
    }
    else
    {
        InitVar();
    }
    if (argc == 2)
    {
        if (strcmp(argv[1], "log") == 0)
        {
            system("start log.exe");
        }
    }
    FullScreen();
    DisplayDimension(&columns, &rows, &old_columns, &old_rows, false);
    TakeName();
    DisplayDimension(&columns, &rows, &old_columns, &old_rows, true);
    MusicPlayer(MUSIC_FILE, music, true);
    return 0;
}
/* inseriemnto inzionale del nome */
int TakeName()
{
    bool exit = true;
    char c;
    do
    {
        y = rows/2;
        PrintMiddle("Type Name, ENTER for confirm", columns, &y, 0);
        PrintMiddle(username, columns, &y, 1);
        if (kbhit())
        {
            c = getch ();
            switch (c)
            {
            case 8:
                clear();
                username[strlen(username)-1] = '\0';
                break;
            case KEY_ENTER:
                exit = false;
                break;
            default:
                if (strlen(username) < 25)
                {
                    strncat(username, &c, 1);
                } 
                break;
            }
        }
    } while (exit);
    clear();
    return 0;
}
/* Inizializzazione delle variabili se non è presente un file preference */
int InitVar()
{
    char stringtemp[2^256] = {};
    srand(time(NULL));
    if (file_exists("points.dll"))
    {
        points = 99999999;
    }
    else
    {
        points = 0;
    }
    choice.difficulty = 0;
    PrintHorizontalChoice_FILE(DIFFICULTY_FILE, columns, &y, &choice.difficulty, name.difficulty, &value.speed, ";", false);
    music = true;
    choice.color_head = 15;
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_head, name.color_head, &value.color_head, ";", false);
    choice.color_body = 15;
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_body, name.color_body, &value.color_body, ";", false);
    choice.color_background = 0;
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_background, name.color_background, &value.color_background, ";", false);
    choice.color_frame = 15;
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_frame, name.color_frame, &value.color_frame, ";", false);
    choice.color_boccone = 15;
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_boccone, name.color_boccone, &value.color_boccone, ";", false);
    choice.type_head = 0;
    PrintHorizontalChoiceLock_FILE(SKINTYPE_FILE, columns, &y, &choice.type_head, &value.type_head, NULL, NULL, NULL, NULL, NULL, ";", points, false);
    choice.type_body = 0;
    PrintHorizontalChoiceLock_FILE(SKINTYPE_FILE, columns, &y, &choice.type_body, &value.type_body, NULL, NULL, NULL, NULL, NULL, ";", points, false);
    choice.type_frame = 0;
    PrintHorizontalChoiceLock_FILE(FRAMETYPE_FILE, columns, &y, &choice.type_frame, &value.frame_up, &value.frame_side, &value.frame_angle_up_dx, &value.frame_angle_down_dx, &value.frame_angle_up_sx, &value.frame_angle_down_sx, ";", points, false);
    choice.type_boccone = 0;
    PrintHorizontalChoiceLock_FILE(SKINTYPE_FILE, columns, &y, &choice.type_boccone, &value.type_boccone, NULL, NULL, NULL, NULL, NULL, ";", points, false);
    RestoreVar();
    return 0;
}
/* Ripresa delle variabili dal file preference */
int RestoreVar()
{
    FILE *f;
    f = fopen(PREFERENCE_FILE,"rb");
    fread(&value,sizeof(valori),1,f);
    fread(&choice,sizeof(scelte),1,f);
    fread(&name,sizeof(nome),1,f);
    fread(&username,sizeof(username),1,f);
    fread(&music,sizeof(int),1,f);
    fread(&points,sizeof(int),1,f);
    fclose(f);
    choice.main_menu = 0;
    choice.pause_menu = 0;
    choice.setting_menu = 0;
    choice.lost_menu = 0;
    return 0;
}
/* Fine del programma */
int Terminate()
{
    SaveVar();
    StopLog();
    return 0;
}
/* Salvataggio delle variabili */
int SaveVar()
{
    FILE *f;
    f = fopen(PREFERENCE_FILE,"wb");
    fwrite(&value,sizeof(valori),1,f);
    fwrite(&choice,sizeof(scelte),1,f);
    fwrite(&name,sizeof(nome),1,f);
    fwrite(&username,sizeof(username),1,f);
    fwrite(&music,sizeof(int),1,f);
    fwrite(&points,sizeof(int),1,f);
    fclose(f);
    return 0;
}
/* Fermare il log */
int StopLog()
{
    remove("log.dll");
    return 0;
}
/* Start per il log */
int InitLog(char *name)
{
    time_t t;
    time(&t);
    FILE *fp; 
    fp=fopen("log.dll","w"); 
    fclose(fp);
    Sleep(10);
    fp=fopen(name, "a");
    if( fp==NULL )
    {
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "Log Snake Start: %s", ctime(&t));
    fclose(fp);
    Sleep(10);
    return 0;
}

#endif