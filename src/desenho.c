#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <time.h>
#include "jogo.h"

void draw_nave(uint8_t *ssd, uint8_t x, bool set){ //função que desenha a nave
ssd1306_draw_line(ssd, x, 60, x, 48, set);
ssd1306_draw_line(ssd, x -1, 59 , x -1 , 50, set);  
ssd1306_draw_line(ssd, x -2, 59, x -2 , 51, set);
ssd1306_draw_line(ssd, x -3, 57, x -3 , 53, set);
ssd1306_draw_line(ssd, x -4, 57, x -4 , 54, set);
ssd1306_draw_line(ssd, x -5, 57, x -5 , 53, set);
ssd1306_draw_line(ssd, x -6, 57, x -6 , 53, set);
ssd1306_draw_line(ssd, x -7, 57, x -7 , 56, set);
ssd1306_draw_line(ssd, x -8, 57, x -8 , 57, set);
ssd1306_draw_line(ssd, x +1, 60, x +1 , 48, set);
ssd1306_draw_line(ssd, x +2, 59, x +2 , 50, set);  
ssd1306_draw_line(ssd, x +3, 59, x +3 , 51, set);
ssd1306_draw_line(ssd, x +4, 57, x +4 , 53, set);
ssd1306_draw_line(ssd, x +5, 57, x +5 , 54, set);
ssd1306_draw_line(ssd, x +6, 57, x +6 , 53, set);
ssd1306_draw_line(ssd, x +7, 57, x +7 , 53, set);
ssd1306_draw_line(ssd, x +8, 57, x +8 , 56, set);
ssd1306_draw_line(ssd, x +9, 57, x +9 , 57, set);
}

uint8_t tiros[10][2] = { //coordenadas das balas
    {0, 50},
    {0, 45},
    {0, 40},
    {0, 35},
    {0, 30},
    {0, 25},
    {0, 20},
    {0, 15},
    {0, 10},
    {0, 5}
    };

void tiros_apagar(uint8_t *ssd){

    for(uint8_t i = 0; i < 10; i++){
        ssd1306_draw_line(ssd, tiros[i][0] -4, tiros[i][1], tiros[i][0] -5, tiros[i][1], false);
        ssd1306_draw_line(ssd, tiros[i][0] +5, tiros[i][1], tiros[i][0] +6, tiros[i][1], false);
    }
} 

void tiros_colocar(uint8_t *ssd, uint8_t x_nave){

    tiros[0][0] = x_nave;
    for(uint8_t i = 9; i > 0; i--){
        tiros[i][0] = tiros[i-1][0];
    }
    for(uint8_t i = 0; i < 10; i++){
        ssd1306_draw_line(ssd, tiros[i][0] -4, tiros[i][1], tiros[i][0] -5, tiros[i][1], true);
        ssd1306_draw_line(ssd, tiros[i][0] +5, tiros[i][1], tiros[i][0] +6, tiros[i][1], true);
    }
}

void atualizar_balas(u_int8_t *ssd, uint8_t x_nave){
    tiros_apagar(ssd);
    tiros_colocar(ssd, x_nave);
}