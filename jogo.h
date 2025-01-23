#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <time.h>

void draw_nave(uint8_t*, uint8_t, bool);
void tiros_apagar(uint8_t*);
void tiros_colocar(uint8_t*, uint8_t);
void atualizar_balas(u_int8_t*, uint8_t);


#endif

