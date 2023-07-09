#ifndef _SNAKEMAINMENU_H_
#define _SNAKEMAINMENU_H_

/* Chiama del menu principale restituisce false se si decide di uscirne
   Viene calcola una y per l'inizio della stampa verticale
   Successivamente stampa delle varie opzioni del menu con vari avvisi posti negli angoli */
bool MainMenu()
{
    bool exit = true;
    int CHOICE_MAIN_MENU = 0;
    char s[WORD] = {};
    y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    PrintEasterEgg();
    sprintf(s, "Total Points: %i", points);
    gotoxy(columns-strlen(s), 0);
    puts(s);
    PrintBanner(LOGO_FILE, columns, &y);
    PrintRowMenu(&choice.main_menu, &CHOICE_MAIN_MENU, "Single-player", columns, &y, 2);
    PrintRowMenu(&choice.main_menu, &CHOICE_MAIN_MENU, "Multi-player", columns, &y, 2);
    PrintRowMenu(&choice.main_menu, &CHOICE_MAIN_MENU, "Difficolta", columns, &y, 2);
    PrintHorizontalChoice_FILE(DIFFICULTY_FILE, columns, &y, &choice.difficulty, name.difficulty, &value.speed, ";", true);
    PrintRowMenu(&choice.main_menu, &CHOICE_MAIN_MENU, "Classifica", columns, &y, 2);
    PrintRowMenu(&choice.main_menu, &CHOICE_MAIN_MENU, "Impostazioni", columns, &y, 2);
    PrintRowMenu(&choice.main_menu, &CHOICE_MAIN_MENU, "Esci", columns, &y, 2);
    if (strlen(username) == 0)
    {
        sprintf(s, "Name: PC Name");
    }
    else
    {
         sprintf(s, "Name: %s", username);
    }
    gotoxy(columns-strlen(s), rows-2);
    puts(s);
    CHOICE_MAIN_MENU--;
    GearMainMenu(CHOICE_MAIN_MENU, &exit);
    return exit;
}
/* Rileva i tasti premuti all'interno del menu di rifermento e alla conferma dell'opzione
   (pressioni tasto ENTER o scelte dei menu orizzantali), decide a quale impostazioni portare
   attraverso gli if, tutti i controlli sono effettuati sulle funzioni di riferimento*/
int GearMainMenu(int CHOICE_MAIN_MENU, bool *exit)
{
    int DIFFICULTY_NUMBER = RowFileTxt(DIFFICULTY_FILE)-1;
    int i;
    if (kbhit())
    {
        char c = getch();
        ScanEasterEgg(c);
        RangeverticalMenu(c, &choice.main_menu, CHOICE_MAIN_MENU);
        switch (c)
        {
        case KEY_ENTER:
            i = 0;
            if (choice.main_menu == i++)
            {
                SinglePlayer();
            }
            if (choice.main_menu == i++)
            {
                Multiplayer();
            }
            if (choice.main_menu == i++)
            {
                ArrowRightMenu(&choice.difficulty, DIFFICULTY_NUMBER);
            }
            if (choice.main_menu == i++)
            {
                ClassificaMenu();
            }
            if (choice.main_menu == i++)
            {
                SettingMenu();
            }
            if (choice.main_menu == i++)
            {
                (*exit) = false;
            }
            break;
        case KEY_LEFT:
            i = 0;
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                ArrowLeftMenu(&choice.difficulty, DIFFICULTY_NUMBER);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            break;
        case KEY_RIGHT:
            i = 0;
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                ArrowRightMenu(&choice.difficulty, DIFFICULTY_NUMBER);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            if (choice.main_menu == i++)
            {
                Sleep(1);
            }
            break;
        }
    }
    return 0;
}
#endif