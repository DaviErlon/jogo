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

#define I2C_SDA 14
#define I2C_SCL 15
#define buzzer_B 10
#define buzzer_A 21
#define but_A 5
#define but_B 6

int main(){
    
    stdio_init_all();

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

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
    render_on_display(ssd, &frame_area);

    // Inicialização dos botões
    gpio_init(but_A);
    gpio_init(but_B);
    gpio_set_dir(but_A, GPIO_IN);
    gpio_set_dir(but_B, GPIO_IN);
    gpio_pull_up(but_A);
    gpio_pull_up(but_B);

    // Variaveis

    uint8_t x_nave = 66;  

    while(true){

        while((!gpio_get(but_A)) && (x_nave != 10)){

            draw_nave(ssd, x_nave, false);
            x_nave = x_nave -1;
            draw_nave(ssd, x_nave, true);
            atualizar_balas(ssd, x_nave);
            render_on_display(ssd, &frame_area);
        } 
        while ((!gpio_get(but_B)) && (x_nave != 115)){

            draw_nave(ssd, x_nave, false);
            x_nave = x_nave + 1;
            draw_nave(ssd, x_nave, true);
            atualizar_balas(ssd, x_nave);
            render_on_display(ssd, &frame_area);
        }

        draw_nave(ssd, x_nave, true);
        atualizar_balas(ssd, x_nave);
        render_on_display(ssd, &frame_area);
    }

}