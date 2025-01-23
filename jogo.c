#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <time.h>

#define I2C_SDA 14
#define I2C_SCL 15
#define buzzer_B 10
#define buzzer_A 21
#define but_A 5
#define but_B 6

void inverter(uint8_t *ssd){
    for(uint16_t i = 0; i < 1024; i++){
        ssd[i] = ~(ssd[i]);
    }
}

uint8_t tempo(){
    static float temp = 0.0;
    static float ult = 0.0;

    float atual = ((float)(clock()) / CLOCKS_PER_SEC);
    float decor = atual - ult;

    temp += decor;
    ult = atual;

    if(temp > 1.0){
        temp -= (int)temp;
        return 1;
    } else {
        return 0;
    }
}

void inicial(uint8_t *ssd, struct render_area* frame_area){

    uint8_t pointer = 0;
    ssd1306_draw_string(ssd, 16, 22, "JOGO DE DAVI");
    ssd1306_draw_string(ssd, 24, 38, "A iniciar");
    ssd1306_set_pixel(ssd, 34, 38, true);
    sleep_ms(20);
    inverter(ssd);
    sleep_ms(20);
    render_on_display(ssd, frame_area);

    while(true){
    ssd1306_draw_line(ssd, 16, 32, 19, 32, pointer);
    ssd1306_draw_line(ssd, 16, 33, 20, 33, pointer);
    ssd1306_draw_line(ssd, 16, 34, 21, 34, pointer);
    ssd1306_draw_line(ssd, 16, 35, 20, 35, pointer);
    ssd1306_draw_line(ssd, 16, 36, 19, 36, pointer);
    if(tempo()){
        pointer = ~pointer;
        sleep_ms(20);
        render_on_display(ssd, frame_area);
    }
        if(!gpio_get(but_A)){
            break;
        }
    }
}

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

int main(){
    
    stdio_init_all();

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização dos botões
    gpio_init(but_A);
    gpio_init(but_B);
    gpio_set_dir(but_A, GPIO_IN);
    gpio_set_dir(but_B, GPIO_IN);
    gpio_pull_up(but_A);
    gpio_pull_up(but_B);

    // Variaveis

    uint8_t x_nave = 66;

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);

    inicial(ssd, &frame_area);

    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
    sleep_ms(100);

    while(true){

        if ((!gpio_get(but_A)) && (x_nave != 10)){
            draw_nave(ssd, x_nave, false);
            x_nave = x_nave -1;
        }

        if ((!gpio_get(but_B)) && (x_nave != 116)){
            draw_nave(ssd, x_nave, false);
            x_nave = x_nave + 1;
        }
        
        draw_nave(ssd, x_nave, true);
        render_on_display(ssd, &frame_area);
        atualizar_balas(ssd, x_nave);
    }

}