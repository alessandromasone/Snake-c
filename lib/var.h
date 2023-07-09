#ifndef _SNAKEVAR_H_
#define _SNAKEVAR_H_

/* typedef per i valori grafici */
typedef struct _valori
{
    int speed; 
    int color_head; 
    int color_body; 
    int color_background; 
    int color_boccone; 
    int color_frame; 
    int type_head; 
    int type_boccone; 
    int type_body; 
    int frame_up; 
    int frame_side;
    int frame_angle_up_dx; 
    int frame_angle_down_dx; 
    int frame_angle_up_sx;
    int frame_angle_down_sx; 
}valori;
/* typedef per le scelte generali delle preferenze */
typedef struct _scelte
{
	int main_menu;
    int pause_menu;
    int difficulty;
    int setting_menu;
    int lost_menu;
    int color_head;
    int color_body;
    int color_background;
    int color_frame;
    int color_boccone;
    int type_head;
    int type_body;
    int type_frame;
    int type_boccone;
}scelte;
/* typedef dei nomi */
typedef struct _nome
{
    char difficulty[WORD];
    char color_head[WORD];
    char color_body[WORD];
    char color_background[WORD];
    char color_frame[WORD];
    char color_boccone[WORD];
}nome;
/* typedef per i colori */
typedef struct _tempc
{
    int head;
    int body;
    int background;
    int frame;
    int boccone;
    char backgroud_cmd[WORD];
}tempc;
/* typedef per il boccone */
typedef struct boccone
{
	int x;
	int y;
} Boc;
/* typedef per il serpente */
typedef struct serpente
{
	int x;
	int y;
	struct serpente *prossimo;
} Ser;

valori value;
scelte choice;
nome name;
tempc color;

int CAMPO_GIOCO_X;
int CAMPO_GIOCO_Y;

int easteregg[N_EASTEREGG] = {};
char buffereasteregg[WORD] = {}; 
int columns, rows, old_columns, old_rows, y;
bool music;
int points = 0;
char username[WORD] = {};
int padding_columns;
int padding_rows;

#endif