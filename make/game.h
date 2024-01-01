#ifndef _GAME_H_
#define _GAME_H_

void game_start();
// You have to game_init first.
void game_init(int lv,int player); 
// lv means the AI difficulty (0~12, The higher the number, the smarter the AI), 
// player determines whether the player starts from the upper board (0) or the lower board (1).
#endif