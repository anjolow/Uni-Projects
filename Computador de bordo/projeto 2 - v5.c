/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcdDisplay.h"
#include "tim.h"
#include <stdio.h>
// Definir as opções do menu
#define MENU_OPTION_1 "Vel. Media"
#define MENU_OPTION_2 "Vel. Instant"
#define MENU_OPTION_3 "Hodometro"
#define MENU_OPTION_4 "Alerta de Falha"
#define MENU_OPTION_5 "ALL VIEW"

#define AVG_SLOPE (4.3F)
#define V_AT_25C (1.43F)
#define V_REF_INT (1.2F)

// Array para armazenar o menu
char *menu[] = {MENU_OPTION_1, MENU_OPTION_2, MENU_OPTION_3, MENU_OPTION_4, MENU_OPTION_5};

// Variáveis globais para controlar o índice do menu e a seleção
uint8_t menu_index = 0;
uint8_t menu_length = 5;  // Número de opções no menu
uint8_t menu_selected = 0; // Modo selecionado
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
lcd_t Lcd;
uint8_t seta[8] = {0x00, 0x04, 0x06, 0x1F, 0x1F, 0x06, 0x04, 0x00};

int tela=0, count_temp=0, count_crit=0;
float temp=0, combus=0;
char alerta_temp=0, alerta_combus=0; //flags para indicar se carro está em alerta
char buzz_temp=0, buzz_combus=0; //flags para indicar se deve ou não ligar a buzina/crítico
char flag_pedais=0, flag_velocidade=0, bloq_acelerador=0;
float vel_instantanea=0.0f, vel_media=0.0f, velo_ant=0.0f;
float hodometro=0, autonomia=0.0f, autonomia_aux=0.0f, combustivel=0.0f;
float nivel_combus = 0.0f; // Nível do tanque, em litros
float injecao_combust=0.0f;
char buzina=0, est=1; //flag para identificar buzina ligada

volatile uint8_t buzzer_active = 1;
volatile uint32_t timer8_counter = 0;

uint16_t AD_RES[2];
float V_Sense, V_Ref;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void MX_TIM6_Init(); // Timer 6: 20ms
void MX_TIM7_Init(); // Timer 7: 50ms
void MX_TIM4_Init(); // Timer 4: 500ms
void MX_TIM2_Init(); // Timer 2: 2s
void MX_TIM15_Init(); // Timer 5: 100ms
void MX_TIM1_Init(); // Timer 1: PWM 20ms
void MX_TIM3_Init(); // TImer 3: PWM 800Hz
void MX_TIM8_Init(); // Timer 8: 2s on, 30s off

//declarações de funções
void att_monitor();
void opcao_disponivel();
void prox_opcao();
void retorno_opcao();
void medidor_temperatura();
void alerta_led();
void buzzer();
void sit_critica();
void interrupt_500ms();
void sensor_pedal();
void medidores ();
void calculo_combustivel();
void autonomia_veiculo();
void atualiza_nivel_combus();

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Callback de interrupções dos timers
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) { // Timer 6: 20ms
        calculo_combustivel();
    } 
    else if (htim->Instance == TIM7) { // Timer 7: 50ms
        medidor_temperatura();
    } 
    else if (htim->Instance == TIM4) { // Timer 4: 500ms
        interrupt_500ms();
    } 
    else if (htim->Instance == TIM2) { // Timer 2: 2s
        autonomia_veiculo();
    } 
    else if (htim->Instance == TIM15) { // Timer 5: 100ms
        atualiza_nivel_combus();
    }
    else if (htim->Instance == TIM8 && buzina) {
        timer8_counter++;

        if (buzzer_active) {
            if (timer8_counter >= 2000) { // Desativa após 2 segundos
                HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
                buzzer_active = 0;
                timer8_counter = 0;
            }
        } else {
            if (timer8_counter >= 28000) { // Ativa após 28 segundos
                HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
                buzzer_active = 1;
                timer8_counter = 0;
            }
        }
    }
}

//=================================================================================================================
void lcd_inicio(){
	Lcd.columns = 16;
	Lcd.rows = 2;
	Lcd.font = LCD_FONT_5X8;
	Lcd.interface = LCD_INTERFACE_4BIT;

	Lcd.gpios[LCD_RS].GPIO = (uint32_t) LCD_RS_GPIO_Port;
	Lcd.gpios[LCD_RS].pin = LCD_RS_Pin;
	Lcd.gpios[LCD_E].GPIO = (uint32_t) LCD_E_GPIO_Port;
	Lcd.gpios[LCD_E].pin = LCD_E_Pin;
	Lcd.gpios[LCD_D4].GPIO = (uint32_t) LCD_D4_GPIO_Port;
	Lcd.gpios[LCD_D4].pin = LCD_D4_Pin;
	Lcd.gpios[LCD_D5].GPIO = (uint32_t) LCD_D5_GPIO_Port;
	Lcd.gpios[LCD_D5].pin = LCD_D5_Pin;
	Lcd.gpios[LCD_D6].GPIO = (uint32_t) LCD_D6_GPIO_Port;
	Lcd.gpios[LCD_D6].pin = LCD_D6_Pin;
	Lcd.gpios[LCD_D7].GPIO = (uint32_t) LCD_D7_GPIO_Port;
	Lcd.gpios[LCD_D7].pin = LCD_D7_Pin;

	lcd_init(&Lcd);

}


// Função para atualizar o menu exibido no LCD
void Update_LCD(void) {
	int contador;
	char texto[17];
	char linha = 0;
	char coluna = 0;

	lcd_send_char_pos(&Lcd, LCD_CUSTOM_1, 0, 0);
	lcd_send_string_pos(&Lcd, menu[menu_index], 0, 1);
	lcd_send_string_pos(&Lcd, menu[(menu_index + 1) % menu_length], 1, 0);
}



void lcd_caractere(){
	lcd_create_custom_char(&Lcd, LCD_CUSTOM_1, seta);
}

int num_digits(int num) {
    int digits = 0;
    do {
        digits++;
        num /= 10;
    } while (num > 0);
    return digits;
}

// Função para verificar o estado dos botões e navegar pelo menu
void Check_Button_Input(void) {
    static uint32_t last_press_time = 0;  // Para armazenar o tempo da última leitura válida
    uint32_t current_time = HAL_GetTick();  // Tempo atual em milissegundos
    // Verifica o botão
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET) {
    	lcd_send_string_pos(&Lcd, "                ", 0, 0);
    	lcd_send_string_pos(&Lcd, "                ", 1, 0);
        // Verifica se já passou o tempo do debounce
        if ((current_time - last_press_time) > 100) {  // 100 ms de debounce
            menu_index++;
            HAL_Delay(200);
            if (menu_index >= menu_length) {
                menu_index = 0;  // Volta ao início
            }
            last_press_time = current_time;  // Atualiza o tempo da última leitura
        }
    }
}
//=================================================================================================================

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//==============================================================================

//==============================================================================
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  // Inicializar periféricos configurados no CubeMX
  MX_TIM6_Init(); // Timer 6: 20ms
  MX_TIM7_Init(); // Timer 7: 50ms
  MX_TIM4_Init(); // Timer 4: 500ms
  MX_TIM2_Init(); // Timer 2: 2s
  MX_TIM15_Init(); // Timer 5: 100ms
  MX_TIM1_Init(); // Timer 1: PWM 20ms
  MX_TIM3_Init(); // TImer 3: PWM 800Hz
  MX_TIM8_Init(); // Timer 8: 2s on, 30s off
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

    // Iniciar os timers com interrupções
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim15);
    HAL_TIM_Base_Start_IT(&htim8);

   //==============================================================================
  lcd_inicio();
  lcd_caractere();

  lcd_clear_all (&Lcd);
  HAL_Delay(1000);
  lcd_send_string_pos(&Lcd, "COMPUTADOR", 0, 2);
  lcd_send_string_pos(&Lcd, "DE BORDO", 1, 3);
  HAL_Delay(2000);
  lcd_clear_all (&Lcd);

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

  HAL_ADC_Start (&hadc1);
  int radc = HAL_ADC_GetValue(&hadc1);

  int contador = 0;
  int contador1 = 0;
  char texto[17];
  char texto1[17];
  char linha = 0;
  char coluna = 0;
  int digits = num_digits(contador);
  // Define a posição inicial para alinhamento à direita
  int start_position = 6 - digits;
  //==============================================================================
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Update_LCD();
	  //Check_Button_Input();
	  Check_Button_Input();

	  char j = 1;
        /* Verifica se uma opção foi selecionada */
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET)
        {
        // Ações baseadas na opção selecionada usando switch-case
            char c = 1;
            while(c == 1){

            int digits = num_digits(contador);
            // Define a posição inicial para alinhamento à direita
            int start_position = 6 - digits;

            switch(menu_index)
            {
                case 0:
                // Realiza ação para a Opção 1
                    lcd_clear_all(&Lcd);
                    lcd_send_string_pos(&Lcd, "VELOCIDADE MEDIA", 0, 0);
                    lcd_send_string_pos(&Lcd, "Vm=", 1, 0);
                    lcd_send_string_pos(&Lcd, "   ", 1, start_position);
                    sprintf(texto, "%d", vel_media);
                    lcd_send_string_pos(&Lcd, texto, 1, start_position);
                    lcd_send_string_pos(&Lcd, "Km/h", 1, 7);
                    HAL_Delay(100);  // Aguarda 500 milissegundos
                    break;

                case 1:
                    // Realiza ação para a Opção 2
                    lcd_clear_all(&Lcd);
                    lcd_send_string_pos(&Lcd, "VELOCIDADE INST", 0, 0);
                    lcd_send_string_pos(&Lcd, "Vi=", 1, 0);
                    lcd_send_string_pos(&Lcd, "   ", 1, start_position);
                    sprintf(texto, "%d", vel_instantanea);
                    lcd_send_string_pos(&Lcd, texto, 1, start_position);
                    lcd_send_string_pos(&Lcd, "Km/h", 1, 7);
                    HAL_Delay(100);  // Aguarda 500 milissegundos
                    break;

                case 2:
                    // Realiza ação para a Opção 3
                    lcd_clear_all(&Lcd);
                    lcd_send_string_pos(&Lcd, "HODOMETRO", 0, 0);
                    lcd_send_string_pos(&Lcd, "D=", 1, 0);
                    lcd_send_string_pos(&Lcd, "   ", 1, start_position);
                    sprintf(texto, "%d", hodometro);
                    lcd_send_string_pos(&Lcd, texto, 1, start_position);
                    lcd_send_string_pos(&Lcd, "m", 1, 7);
                    HAL_Delay(100);  // Aguarda 500 milissegundos
                    break;

                case 3:
                    // Realiza ação para a Opção 4
                    
                    lcd_clear_all(&Lcd);
                    lcd_send_string_pos(&Lcd, "ALERTA DE FALHA", 0, 0);
                    lcd_send_string_pos(&Lcd, "ESTADO:", 1, 0);

                    if(est == 1)
                        lcd_send_string_pos(&Lcd, "OK", 1, 8);
                    else if(est == 2)
                        lcd_send_string_pos(&Lcd, "TEMP ALTA", 1, 7);
                    else if(est == 3)
                        lcd_send_string_pos(&Lcd, "CRITICO", 1, 8);

                    HAL_Delay(500);
                    break;

                case 4:
                    // Realiza ação para a Opção 5
                    if(j == 1){
                    lcd_clear_all(&Lcd);
                    lcd_send_string_pos(&Lcd, "Vm[Km/h]", 0, 0);
                    lcd_send_string_pos(&Lcd, "Vi[Km/h]", 1, 0);
                    lcd_send_string_pos(&Lcd, "HOD[m]", 0, 9);
                    lcd_send_string_pos(&Lcd, "AF", 1, 12);
                    HAL_Delay(3000);}
                    j = 0;

                    lcd_send_string_pos(&Lcd, "                ", 0, 0);
                    lcd_send_string_pos(&Lcd, "                ", 1, 0);
                    lcd_send_string_pos(&Lcd, "   ", 0, start_position-2);
                    sprintf(texto, "%d", vel_media);
                    lcd_send_string_pos(&Lcd, texto, 0, start_position-2);

                    lcd_send_string_pos(&Lcd, "   ", 1, start_position-2);
                    sprintf(texto1, "%d", vel_instantanea);
                    lcd_send_string_pos(&Lcd, texto1, 1, start_position-2);

                    lcd_send_string_pos(&Lcd, "   ", 0, start_position+5);
                    sprintf(texto1, "%d", hodometro);
                    lcd_send_string_pos(&Lcd, texto1, 0, start_position+5);

                    lcd_send_string_pos(&Lcd, "   ", 1, start_position+5);
                    if(est == 1)
                        lcd_send_string_pos(&Lcd, "OK", 1, start_position+5);
                    else if(est == 2)
                        lcd_send_string_pos(&Lcd, "ALTA", 1, start_position+5);
                    else if(est == 3)
                        lcd_send_string_pos(&Lcd, "CRIT", 1, start_position+5);

                    HAL_Delay(500);
                    break;

                default:
                    // Caso inválido, pode adicionar uma ação de erro
                    lcd_clear_all(&Lcd);
                    lcd_send_string_pos(&Lcd, "Opção Invalida", 0, 0);
                    break;
            }
            // Verifica se o botão foi pressionado para sair
                if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET) {
                HAL_Delay(100);  // Debounce do botão
                c = 0;  // Sai do menu

                // Após sair do menu, limpa o display
                lcd_send_string_pos(&Lcd, "                ", 0, 0);
                lcd_send_string_pos(&Lcd, "                ", 1, 0);
              }
	        }
	    }
	  // Após a seleção, reseta a flag de seleção


	  /* Verifica o estado do botão */
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)== GPIO_PIN_SET)  // O botão foi pressionado (nível lógico baixo)
        {
        /* Acende o LED */
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
        }else
        {
        /* Apaga o LED */
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
        }

        /* Delay para evitar leitura repetida excessiva */
        HAL_Delay(100);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin
                          |LCD_E_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(saida_GPIO_Port, saida_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_D7_Pin LCD_D6_Pin LCD_D5_Pin LCD_D4_Pin
                           LCD_E_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin
                          |LCD_E_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : bot_o_naveg_Pin */
  GPIO_InitStruct.Pin = bot_o_naveg_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(bot_o_naveg_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : saida_Pin */
  GPIO_InitStruct.Pin = saida_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(saida_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */

    /* Configura PC1 (TIM1_CH2) */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;  // Função alternativa para TIM1_CH2
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Configura PB0 (TIM3_CH1) como saída alternada */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void att_monitor(){ //atualiza computador de bordo, chamada a cada 0.5s
    alerta_led();
    buzzer();
    sit_critica();
}

void medidor_temperatura(){
   
    char led = 0, critical = 0;

    V_Ref = (float)((V_REF_INT * 4095.0)/AD_RES[0]);
    V_Sense = (float)(AD_RES[1] * V_Ref)/4095.0;
    temp = (((V_AT_25C - V_Sense) * 1000.0) /AVG_SLOPE);

    if(temp > 35){  //se temperatura maior que 35°C
        count_temp++;
       
        if(count_temp > 4){ //se teve 5 leituras de temperatura alta seguidas
            count_temp = 5;
            led = 1; //liga o led amarelo de alerta
           
            if(temp >= 50){
                est = 3;
                critical = 1; //indica que está em condição crítica pra buzina
            }
            else{
                est = 2;
            }
        }
    }
    else{ //não está com temperatura alta
       
        count_temp = 0;
       
        est = 1;
    }
   
    alerta_temp = led; //define se liga ou não o led de alerta
    buzz_temp = critical; //define se liga ou não a buzina
}

void alerta_led(){
    if(alerta_temp || alerta_combus)
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); //liga led amarelo
    else
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); //desliga led amarelo
}

void buzzer(){
    if(buzz_temp){ //está crítico
        buzina = 1;
        count_crit++;
    }
    else{
        buzina = 0;
        count_crit = 0;
    }
}

void sit_critica(){ //situação crítica 
   
    if(count_crit >= 360){ //somado em buzzer, chamada a cada 0.5s, logo, 360 contagens = 3min
        count_crit = 361;
        bloq_acelerador = 1; //bloqueia pedal do acelerador
    }
    else
        bloq_acelerador = 0; //libera pedal do acelerador
}

void interrupt_500ms(){ //chama funções a cada 0.5s
   
    sensor_pedal();
    medidores ();
    att_monitor();
}

void sensor_pedal(){ //verifica pedais e altera a injeção

    if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == GPIO_PIN_SET){ //pressionou freio -> diminui 50%

        flag_pedais = 1; //tem um pedal pressionado
   
        if(injecao_combust > 0.5)
            injecao_combust = injecao_combust - 0.5;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (injecao_combust*(htim1.Instance->ARR)));
        else
            injecao_combust = 0;
    }
    else if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6) == GPIO_PIN_SET){ //pressionou acelerador -> aumenta 10%

        if(!(bloq_acelerador)){ //se passar 3min críticos, bloqueia acelerador
           
            flag_pedais = 1; //tem um pedal pressionado
           
            if(injecao_combust < 0.9)
                injecao_combust = injecao_combust + 0.1;

            else
                injecao_combust = 1; //nível máximo

            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (injecao_combust*(htim1.Instance->ARR)));
        }
    }
    else{ //nada pressionado -> diminui 10% a cada 1s


        if(flag_pedais == 1) //antes tinha um pedal pressionado
            flag_pedais = 0;
        else{ //2x sem pressionar -> passou 1s -> diminui 10%
            flag_pedais = 1;
           
            if(injecao_combust > 0.1)
                injecao_combust = injecao_combust - 0.1;

            else
                injecao_combust = 0;

            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (injecao_combust*(htim1.Instance->ARR)));
        }
    }


    printf("Injecao:  %.2f\n", injecao_combust);
}

void medidores (){ //calcula velocidades, hod^metro e outros
   
    vel_instantanea = injecao_combust*100; //velocidade instantânea, em km/h
   
    if(flag_velocidade){ //calculos feitos a cada 1s
       
        vel_media = (vel_instantanea + velo_ant)/2; //velocidade média, em km/h
        hodometro = hodometro + vel_media/3.6; //hodômetro, em m
        autonomia_aux = autonomia_aux + (vel_media/3600); //soma distância percorrida em 1s, em km, para calculo da autonomia
    }
   
    flag_velocidade = !flag_velocidade;
    velo_ant = vel_instantanea; //salva a velocidade anterior
   
}

void calculo_combustivel(){
   
    char inject_times;
   
    if(injecao_combust > 0){
       
        combustivel = combustivel + 4; //4ul a cada 2ms da injeção

    }
}

void autonomia_veiculo(){ //chamada a cada 2s
   
    combustivel = combustivel/pow(10,6); //de ul para litros
   
    if((autonomia_aux > 0) && (combustivel > 0))
        autonomia = autonomia_aux/combustivel; //em km/l
    else
        autonomia = 0;
   
    autonomia_aux = 0; //zera variáveis para novo cálculo de autonomia
    combustivel = 0;
}

// Função para calcular o nível de combustível
void atualiza_nivel_combus(){
    //float potenciometro = potenciometro_maquete.read(); // Lê o valor analógico (0.0 a 1.0)
    nivel_combus = potenciometro * 50.0f; // Mapeia para a escala de 0L a 50L
    if(nivel_combus < 4)
    {
        alerta_combus = 1;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuração do TIM1 para PWM (20ms)
void MX_TIM1_Init(void) {
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* Configuração do timer */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 15;             // Prescaler para 1 MHz
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 19999;             // Período para 20ms (50 Hz)
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;      // Repetição (para PWM complementar)
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
        Error_Handler();
    }

    /* Configuração do PWM no canal 1 */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;     // Modo PWM 1
    sConfigOC.Pulse = 0;                // Valor inicial do CCR (0% duty cycle)
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
        Error_Handler();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuração do TIM3 para PWM (800Hz)
void MX_TIM3_Init(void) {
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* Configuração do TIM3 para PWM */
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 15;             // Prescaler para 1 MHz
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 1249;              // Período para 800 Hz
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }

    /* Configuração do PWM no canal 1 */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 625;                // 50% duty cycle
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK) {
        Error_Handler();
    }
}

void MX_TIM8_Init(void) {
    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 15999;         // Prescaler para 1 kHz
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 29999;            // Período total de 30 segundos
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim8) != HAL_OK) {
        Error_Handler();
    }

    /* Ativa interrupção */
    HAL_TIM_Base_Start_IT(&htim8);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* TIM6: 20ms */
void MX_TIM6_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 15;             // Prescaler para 1MHz
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 19999;              // 20ms = (15 + 1) * (19999 + 1) / 16MHz
    htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim6, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

/* TIM7: 50ms */
void MX_TIM7_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 15;             // Prescaler para 1MHz
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim7.Init.Period = 49999;              // 50ms = (999 + 1) * (49999 + 1) / 16MHz
    htim7.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim7) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim7, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

/* TIM4: 500ms */
void MX_TIM4_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 15999;  // Freq. base: 1kHz
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 499;   // 500ms = (15999 + 1) * (499 + 1) / 16MHz
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

/* TIM2: 2s */
void MX_TIM2_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 15999;             // Prescaler para 1kHz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1999;            // 2s = (15999 + 1) * (1999 + 1) / 16MHz
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

/* TIM5: 100ms */
void MX_TIM5_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 15999;             // Prescaler para 1kHz
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 99;              // 100ms = (15999 + 1) * (99 + 1) / 16MHz
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim5) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
