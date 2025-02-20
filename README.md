# Semáforo Inteligente para pedestres

## Descrição
Este projeto implementa um semáforo inteligente utilizando um display OLED SSD1306 e um microcontrolador compatível com Raspberry Pi Pico. O sistema controla LEDs para indicar o status do semáforo e exibe mensagens informativas no display OLED. Ele também inclui botões que podem ser acionados para alterar o estado do semáforo de forma interativa, simulando o comportamento de um pedestre antes de atravessar a rua.

## Funcionalidades
- Controle de LEDs para indicar os estados do sinal de pedestres como "Aberto" (verde) ou "Fechado" (vermelho).
- Exibição de mensagens no display OLED para auxiliar os pedestres.
- Detecção de botões para permitir a solicitação de travessia.
- Temporização automática dos estados do semáforo.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico ou similar
- **Display OLED:** SSD1306 (com interface I2C)
- **LEDs:** Indicadores para os estados vermelho e verde
- **Botões:** Entrada para interação do pedestre
- **Resistores:** Para ajuste de corrente nos LEDs
- **Fios e protoboard:** Para conexões elétricas

## Conexões
| Componente  | Pino do Microcontrolador |
|-------------|-------------------------|
| OLED SDA    | GP14 |
| OLED SCL    | GP15 |
| LED Verde   | GP11 |
| LED Vermelho| GP13 |
| Botão A    | GP5  |
| Botão B    | GP6  |

## Instalação e Configuração
1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/semaforo-inteligente.git
   ```
2. Compile o código e transfira para o microcontrolador.
3. Conecte os componentes conforme o esquema acima.
4. Ligue o sistema e acompanhe a mudança de estados no display OLED.

## Como Funciona
1. O sistema inicia com o **sinal vermelho ativado**.
2. Se um pedestre pressionar um dos botões, uma mensagem de "Aguarde" é exibida.
3. Após um tempo de espera, o **sinal verde é ativado** por 8 segundos.
4. O ciclo se repete continuamente.

## Exemplo de Saída no OLED
```
  SINAL FECHADO  
  AGUARDE  
```
```
  SINAL ABERTO  
  ATRAVESSE  
  COM CUIDADO  
```

## Simulação pronta no Wokwi
- Acesse [Wokwi](https://wokwi.com/projects/420885549333762049).

## Licença
Este projeto é de código aberto sob a licença MIT. Sinta-se à vontade para modificar e compartilhar!

## Autor
Desenvolvido por Lucas Pereira Castanheira Nascimento.

