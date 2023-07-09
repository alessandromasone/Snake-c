#ifndef _SNAKESETTINGMENU_H_
#define _SNAKESETTINGMENU_H_

/* Chiamata del menu setting */
int SettingMenu()
{
    clear();
    do
    {
        PrintEasterEgg();
        y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    } while (MainSetting());
    clear();
    return 0;
}
/* Stampa del menu setting */
bool MainSetting()
{
    char s[WORD] = {};
    bool exit = true, lock_head = true, lock_body = true, lock_frame = true, lock_boccone = true, lock = true;
    int CHOICE_SETTING_MENU = 0;
    sprintf(s, "Total Points: %i", points);
    gotoxy(columns-strlen(s), 0);
    puts(s);
    PrintBanner(LOGO_FILE, columns, &y);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Musica", columns, &y, 2);
    if (music == 1)
    {
        PrintMiddle("SI", columns, &y, 1);
    }
    else
    {
        PrintMiddle("NO", columns, &y, 1);
        if (easteregg[1] == 2)
        {
            easteregg[1] = 0;
        }
    }
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Colore Testa", columns, &y, 2);
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_head, name.color_head, &value.color_head, ";", true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Colore Corpo", columns, &y, 2);
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_body, name.color_body, &value.color_body, ";", true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Colore Sfondo", columns, &y, 2);
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_background, name.color_background, &value.color_background, ";", true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Colore Cornice", columns, &y, 2);
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_frame, name.color_frame, &value.color_frame, ";", true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Colore Boccone", columns, &y, 2);
    PrintHorizontalChoiceWithColor_FILE(COLOR_FILE, columns, &y, &choice.color_boccone, name.color_boccone, &value.color_boccone, ";", true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Tipo Testa", columns, &y, 2);
    lock_head = PrintHorizontalChoiceLock_FILE(SKINTYPE_FILE, columns, &y, &choice.type_head, &value.type_head, NULL, NULL, NULL, NULL, NULL, ";", points, true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Tipo Corpo", columns, &y, 2);
    lock_body = PrintHorizontalChoiceLock_FILE(SKINTYPE_FILE, columns, &y, &choice.type_body, &value.type_body, NULL, NULL, NULL, NULL, NULL, ";", points, true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Tipo Cornice", columns, &y, 2);
    lock_frame = PrintHorizontalChoiceLock_FILE(FRAMETYPE_FILE, columns, &y, &choice.type_frame, &value.frame_up, &value.frame_side, &value.frame_angle_up_dx, &value.frame_angle_down_dx, &value.frame_angle_up_sx, &value.frame_angle_down_sx, ";", points, true);
    PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Tipo Boccone", columns, &y, 2);
    lock_boccone = PrintHorizontalChoiceLock_FILE(SKINTYPE_FILE, columns, &y, &choice.type_boccone, &value.type_boccone, NULL, NULL, NULL, NULL, NULL, ";", points, true);
    if (lock_head == false && lock_body == false && lock_frame == false && lock_boccone == false)
    {
        lock = false;
    }
    if (lock)
    {
        PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Indietro lock", columns+5, &y, 2);
    }
    else
    {
        PrintRowMenu(&choice.setting_menu, &CHOICE_SETTING_MENU, "Indietro     ", columns+5, &y, 2);
    }
    CHOICE_SETTING_MENU--;
    GearSettingMenu(CHOICE_SETTING_MENU, &exit, lock);
    return exit;
}
/* Controllo dei vari input selle varie impostazioni orizzontali e verticali */
int GearSettingMenu(int CHOICE_SETTING_MENU, bool *exit, bool lock)
{
    int COLOR_NUMBER = RowFileTxt(COLOR_FILE)-1;
    int SKIN_NUMBER = RowFileTxt(SKINTYPE_FILE)-1;
    int FRAME_NUMBER = RowFileTxt(FRAMETYPE_FILE)-1;
    int i;
    if (kbhit())
    {
        char c = getch();
        ScanEasterEgg(c);
        RangeverticalMenu(c, &choice.setting_menu, CHOICE_SETTING_MENU);
        switch (c)
        {
        case KEY_ESC:
            if (lock == false)
            {
                *exit = false;
            }
            break;
        case KEY_ENTER:
            i = 0;
            if (choice.setting_menu == i++)
            {
                int x;
                if (music)
                {
                    x = 1;
                }
                else
                {
                    x = 0;
                }
                ArrowRightMenu(&x, 1);
                if (x == 1)
                {
                    music = true;
                }
                else
                {
                    music = false;
                }
                MusicPlayer(MUSIC_FILE, music, true);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_head, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_body, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_background, choice.color_body, choice.color_head, choice.color_frame, choice.color_boccone, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_frame, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_boccone, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_head, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_body, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_frame, FRAME_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_boccone, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                if (lock == false)
                {
                    *exit = false;
                }
            }
            break;
        case KEY_LEFT:
            i = 0;
            if (choice.setting_menu == i++)
            {
                int x;
                if (music)
                {
                    x = 1;
                }
                else
                {
                    x = 0;
                }
                ArrowLeftMenu(&x, 1);
                if (x == 1)
                {
                    music = true;
                }
                else
                {
                    music = false;
                }
                MusicPlayer(MUSIC_FILE, music, true);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_head, -1, choice.color_background, -1, -1, KEY_LEFT, COLOR_NUMBER);
            }   
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_body, -1, choice.color_background, -1, -1, KEY_LEFT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_background, choice.color_body, choice.color_head, choice.color_frame, choice.color_boccone, KEY_LEFT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_frame, -1, choice.color_background, -1, -1, KEY_LEFT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_boccone, -1, choice.color_background, -1, -1, KEY_LEFT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowLeftMenu(&choice.type_head, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowLeftMenu(&choice.type_body, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowLeftMenu(&choice.type_frame, FRAME_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowLeftMenu(&choice.type_boccone, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                Sleep(1);
            }
            break;
        case KEY_RIGHT:
            i = 0;
            if (choice.setting_menu == i++)
            {
                int x;
                if (music)
                {
                    x = 1;
                }
                else
                {
                    x = 0;
                }
                ArrowRightMenu(&x, 1);
                if (x == 1)
                {
                    music = true;
                }
                else
                {
                    music = false;
                }
                MusicPlayer(MUSIC_FILE, music, true);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_head, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_body, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_background, choice.color_body, choice.color_head, choice.color_frame, choice.color_boccone, KEY_RIGHT, COLOR_NUMBER);
                        }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_frame, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ColorElementGame(&choice.color_boccone, -1, choice.color_background, -1, -1, KEY_RIGHT, COLOR_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_head, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_body, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_frame, FRAME_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                ArrowRightMenu(&choice.type_boccone, SKIN_NUMBER);
            }
            if (choice.setting_menu == i++)
            {
                Sleep(1);
            }
            break;
        }
    }
    return 0;
}

#endif