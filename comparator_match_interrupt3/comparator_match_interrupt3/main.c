#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L

volatile int count = 0;
int state = 0;

ISR(TIMER1_COMPA_vect) {
	TCNT1 = 0;
	
	state = !state;
	if(state) PORTD = 0x00;
	else PORTD = 0xFF;
}

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	/* 16Mhz 클록을 1024로 분주한 경우 타이머/카운터에 공급되는 클록은
		1초에 16K 개가 되며, 0.5초가 경과하기 위해서는 8K 개의 클록이 필요하다.\
		따라서 OCR1A 레지스터에 비교일치가 발생하는 값은,
		8 x 2 (10승) =  8192 = 0x2000 으로 설정한다.
	*/
	OCR1A = 0x0080;
	
	TIMSK1 |= (1 << OCIE1A);
	sei();
	
	while (1)
	{
		
	}
}
