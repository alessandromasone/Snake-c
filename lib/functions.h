#ifndef _SNAKEFUNCTIONS_H_
#define _SNAKEFUNCTIONS_H_

/* Tutte le funzioni sono intere per gestione degli errori */
/* TakeName() */
int TakeName();
/* Initialize() */
int Initialize();
/* InitVar() */
int InitVar();
/* MainMenu() */
bool MainMenu();
int GearMainMenu(int CHOICE_MAIN_MENU, bool *exit);
/* RestoreVar() */
int RestoreVar();
/* SettingMenu() */
int SettingMenu();
/* MainSetting() */
bool MainSetting();
/* GearSettingMenu(Scelte massime del menu, true = non uscita false = uscita, lock = true -> item bloccato lock = false -> item sbloccati) */
int GearSettingMenu(int CHOICE_SETTING_MENU, bool *exit, bool lock);
/* DeBug() */
void DeBug();
/* PrintEasterEgg() */
void PrintEasterEgg();
/* ScanEasterEgg (tasto premuto) */
void ScanEasterEgg (char c);
/* SaveVar() */
int SaveVar();
/* StopLog() */
int StopLog();
/* InitLog(nome del file da creare per il log avviato) */
int InitLog(char *name);
/* InitializeSingleplayer() */
int InitializeSingleplayer();
/* TerminateSingleplayer() */
int TerminateSingleplayer();
/* SinglePlayer() */
int SinglePlayer();
/* *creaSerpente() */
Ser *creaSerpente();
/* *muoviSerpente(testa del serpente, direzione del serprente, true = mangiato false = non mangiato) */
Ser *muoviSerpente(Ser *testa, int direzione, int bocconeMangiato);
/* creaBoccone(corpo del serpente) */
Boc creaBoccone(Ser *p);
/* disegnaCornice() */
int disegnaCornice();
/* disegnaSerpente(Serpente da stampare) */
int disegnaSerpente(Ser *p);
/* collisioneCornice(Serpente) */
int collisioneCornice(Ser *testa);
/* collisioneSeStesso(Serpente) */
int collisioneSeStesso(Ser *testa);
/* fineGioco(Serpente) */
int fineGioco(Ser *testa);
/* Move(old direction) */ 
int Move(int x);
/* GearPauseMenu(Scelte massime del menu, true = non uscita false = uscita, associazione valore con puntatore) */
int GearPauseMenu(int CHOICE_PAUSE_MENU, bool *exit, int *x);
/* MainPauseMenu(associazione valore con puntatore) */
bool MainPauseMenu(int *x);
/* CallPauseMenu() */
int CallPauseMenu();
/* GearLostMenu(Scelte massime del menu, true = non uscita false = uscita, associazione valore con puntatore) */
int GearLostMenu(int CHOICE_LOST_MENU, bool *exit, int *x);
/* MainLostMenu(Associazione valore con puntatore, punti) */
bool MainLostMenu(int *x, int b);
/* LostMenu(punti) */
int LostMenu(int b);
/* SaveScore(punti) */
int SaveScore(int b);
/* InitializeMultyplayer() */
int InitializeMultyplayer();
/* TerminateMultyplayer() */
int TerminateMultyplayer();
/* Multiplayer() */
int Multiplayer();
/* QUANDO QUALCUNO DICE QUESTO LO SO FARE ANCHE IO, VUOL DIRE CHE LO SA RIFARE ALTRIMENTI LO AVREBBE GIA' FATTO PRIMA CIT.BRUNO MUNARI */
/* *creaSerpenteMultiPlayer(posizione x1, posizione y1, posizione x2, posizione y2, posizione x3, posizione y3) */
Ser *creaSerpenteMultiPlayer(int x1, int y1, int x2, int y2, int x3, int y3);
/* MoveMultiplayer(direzione player 1, direzione player 2, precedente direzione player 1, precedente direzione player 2) */
int MoveMultiplayer(int *a, int *b, int old_a, int old_b);
/* OldMoveMultiplayer(precedente direzione player 1, precedente direzione player 2, direzione player 1, direzione player 2) */
int OldMoveMultiplayer(int *old, int *old2, int direzione, int direzione2);
/* collisioneAltro(Testa del serpente player 1, testa del serpente player 2) */
int collisioneAltro(Ser *testa, Ser *testa2);
/* fineGiocoMultiPlayer(Testa del serpente player 1, testa del serpente player 2) */
int fineGiocoMultiPlayer(Ser *testa, Ser *testa2);
/* creaBocconeMultiPlayer(Testa del serpente player 1, testa del serpente player 2) */
Boc creaBocconeMultiPlayer(Ser *p, Ser *pp);
/* CallPauseMenuMultiPlayer() */
int CallPauseMenuMultiPlayer();
/* MainPauseMenuMultiPlayer(Associazione valore con puntatore) */
bool MainPauseMenuMultiPlayer(int *x);
/* CallPauseMenuMultiPlayer() */
int CallPauseMenuMultiPlayer();
/* MainPauseMenuMultiPlayer(Associazione valore con puntatore) */
bool MainPauseMenuMultiPlayer(int *x);
/* LostMenuMultiplayer(Payer vincitore) */
int LostMenuMultiplayer(int n);
/* MainLostMenuMultiPlayer(Associazione valore con puntatore, vincitore) */
bool MainLostMenuMultiPlayer(int *x, int n);
/* ClassificaMenu() */
int ClassificaMenu();
/* MainClassifica() */
int MainClassifica();
/* PrintClassifica() */
int PrintClassifica();

#endif