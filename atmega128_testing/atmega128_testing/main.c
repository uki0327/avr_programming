/*
 * Atmega128_20201218_Test_Q2.c
 *
 * Created: 2020-12-18 오전 11:51:41
 * Author : 이장욱
 * [문제2] LED가 500ms 간격으로 (PC0 ~ PC7) 켜지도록 
 * 반복하는 프로그램을 쉬프트 연산자를 활용하여 작성하세요.
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000L

char ledState = 0xFE;

void shiftLed() {
	if(ledState == 0b01111111) {
		ledState = 0b11111110;
	} else {
		ledState = (ledState << 1) + 1;
	}
}

int main(void)
{
    DDRC = 0xFF;
	PORTC = 0xFF;
	
    while (1) 
    {
		PORTC = ledState;
		_delay_ms(5000);
		shiftLed();
    }
}

