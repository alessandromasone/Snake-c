#ifndef _SNAKEEASTEREGG_H_
#define _SNAKEEASTEREGG_H_

/* Stampa del primo easteregg (stati delle varie variabili), solo nel menu principale e nel menu setting */
void DeBug()
{
    gotoxy(0,1);
    printf("value_color_head-> %i           \n",value.color_head);
    printf("value_color_body-> %i           \n",value.color_body);
    printf("value_color_background-> %i           \n",value.color_background);
    printf("value_color_frame-> %i           \n",value.color_frame);
    printf("value_type_head-> %i           \n",value.type_head);
    printf("value_type_body-> %i           \n",value.type_body);
    printf("value_frame_up-> %i           \n",value.frame_up);
    printf("value_frame_side-> %i           \n",value.frame_side);
    printf("value_frame_angle_up_dx-> %i           \n",value.frame_angle_up_dx);
    printf("value_frame_angle_down_dx-> %i           \n",value.frame_angle_down_dx);
    printf("value_frame_angle_up_sx-> %i           \n",value.frame_angle_up_sx);
    printf("value_frame_angle_down_sx-> %i           \n",value.frame_angle_down_sx);
    printf("value_speed-> %i           \n",value.speed);
    printf("name_color_head-> %s           \n", name.color_head);
    printf("name_color_body-> %s           \n", name.color_body);
    printf("name_color_frame-> %s           \n", name.color_frame);
    printf("name_difficulty-> %s           \n", name.difficulty);
    printf("columns-> %i           \n",columns);
    printf("rows-> %i           \n",rows);
    printf("old_columns-> %i           \n",old_columns);
    printf("old_rows-> %i           \n",old_rows);
    printf("y-> %i           \n",y);
    printf("music-> %i           \n",music);
    printf("choice_main_menu-> %i           \n",choice.main_menu);
    printf("choice_difficulty-> %i           \n",choice.difficulty);
    printf("choice_setting_menu-> %i           \n",choice.setting_menu);
    printf("choice_color_head-> %i           \n",choice.color_head);
    printf("choice_color_body-> %i           \n",choice.color_body);
    printf("choice_color_background-> %i           \n",choice.color_background);
    printf("choice_color_frame-> %i           \n",choice.color_frame);
    printf("choice_type_head-> %i           \n",choice.type_head);
    printf("choice_type_body-> %i           \n",choice.type_body);
    printf("choice_type_frame-> %i           \n",choice.type_frame);
    printf("points-> %i           \n",points);
    for (size_t i = 0; i < N_EASTEREGG; i++)
    {
        printf("easteregg[%i]-> %i           \n", i, easteregg[i]);
    }
    printf("buffereasteregg-> %s           \n", buffereasteregg);
}
/* Se l'utente ha trovato il modo di attivare il primo easteregg lo stampa a video */
void PrintEasterEgg ()
{
    if (easteregg[0] == 1)
    {
        DeBug();
    }
}
/* Scan della tastiera per inserimento della parola per easteregg */
void ScanEasterEgg (char c)
{
    if (c == '!')
    {
        if (easteregg[0] == 0)
        {
            easteregg[0] = 1;
        }
        else
        {
            clear();
            easteregg[0] = 0;
        }
    }
    int i = 0;
    if (buffereasteregg[0] == 'u')
    {
        if (buffereasteregg[1] == 's')
        {
            if (buffereasteregg[2] == 's')
            {
                if (c == 'r')
                {
                    if (music == 1)
                    {
                        easteregg[1] = 2;
                        MusicPlayer("assets/easteregg/egg1.snake", music, false);
                        memset(buffereasteregg, '\0', sizeof buffereasteregg);
                    }
                }
                else
                {
                    memset(buffereasteregg, '\0', sizeof buffereasteregg);
                    if (c == 'a')
                    {
                        buffereasteregg[0] = c;
                    }
                    else if (c == 'u')
                    {
                        buffereasteregg[0] = c;
                    }
                }
            }
            else if (c == 's')
            {
                buffereasteregg[2] = c;
            }
            else
            {
                memset(buffereasteregg, '\0', sizeof buffereasteregg);
                if (c == 'a')
                {
                    buffereasteregg[0] = c;
                }
                else if (c == 'u')
                {
                    buffereasteregg[0] = c;
                }
            }
        }
        else if (c == 's')
        {
            buffereasteregg[1] = c;
        }
        else
        {
            memset(buffereasteregg, '\0', sizeof buffereasteregg);
            if (c == 'a')
            {
                buffereasteregg[0] = c;
            }
            else if (c == 'u')
            {
                buffereasteregg[0] = c;
            }
        }
    }
    else if (buffereasteregg[0] == 'a')
    {
        if (buffereasteregg[1] == 'w')
        {
            if (buffereasteregg[2] == 'e')
            {
                if (buffereasteregg[3] == 's')
                {
                    if (buffereasteregg[4] == 'o')
                    {
                        if (buffereasteregg[5] == 'm')
                        {
                            if (c == 'e')
                            {
                                easteregg[2] = 1;
                                memset(buffereasteregg, '\0', sizeof buffereasteregg);
                            }
                            else if (c == 'e')
                            {
                                buffereasteregg[6] = c;
                                memset(buffereasteregg, '\0', sizeof buffereasteregg);
                            }
                            else
                            {
                                memset(buffereasteregg, '\0', sizeof buffereasteregg);
                                if (c == 'a')
                                {
                                    buffereasteregg[0] = c;
                                }
                                else if (c == 'u')
                                {
                                    buffereasteregg[0] = c;
                                }
                            }
                        }
                        else if (c == 'm')
                        {
                            buffereasteregg[5] = c;
                        }
                        else
                        {
                            memset(buffereasteregg, '\0', sizeof buffereasteregg);
                            if (c == 'a')
                            {
                                buffereasteregg[0] = c;
                            }
                            else if (c == 'u')
                            {
                                buffereasteregg[0] = c;
                            }
                        }
                    }
                    else if (c == 'o')
                    {
                        buffereasteregg[4] = c;
                    }
                    else
                    {
                        memset(buffereasteregg, '\0', sizeof buffereasteregg);
                        if (c == 'a')
                        {
                            buffereasteregg[0] = c;
                        }
                        else if (c == 'u')
                        {
                            buffereasteregg[0] = c;
                        }
                    }
                }
                else if (c == 's')
                {
                    buffereasteregg[3] = c;
                }
                else
                {
                    memset(buffereasteregg, '\0', sizeof buffereasteregg);
                    if (c == 'a')
                    {
                        buffereasteregg[0] = c;
                    }
                    else if (c == 'u')
                    {
                        buffereasteregg[0] = c;
                    }
                }
            }
            else if (c == 'e')
            {
                buffereasteregg[2] = c;
            }
            else
            {
                memset(buffereasteregg, '\0', sizeof buffereasteregg);
                if (c == 'a')
                {
                    buffereasteregg[0] = c;
                }
                else if (c == 'u')
                {
                    buffereasteregg[0] = c;
                }
            }
        }
        else if (c == 'w')
        {
            buffereasteregg[1] = c;
        }
        else
        {
            memset(buffereasteregg, '\0', sizeof buffereasteregg);
            if (c == 'a')
            {
                buffereasteregg[0] = c;
            }
            else if (c == 'u')
            {
                buffereasteregg[0] = c;
            }
        }
    }
    else if (c == 'u')
    {
        buffereasteregg[0] = c;
    }
    else if (c == 'a')
    {
        buffereasteregg[0] = c;
    }
    else
    {
        memset(buffereasteregg, '\0', sizeof buffereasteregg);
    }
}

#endif