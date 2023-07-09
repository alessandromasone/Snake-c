/* Inizializzazione delle variabili base (colori, dimensioni campo di gioco, posizione campo di gioco) */
int InitializeMultiplayer()
{   
    char stringtemp[2^256] = {};
    char temp;
    int x;
    if (value.color_background == 1) temp = '1';
    if (value.color_background == 2) temp = '2';
    if (value.color_background == 3) temp = '3';
    if (value.color_background == 4) temp = '4';
    if (value.color_background == 5) temp = '5';
    if (value.color_background == 6) temp = '6';
    if (value.color_background == 7) temp = '7';
    if (value.color_background == 8) temp = '8';
    if (value.color_background == 9) temp = '9';
    if (value.color_background == 10) temp = 'A';
    if (value.color_background == 11) temp = 'B';
    if (value.color_background == 12) temp = 'C';
    if (value.color_background == 13) temp = 'D';
    if (value.color_background == 14) temp = 'E';
    if (value.color_background == 15) temp = 'F';
    memset(color.backgroud_cmd, '\0', sizeof color.backgroud_cmd);
    sprintf(color.backgroud_cmd, "COLOR %cF", temp);
    system(color.backgroud_cmd);
    x = value.color_background * 16;
    color.head = x + value.color_head;
    color.body = x + value.color_body;
    color.frame = x + value.color_frame;
    color.boccone = x + value.color_boccone;
    color.background = x;
    CAMPO_GIOCO_X = (columns-40)/value.speed;
    CAMPO_GIOCO_Y = (rows-10)/value.speed;
    padding_columns = (columns - CAMPO_GIOCO_X)/2;
    padding_rows = (rows - CAMPO_GIOCO_Y)/2;
    clear();
    return 0;
}
/* Ritorno al colore dedfault e riattivazione della musica lobby se attiva la scelta */
int TerminateMultiplayer()
{
    system("COLOR 0F");
    MusicPlayer(MUSIC_FILE, music, true);
    clear();
    return 0;
}
/* Assegnazione della posizione di start ai vari serpenti, disegno della cornice, disegno del serpente a video, creazione del boccone
   Successivamente rilevamente dell'input per le varie direzioni e per i vari menu */
int Multiplayer()
{
    char s[WORD] = {};
    int egg_color = 0;
    int x;
    int old = 0, old2 = 0;
    int contaBocconi = 0, contaBocconi2 = 0, direzione = 0, direzione2 = 0;
	char c;
    bool exit = true;
    Boc boccone;
	Ser *testa, *nuovo;
	Ser *testa2, *nuovo2;
    MusicPlayer(NULL, 1, false);
    InitializeMultiplayer();
    disegnaCornice ();
    testa = creaSerpenteMultiPlayer(CAMPO_GIOCO_X/2-10, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-9, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-8, CAMPO_GIOCO_Y/2);
    testa2 = creaSerpenteMultiPlayer(CAMPO_GIOCO_X/2, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-1, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-2, CAMPO_GIOCO_Y/2);
    disegnaSerpente (testa);
    disegnaSerpente (testa2);
    boccone = creaBocconeMultiPlayer (testa, testa2);
    do
    {
        /* stampa a video le scritte dei punteggi dei player */
        Sleep(((100/value.speed)));
        gotoxy (padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 2);
        Coolor(color.boccone);
        gotoxy(padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 2);
        printf ("Bocconi Player 1 -> %i", contaBocconi);
        gotoxy (padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 3);
        printf("Punteggio Player 1 -> %i", contaBocconi*5);
        gotoxy (padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 2);
        Coolor(color.boccone);
        sprintf(s, "Bocconi Player 2 -> %i", contaBocconi2);
        gotoxy(padding_columns+CAMPO_GIOCO_X-strlen(s)+2, padding_rows+CAMPO_GIOCO_Y + 2);
        puts(s);
        sprintf(s, "Punteggio Player 2 -> %i", contaBocconi2*5);
        gotoxy (padding_columns+CAMPO_GIOCO_X-strlen(s)+2, padding_rows+CAMPO_GIOCO_Y + 3);
        puts(s);
        /* se l'easteregg è attivato esegue l'azione */
        if (easteregg[2] == 1)
        {
            if (egg_color > 15)
            {
                egg_color = 0;
            }
            color.body = color.background + egg_color++;
        }
        /* associa le direzioni ai due serpenti: 1 = su, 2 = dx, 3 = giu, 4 = sx, 5 = uscita dalla modalità*/
        if (kbhit())
        {
            MoveMultiplayer(&direzione, &direzione2, old, old2);
        }
        /* cambio delle vecchie direzioni con le nuove */
        OldMoveMultiplayer(&old, &old2, direzione, direzione2);
        if (direzione == 5)
        {
            exit = false;
        }
        else if (direzione != 0)
        {
            /* Se la testa è sul boccone rimane l'ultimo elemento del serprente */
            if (testa->x == boccone.x && testa->y == boccone.y)
            {
                gotoxy(padding_columns+testa->x, padding_rows+testa->y);	
                Coolor(color.body);	
                printf("%c", value.type_body);
                MusicPlayer(EAT_FILE, 1, false);
                contaBocconi++;
                boccone = creaBocconeMultiPlayer (testa, testa2);
                testa = muoviSerpente (testa, direzione, 1);
            }
            else /* Se la testa non è sul boccone cancella l'ultimo elemento del serpente*/
            {
                gotoxy(padding_columns+testa->x, padding_rows+testa->y);	
                Coolor(color.body);		
                printf("%c", value.type_body);
                testa = muoviSerpente (testa, direzione, 0);
            }
            /* Se c'è una collisione del serpente */
            if (fineGiocoMultiPlayer (testa, testa2) != 0)
            {
                MusicPlayer(LOSE_FILE, 1, false);
                /* Comparsa del menu "HAI PERSO" */
                x = LostMenuMultiplayer(1);
                if (x == 1) /* Opzione riprova */
                {
                    system(color.backgroud_cmd);
                    easteregg[2] = 0;
                    contaBocconi = 0, contaBocconi2 = 0, direzione = 0, direzione2 = 0;
                    free(testa);
                    free(testa2);
                    disegnaCornice ();
                    testa = creaSerpenteMultiPlayer(CAMPO_GIOCO_X/2-10, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-9, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-8, CAMPO_GIOCO_Y/2);
                    testa2 = creaSerpenteMultiPlayer(CAMPO_GIOCO_X/2, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-1, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-2, CAMPO_GIOCO_Y/2);
                    disegnaSerpente (testa);
                    disegnaSerpente (testa2);
                    boccone = creaBocconeMultiPlayer (testa, testa2);
                    exit = true;
                }
                else if (x == 2) /* Opzione Ritorna al menu principale */
                {
                    exit = false;
                    easteregg[2] = 0;
                }
                points = points + (contaBocconi*5); 
                points = points + (contaBocconi2*5); 
            }
        }
        else if (direzione2 == 0) /* Se entrambi sono fermi si ripete la stampa del serpente */
        {
            disegnaCornice ();
            gotoxy (padding_columns+boccone.x, padding_rows+boccone.y);
            Coolor(color.boccone);	
		    printf ("%c", value.type_boccone);
            disegnaSerpente(testa);
            disegnaSerpente(testa2);
        }

        if (direzione == 5)
        {
            exit = false;
        }
        else if (direzione2 != 0)
        {
            /* Se la testa è sul boccone rimane l'ultimo elemento del serprente */
            if (testa2->x == boccone.x && testa2->y == boccone.y)
            {
                gotoxy(padding_columns+testa2->x, padding_rows+testa2->y);	
                Coolor(color.body);	
                printf("%c", value.type_body);
                MusicPlayer(EAT_FILE, 1, false);
                contaBocconi2++;
                boccone = creaBocconeMultiPlayer (testa, testa2);
                testa2 = muoviSerpente (testa2, direzione2, 1);
            }
            else /* Se la testa non è sul boccone cancella l'ultimo elemento del serpente*/
            {
                gotoxy(padding_columns+testa2->x, padding_rows+testa2->y);	
                Coolor(color.body);		
                printf("%c", value.type_body);
                testa2 = muoviSerpente (testa2, direzione2, 0);
            }
            /* Se c'è una collisione del serpente */
            if (fineGiocoMultiPlayer (testa2, testa) != 0)
            {
                MusicPlayer(LOSE_FILE, 1, false);
                /* Comparsa del menu "HAI PERSO" */
                x = LostMenuMultiplayer(2);
                if (x == 1) /* Opzione riprova */
                {
                    system(color.backgroud_cmd);
                    easteregg[2] = 0;
                    contaBocconi = 0, contaBocconi2 = 0, direzione = 0, direzione2 = 0;
                    free(testa);
                    free(testa2);
                    disegnaCornice ();
                    testa = creaSerpenteMultiPlayer(CAMPO_GIOCO_X/2-10, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-9, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-8, CAMPO_GIOCO_Y/2);
                    testa2 = creaSerpenteMultiPlayer(CAMPO_GIOCO_X/2, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-1, CAMPO_GIOCO_Y/2, (CAMPO_GIOCO_X/2)-2, CAMPO_GIOCO_Y/2);
                    disegnaSerpente (testa);
                    disegnaSerpente (testa2);
                    boccone = creaBocconeMultiPlayer (testa, testa2);
                    exit = true;        
                }
                else if (x == 2) /* Opzione Ritorna al menu principale */
                {
                    exit = false;
                    easteregg[2] = 0;
                }
                points = points + (contaBocconi*5); 
                points = points + (contaBocconi2*5); 
            }
        }
        else if (direzione == 0) /* Se entrambi sono fermi si ripete la stampa del serpente */
        {
            disegnaCornice ();
            gotoxy (padding_columns+boccone.x, padding_rows+boccone.y);
            Coolor(color.boccone);	
		    printf ("%c", value.type_boccone);
            disegnaSerpente(testa);
            disegnaSerpente(testa2);
        }
    } while (exit);
    TerminateMultiplayer();
    return 0;
}

/* Associazione delle cordine ai primi 3 elementi del serpente base */
Ser *creaSerpenteMultiPlayer(int x1, int y1, int x2, int y2, int x3, int y3)
{
	Ser *testa, *coda, *nuovo;	
	nuovo = (Ser *)malloc(sizeof(Ser));		
	testa = nuovo;
	testa->x = x1;
	testa->y = y1;
	testa->prossimo = NULL;
	coda = testa;							
	nuovo = (Ser *)malloc(sizeof(Ser));		
	nuovo->x = x2;
	nuovo->y = y2;
	nuovo->prossimo = NULL;
	coda->prossimo = nuovo;					
	coda = nuovo;	
	nuovo = (Ser *)malloc(sizeof(Ser));	
	nuovo->x = x3;
	nuovo->y = y3;
	nuovo->prossimo = NULL;
	coda->prossimo = nuovo;
	coda = nuovo;	
	return testa;
}
/* Rilevazione cambio di direzione */
int MoveMultiplayer(int *a, int *b, int old_a, int old_b)
{
    int x, key;
    key=getch();
    if (key == 224)
    {
        do
        {
            key=getch();
        } while(key==224);
        /* Direzione per il primo player */
        switch (key) 
        {
            case KEY_UP:
                if (old_a != 3)
                {
                    *a = 1;
                }
                else
                {
                    *a = 3;
                }
                break;
            case KEY_LEFT:
                if (old_a != 2)
                {
                    *a = 4;
                }
                else
                {
                    *a = 2;
                }
                break;
            case KEY_RIGHT:
                if (old_a != 4)
                {
                    *a = 2;
                }
                else
                {
                    *a = 4;
                }
                break;
            case KEY_DOWN:
                if (old_a != 1)
                {
                    *a = 3;
                }
                else
                {
                    *a = 1;
                }
                break;
            
        }
    }
    else if (key == KEY_ESC) /* Menu pausa */
    {
        choice.pause_menu = 0;
        x = CallPauseMenuMultiPlayer(); /* Se è diverso da 5 mette in pausa i due serpenti */
        if (x != 5)
        {
            system(color.backgroud_cmd);
            *a = 0;
            *b = 0;
        } 
        else
        {
            *a = 5;
        }
    }
    else
    {
        /* Direzione per il secondo player */
        switch (key)
        {
            case KEY_W:
                if (old_b != 3)
                {
                    *b = 1;
                }
                else
                {
                    *b = 3;
                }
                break;
            case KEY_A:
                if (old_b != 2)
                {
                    *b = 4;
                }
                else
                {
                    *b = 2;
                }
                break;
            case KEY_D:
                if (old_b != 4)
                {
                    *b = 2;
                }
                else
                {
                    *b = 4;
                }
                break;
            case KEY_S:
                if (old_b != 1)
                    {
                        *b = 3;
                    }
                    else
                    {
                        *b = 1;
                    }
                break;
        }
    }
    return 0; 
}
/* Modifica delle vecchie direzioni se sono diverse dalle nuove con riproduzione del suono */
int OldMoveMultiplayer(int *old, int *old2, int direzione, int direzione2)
{
    if (*old != direzione)
    {
        *old = direzione;
        if (direzione == 1)
        {
            MusicPlayer(MV_UP_FILE, 1, false);
        }
        if (direzione == 4)
        {
            MusicPlayer(MV_LEFT_FILE, 1, false);
        }
        if (direzione == 2)
        {
            MusicPlayer(MV_RIGHT_FILE, 1, false);
        }
        if (direzione == 3)
        {
            MusicPlayer(MV_DOWN_FILE, 1, false);
        }
    }
    if (*old2 != direzione2)
    {
        *old2 = direzione2;
        if (direzione2 == 1)
        {
            MusicPlayer(MV_UP_FILE, 1, false);
        }
        if (direzione2 == 4)
        {
            MusicPlayer(MV_LEFT_FILE, 1, false);
        }
        if (direzione2 == 2)
        {
            MusicPlayer(MV_RIGHT_FILE, 1, false);
        }
        if (direzione2 == 3)
        {
            MusicPlayer(MV_DOWN_FILE, 1, false);
        }
    }
}
/* Collisione con altro serpente */
int collisioneAltro (Ser *testa, Ser *testa2)
{
    Ser *p, *pp;
	p = testa2->prossimo;
    pp = testa->prossimo;
	while (p != NULL)
	{
		if (testa->x == p->x && testa->y == p->y)
        {
            return 1;
        }
        p = p->prossimo;
    }
    while (pp != NULL)
	{
        if (testa2->x == pp->x && testa2->y == pp->y)
        {
            return 1;
        }
		
        pp = pp->prossimo;
	}
	return 0;
}
/* Controllo delle collisioni */
int fineGiocoMultiPlayer (Ser *testa, Ser *testa2)
{
	return (collisioneCornice (testa) || collisioneSeStesso (testa) || collisioneAltro (testa, testa2));
}
/* Creazione del boccono nelle posizioni utili nel campo */
Boc creaBocconeMultiPlayer (Ser *p, Ser *pp)
{							
	Boc b;			
	do 
	{
        do
        {	
            b.y = rand() % CAMPO_GIOCO_Y + 1;
            b.x = rand() % CAMPO_GIOCO_Y + 1;
            p = p->prossimo;
            pp = pp->prossimo;
        } while ((b.y == p->y || b.y == pp->y) && (b.x == p->y || b.x == pp->y));
		gotoxy (padding_columns+b.x, padding_rows+b.y);
        Coolor(color.boccone);
        printf("%c", value.type_boccone);
	} while (0);
	return b;
}
/* Chiamata del menu di pausa */
int CallPauseMenuMultiPlayer()
{
    int x;
    clear();
    system("COLOR 0F");
    do
    {
        y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    } while (MainPauseMenuMultiPlayer(&x));
    clear();
    return x;
}
/* Stampa del menu pausa */
bool MainPauseMenuMultiPlayer(int *x)
{
    bool exit = true;
    int CHOICE_PAUSE_MENU = 0;
    PrintBanner(LOGO_FILE, columns, &y);
    PrintRowMenu(&choice.pause_menu, &CHOICE_PAUSE_MENU, "Resume", columns, &y, 2);
    PrintRowMenu(&choice.pause_menu, &CHOICE_PAUSE_MENU, "Back to Main Menu", columns, &y, 2);
    CHOICE_PAUSE_MENU--;
    GearPauseMenu(CHOICE_PAUSE_MENU, &exit, x);
    return exit;
}
/* Stampa del menu di sconfitta */
int LostMenuMultiplayer(int n)
{
    int x = 0;
    system("COLOR 0F");
    clear();
    choice.lost_menu = 0;
    do
    {
        y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    } while (MainLostMenuMultiPlayer(&x, n));
    clear();
    return x;
}
/* Visualizzazione a video del vincitore */
bool MainLostMenuMultiPlayer(int *x, int n)
{
    char s[WORD] = {};
    bool exit = true;
    int CHOICE_LOST_MENU = 0;
    if (n == 1)
    {
        PrintBanner(WON2_FILE, columns, &y);
    }
    else
    {
        PrintBanner(WON1_FILE, columns, &y);
    }
    PrintRowMenu(&choice.lost_menu, &CHOICE_LOST_MENU, "Try Again", columns, &y, 2);
    PrintRowMenu(&choice.lost_menu, &CHOICE_LOST_MENU, "Back to Main Menu", columns, &y, 2);
    CHOICE_LOST_MENU--;
    GearLostMenu(CHOICE_LOST_MENU, &exit, x);
    return exit;
}