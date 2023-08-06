#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint64_t board;
typedef bool map[64];
typedef char constraint[8];

struct problem {
    board monsters;
    board treasures;
    constraint rows;
    constraint columns;
};

problem p = {
    .monsters = 0x8000800080048000,
    .treasures = 0x20000000000,
    .rows = { 3,2,5,3,4,1,4,4 },
    .columns = { 1,4,2,7,0,4,4,4 }
};

typedef struct problem problem;

int map_to_board(map m){
    int r = 0;
    for(int i=0;i<8*8;i++)
        r |= m[i] * (1<<i);
    return r;
}

void board_to_map(board b, map m){
    for(int i=0;i<8*8;i++)
        m[i] = ((1<<i) & b) >> i ;
}

int main(void){
    board mb = 0x8000800080048000;
    map mm = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1,
    };
    bool mm2[64] = {};
    board_to_map(mb,mm2);
    printf("%d\n",map_to_board(mm2)-mb);
    return 0;
}
