//
// Created by augusto on 8/26/26.
//

#ifndef DAPONG_PLAYER_LOGIC_H
#define DAPONG_PLAYER_LOGIC_H

typedef struct {
    int x;
    int y;
    int length;
    int speed;
    char type;
} Player;

void player_logic(Player *player, Player *Player2, int p_type);
void gen_player(Player *Player, char type);

#endif //DAPONG_PLAYER_LOGIC_H
