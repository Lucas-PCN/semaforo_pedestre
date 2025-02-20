#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

// Definições dos pinos
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15
#define LED_R_PIN 13
#define LED_G_PIN 11
#define BTN_A_PIN 5
#define BTN_B_PIN 6

// Configurações do display OLED
const uint I2C_SDA = I2C_SDA_PIN;
const uint I2C_SCL = I2C_SCL_PIN;

// Variáveis globais para o display OLED
uint8_t ssd_buffer[ssd1306_buffer_length];
struct render_area frame_area;

// Inicializa o display OLED
void init_oled() {
    i2c_init(i2c1, 100 * 1000); // Configura a comunicação I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(); // Inicializa o display OLED

    // Configura a área de renderização
    frame_area.start_column = 0;
    frame_area.end_column = ssd1306_width - 1;
    frame_area.start_page = 0;
    frame_area.end_page = ssd1306_n_pages - 1;

    calculate_render_area_buffer_length(&frame_area);

    // Limpa o display
    memset(ssd_buffer, 0, ssd1306_buffer_length);
    render_on_display(ssd_buffer, &frame_area);
}

// Função para exibir mensagens no OLED
void display_messages(const char *messages[], int count) {
    memset(ssd_buffer, 0, ssd1306_buffer_length); // Limpa o buffer

    int y = 0; // Posição vertical inicial
    for (int i = 0; i < count; i++) {
        ssd1306_draw_string(ssd_buffer, 5, y, (char *)messages[i]); // Desenha cada linha
        y += 8; // Move para a próxima linha
    }

    // Renderiza o conteúdo no display
    render_on_display(ssd_buffer, &frame_area);
}

// Função para esperar e verificar o botão
int WaitWithRead(int timeMS) {
    for (int i = 0; i < timeMS / 10; i++) {
        if (!gpio_get(BTN_A_PIN) || !gpio_get(BTN_B_PIN)) { // Verifica se o botão foi pressionado
            return 1;
        }
        sleep_ms(10);
    }
    return 0;
}

// Funções do semáforo
void SinalVerde() {
    gpio_put(LED_R_PIN, 0);       // Desliga o LED vermelho
    gpio_put(LED_G_PIN, 1);       // Liga o LED verde
    const char *messages[] = {
        "  SINAL ABERTO   ",
        "  ATRAVESSE   ",
        "  COM CUIDADO   "
    };
    display_messages(messages, 3);
}

void SinalVermelho() {
    gpio_put(LED_R_PIN, 1);       // Liga o LED vermelho
    gpio_put(LED_G_PIN, 0);       // Desliga o LED verde
    const char *messages[] = {
        "  SINAL FECHADO   ",
        "  AGUARDE   "
    };
    display_messages(messages, 2);
}

int main() {
    // Inicialização de GPIOs
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);

    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);

    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_B_PIN);

    // Inicialização do OLED
    init_oled();

    while (true) {
        // Inicia no sinal vermelho
        SinalVermelho();
        int button_pressed = WaitWithRead(13000); // Aguarda 13 segundos (tempo vermelho)

        if (button_pressed) {
            // Caso o botão seja pressionado, espera 5 segundos antes do sinal verde
            const char *messages[] = {
                "  BOTAO   ",
                "  PRESSIONADO   ",
                "  AGUARDE   "
            };
            display_messages(messages, 3);
            sleep_ms(5000);
        }

        // Ativa o sinal verde
        SinalVerde();
        sleep_ms(8000); // Duração de 8 segundos do sinal verde
    }

    return 0;
}

