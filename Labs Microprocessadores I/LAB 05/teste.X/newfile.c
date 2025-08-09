
// Configura??es iniciais
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config BOREN = ON
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config CP = OFF

#include <xc.h>

char contagens;

void __interrupt() ISR(void)
{
    if (INTCON & (1 << 5))
    {
        if (INTCON & (1 << 2))
        {
            TMR0 = 256 - contagens;
            INTCON &= ~(1 << 2);
            RA0 = !RA0;
        }
    }
}

char debounce(char d)
{
		char BOUNCE = 7;    // quantas repeti??es de bounce precisa fazer
	
		char count = 0;		// contagem de bounces
		char last_key = 0;	// ultima tecla guardada para compara??o
		char key_now;		// tecla atual lida
			
		while(count<BOUNCE)		// enquanto contagem for menor do que o n?mero de repeti??es
		{
				key_now = PORTA & 0x0E;

				if(last_key==key_now)		// se uma for igual a outro
				{
					count++;		// aumenta a contagem
				}
				else
				{
					count=0;		// caso contr?rio zera a contagem
				}
				last_key = key_now;		// substitui??o de tecla para compara??o
		}
			
		return key_now;		// devolve a tecla atual na fun??o
}

// Fun??o principal de comandos
void main()
{
	unsigned char key_now;		// Vari?vel para guardar bot?o atual
	unsigned char last_key;		// Vari?vel para guardar ?ltimo bot?o selecionado antes do atual
	unsigned char config=0;           // Vari?vel auxiliar para selecionar o botao que selecionamos

	TRISB = 0;             // Configura todos os pinos de PORTB como sa?da
	TRISA = 0b00001110;    // Configura RA1, RA2 e RA3 como entrada e RA0 e o resto como sa?da

    OPTION_REG = 0x05;      // Prescaler de 64
    
    INTCON = (1 << 7) + (1 << 5);
            
	// Loop de repeti??o que fica lendo o comando
	while (1)
	{
		key_now = PORTA & 0b00001110;	// Guarda o bot?o atual clicado

		// Se bot?o atual for diferente do ?ltimo bot?o clicado, mudar configura??o, caso contr?rio configura??o continua igual
		if (key_now != last_key)
		{
			if (!(debounce(1) & (1 << 1)))	// Clicando em RA1
				config = 1;	// Define configura??o

			else if (!(debounce(2) & (1 << 2)))	// Clicando em RA2
                config = 2;	// Define configura??o

			else if (!(debounce(3) & (1 << 3)))	// Clicando em RA3
				config = 3;	// Define configura??o
		}
        
        // Seleciona a configuracao 
		switch (config){
            case 1: // Onda de 100 Hz
                contagens = 39;
                PORTB = 0b00111000;     // Exibe o n?mero 1 no display de 7 segmentos
                break;
            case 2: // Onda de 200 Hz
                contagens = 20;
                PORTB = 0b11011101;     // Exibe o n?mero 2 no display de 7 segmentos
                break;
            case 3: // Onda de 300 Hz
                contagens = 13;
                PORTB = 0b01111101;     // Exibe o n?mero 3 no display de 7 segmentos
                break;
        }

		last_key = key_now;	// guardar o valor do bot?o atual para compara??o quando voltar ao loop
	}
	return;
}