#ifndef _SNAKESINGLEPLAYER_H_
#define _SNAKESINGLEPLAYER_H_

/* Inizializzazione delle variabili base (colori, dimensioni campo di gioco, posizione campo di gioco) */
int InitializeSingleplayer()
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
int TerminateSingleplayer()
{
    system("COLOR 0F");
    MusicPlayer(MUSIC_FILE, music, true);
    clear();
    return 0;
}
/* Assegnazione della posizione di start al serpente, disegno della cornice, disegno del serpente a video, creazione del boccone
   Successivamente rilevamente dell'input per le varie direzioni e per i vari menu */
int SinglePlayer()
{
    int egg_color = 0;
    int x;
    int old = 0;
    int contaBocconi = 0, direzione = 0;
	char c;
    bool exit = true;
    Boc boccone;
	Ser *testa, *nuovo;
    MusicPlayer(NULL, 1, false);
    InitializeSingleplayer();
    disegnaCornice ();
    testa = creaSerpente ();
    disegnaSerpente (testa);
    boccone = creaBoccone (testa);
    do
    {
        /* stampa a video le scritte dei punteggi dedl player */
        gotoxy (padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 2);
        Coolor(color.boccone);
        gotoxy(padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 2);
        printf ("Bocconi mangiati -> %i", contaBocconi);
        gotoxy (padding_columns+0, padding_rows+CAMPO_GIOCO_Y + 3);
        printf("Punteggio totale -> %i", contaBocconi*5);  
        /* se l'easteregg è attivato esegue l'azione */
        if (easteregg[2] == 1)
        {
            if (egg_color > 15)
            {
                egg_color = 0;
            }
            color.body = color.background + egg_color++;
        }
        /* restituisce la direzione: 1 = su, 2 = dx, 3 = giu, 4 = sx, 5 = uscita dalla modalità*/
        if (kbhit())
        {
            direzione = Move(direzione);
        }
        /* cambio delle vecchie direzioni con le nuove */
        if (old != direzione)
        {
            old = direzione;
            
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
        if (direzione != 0)
        {
            
            if (direzione == 5)
            {
                exit = false;
            }
            else
            {
                /* Se la testa è sul boccone rimane l'ultimo elemento del serprente */
                if (testa->x == boccone.x && testa->y == boccone.y)
                {
                    gotoxy(padding_columns+testa->x, padding_rows+testa->y);	
                    Coolor(color.body);	
                    printf("%c", value.type_body);
                    MusicPlayer(EAT_FILE, 1, false);
                    contaBocconi++;
                    boccone = creaBoccone (testa);
                    testa = muoviSerpente (testa, direzione, 1);
                }
                else /* Se la testa non è sul boccone cancella l'ultimo elemento del serpente*/
                {
                    gotoxy(padding_columns+testa->x, padding_rows+testa->y);	
                    Coolor(color.body);		
                    printf("%c", value.type_body);
                    testa = muoviSerpente (testa, direzione, 0);
                }
                Sleep((100/value.speed));
            }
            /* Se c'è una collisione del serpente */
            if (fineGioco(testa) != 0)
            {
                MusicPlayer(LOSE_FILE, 1, false);
                /* Comparsa del menu "HAI PERSO" */
                x = LostMenu(contaBocconi);
                if (x == 1) /* Opzione Save score */
                {
                    SaveScore(contaBocconi);
                    exit = false;
                    easteregg[2] = 0;
                }
                else if (x == 2) /* Opzione Riprova */
                {
                    system(color.backgroud_cmd);
                    easteregg[2] = 0;
                    contaBocconi = 0, direzione = 0;
                    free(testa);
                    disegnaCornice ();
                    testa = creaSerpente ();
                    disegnaSerpente (testa);
                    boccone = creaBoccone (testa);
                    direzione = 0;
                    exit = true;
                }
                else if (x == 3) /* Back to main menu */
                {
                    exit = false;
                    easteregg[2] = 0;
                }
                points = points + (contaBocconi*5); 
            }
        }
        else /* Se è fermo ripete la stampa del serpente */
        {
            disegnaCornice ();
            gotoxy (padding_columns+boccone.x, padding_rows+boccone.y);
            Coolor(color.boccone);	
		    printf ("%c", value.type_boccone);
            disegnaSerpente(testa);
        }
    } while (exit);
    TerminateSingleplayer();
    return 0;
}
/* Associazione delle cordine ai primi 3 elementi del serpente base */
Ser *creaSerpente()
{
	Ser *testa, *coda, *nuovo;	
	nuovo = (Ser *)malloc(sizeof(Ser));		
	testa = nuovo;
	testa->x = CAMPO_GIOCO_X/2;
	testa->y = CAMPO_GIOCO_Y/2;
	testa->prossimo = NULL;
	coda = testa;							
	nuovo = (Ser *)malloc(sizeof(Ser));		
	nuovo->x = (CAMPO_GIOCO_X/2)-1;
	nuovo->y = CAMPO_GIOCO_Y/2;
	nuovo->prossimo = NULL;
	coda->prossimo = nuovo;					
	coda = nuovo;	
	nuovo = (Ser *)malloc(sizeof(Ser));	
	nuovo->x = (CAMPO_GIOCO_X/2)-2;
	nuovo->y = CAMPO_GIOCO_Y/2;
	nuovo->prossimo = NULL;
	coda->prossimo = nuovo;
	coda = nuovo;	
	return testa;
}
/* Cambio coordinate del serpente in base alla direzione */
Ser *muoviSerpente (Ser *testa, int direzione, int bocconeMangiato)
{
	Ser *nuovo, *prec;
	nuovo = (Ser *)malloc(sizeof(Ser));
	switch (direzione)					       
	{									
		case 1: 
            nuovo->x = testa->x;
			nuovo->y = testa->y - 1;
			break;
		case 2: 
            nuovo->x = testa->x + 1;
			nuovo->y = testa->y;
				break;
		case 3: 
            nuovo->x = testa->x;
			nuovo->y = testa->y + 1;
			break;
		case 4: 
            nuovo->x = testa->x - 1;
			nuovo->y = testa->y;
			break;			
	}
	nuovo->prossimo = testa;
	testa = nuovo;
    gotoxy(padding_columns+testa->x, padding_rows+testa->y);
    Coolor(color.head);
    printf("%c", value.type_head);
	if (bocconeMangiato == 0)
	{
		while (nuovo->prossimo != NULL)
		{
            prec = nuovo;
			nuovo = nuovo->prossimo;
		}
		gotoxy(padding_columns+nuovo->x, padding_rows+nuovo->y);		 
		Coolor(color.background);
        printf("%c", ' ');			
		free (nuovo);
		prec->prossimo = NULL;	
	}
	return testa;
}
/* Creazione del boccono nelle posizioni utili nel campo */
Boc creaBoccone (Ser *p)				      
{							
	Boc b;			
	do 
	{
        do
        {	
            b.y = rand() % CAMPO_GIOCO_Y + 1;
            p = p->prossimo;
        } while (b.y == p->y);
		do
        {	
            b.x = rand() % CAMPO_GIOCO_X + 1;
            p = p->prossimo;
        } while (b.x == p->x);
		gotoxy (padding_columns+b.x, padding_rows+b.y);
        Coolor(color.boccone);
        printf("%c", value.type_boccone);
	} while (0);
	return b;
}
/* Disegno del campo di gioco */
int disegnaCornice ()
{
	int i;
    /* angolo alto a sinistra */
	gotoxy(padding_columns+0, padding_rows+0);
    Coolor(color.frame);
    printf("%c",value.frame_angle_up_sx);
    /* cornice superiore */
	gotoxy (padding_columns+1, padding_rows+0);
	for (i = 0; i < CAMPO_GIOCO_X ; i++)
		printf ("%c",value.frame_up);
    /* angolo alto a destra */
	gotoxy(padding_columns+CAMPO_GIOCO_X + 1, padding_rows+0);
	printf("%c",value.frame_angle_up_dx);
    /* cornici laterali */
	for (i = padding_rows+1; i <= padding_rows+CAMPO_GIOCO_Y; i++)
	{
		gotoxy (padding_columns+0, i);
		printf ("%c",value.frame_side);
		gotoxy (padding_columns+CAMPO_GIOCO_X + 1, i);
		printf ("%c",value.frame_side);
	}
    /* angolo basso a sinistra */
	gotoxy(padding_columns+0,padding_rows+CAMPO_GIOCO_Y + 1);
	printf("%c",value.frame_angle_down_sx);
    /* angolo basso a destra */
	gotoxy(padding_columns+CAMPO_GIOCO_X + 1,padding_rows+CAMPO_GIOCO_Y + 1);
	printf("%c",value.frame_angle_down_dx);
    /* cornice inferiore */
	gotoxy (padding_columns+1, padding_rows+CAMPO_GIOCO_Y + 1);
	for (i = 0; i < CAMPO_GIOCO_X ; i++)
		printf ("%c",value.frame_up);
    return 0;
}
/* Disegnod del serpente a video */
int disegnaSerpente (Ser *p)	
{
    int i = 0;
	do
	{	
        if (i == 0)
        {
            gotoxy (padding_columns+p->x, padding_rows+p->y);
            Coolor(color.head);
            printf("%c", value.type_head);
            Coolor(7);
            i++;
        }
        else
        {
            gotoxy (padding_columns+p->x, padding_rows+p->y);
            Coolor(color.body);
            printf("%c", value.type_body);
            Coolor(7);
        }
		p = p->prossimo;
	} while (p != NULL);
    return 0;	
}
/* Verifica collisioni con i bordi */
int collisioneCornice (Ser *testa)
{
	if (testa->y == 0 || testa->y == CAMPO_GIOCO_Y + 1 ||
	    testa->x == 0 || testa->x == CAMPO_GIOCO_X + 1)
	    return 1;
	else
		return 0;
}
/* Collusione con se stesso */
int collisioneSeStesso (Ser *testa)
{
	Ser *p;
	p = testa->prossimo;
	while (p != NULL)
	{
		if (testa->x == p->x && testa->y == p->y)
			return 1;
		p = p->prossimo;
	}
	return 0;
}
/* Fine del gioco  se ci sono cullusioni */
int fineGioco (Ser *testa)
{
	return (collisioneCornice (testa) || collisioneSeStesso (testa));
}
/* Scan dei tasti per il cambio direzione */
int Move(int x)
{
    int key;
        key=getch();
        if (key == 224)
        {
            do
            {
                key=getch();
            } while(key==224);
            switch (key) 
            {
                case KEY_UP:
                    if (x != 3)
                    {
                        return 1;
                    }
                    else
                    {
                        return 3;
                    }
                    break;
                case KEY_LEFT:
                    if (x != 2)
                    {
                        return 4;
                    }
                    else
                    {
                        return 2;
                    }
                    break;
                case KEY_RIGHT:
                    if (x != 4)
                    {
                        return 2;
                    }
                    else
                    {
                        return 4;
                    }
                    break;
                case KEY_DOWN:
                    if (x != 1)
                    {
                        return 3;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                default:
                    return x;
                    break;
            }
        }
        else if (key == KEY_ESC) /* Menu pause */
        {
            choice.pause_menu = 0;
            x = CallPauseMenu(); /* Se è diverso da 5 mette in pausa il serpente */
            if (x != 5)
            {
                system(color.backgroud_cmd);
                x = 0;
            }  
            return x;
        }
        else
        {
            return x;
        }
    return 0;
}
/* Rilevazione opzione del menu pausa */
int GearPauseMenu(int CHOICE_PAUSE_MENU, bool *exit, int *x)
{
    int i;
    char c;
    if (kbhit())
    {
        c = getch();
        RangeverticalMenu(c, &choice.pause_menu, CHOICE_PAUSE_MENU);
        switch (c)
        {
        case KEY_ENTER:
            i = 0;
            if (choice.pause_menu == i++)
            {
                *exit = false;
            }
            if (choice.pause_menu == i++)
            {
                *exit = false;
                *x = 5;
            }
        case KEY_ESC:
            *exit = false;  
            break;
        }
    }
    return 0;

}
/* Stampa del menu pausa */
bool MainPauseMenu(int *x)
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
/* Loop menu pause */
int CallPauseMenu()
{
    int x;
    clear();
    system("COLOR 0F");
    do
    {
        y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    } while (MainPauseMenu(&x));
    clear();
    return x;
}
/* Rilevazione tasti del menu lost */
int GearLostMenu(int CHOICE_LOST_MENU, bool *exit, int *x)
{
    int i;
    char c;
    if (kbhit())
    {
        c = getch();
        RangeverticalMenu(c, &choice.lost_menu, CHOICE_LOST_MENU);
        switch (c)
        {
        case KEY_ENTER:
            i = 0;
            if (choice.lost_menu == i++)
            {
                *x = 1;
                *exit = false;
            }
            if (choice.lost_menu == i++)
            {
                *x = 2;
                *exit = false;
            }
            if (choice.lost_menu == i++)
            {
                *x = 3;
                *exit = false;
            }
        default:
            break;
        }
    }
    return 0;
}
/* Stamap del menu Lost */
bool MainLostMenu(int *x, int b)
{
    char s[WORD] = {};
    bool exit = true;
    int CHOICE_LOST_MENU = 0;
    PrintBanner(LOST_FILE, columns, &y);
    sprintf(s, "Score: %i", (b)*5);
    PrintMiddle(s, columns, &y, 2);
    PrintRowMenu(&choice.lost_menu, &CHOICE_LOST_MENU, "Save Score", columns, &y, 2);
    PrintRowMenu(&choice.lost_menu, &CHOICE_LOST_MENU, "Try Again", columns, &y, 2);
    PrintRowMenu(&choice.lost_menu, &CHOICE_LOST_MENU, "Back to Main Menu", columns, &y, 2);
    CHOICE_LOST_MENU--;
    GearLostMenu(CHOICE_LOST_MENU, &exit, x);
    return exit;
}
/* Loop menu Lost */
int LostMenu(int b)
{
    int x = 0;
    system("COLOR 0F");
    clear();
    choice.lost_menu = 0;
    do
    {
        y = Responsitive(&columns, &rows, &old_columns, &old_rows, 30, 10, true);
    } while (MainLostMenu(&x, b));
    clear();
    return x;
}
/* Salvataggio dello score su un file txt */
int SaveScore(int b)
{
    char usernames[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(usernames, &username_len);
    FILE *fd;
    int x=-32;
    time_t t;
    time(&t);
    fd=fopen(CLASSIFICA_FILE, "a");
    if( fd==NULL )
    {
        perror("Errore in apertura del file");
        exit(1);
    }
    if (strlen(username) == 0)
    {
        fprintf(fd, "%s;%i;%s", usernames, b*5, ctime(&t));
    }
    else
    {
        fprintf(fd, "%s;Points-> %i;%s", username, b*5, ctime(&t));
    }
    fclose(fd);
    return 0;
}

#endif