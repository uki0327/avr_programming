#define F_CPU 16000000UL
 
//1. baud rate를 선택
#define USART_BAUDRATE 9600
 
//2.시스템 클록과 원하는 baud rate를 이용하여 UBRR 값을 계산한다.
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
 
 
#include <avr/io.h>
#include <stdio.h>
 
 
void usartInit()
{
    //3. UBRR0은 16비트 레지스터이기 때문에 8비트씩 나누어서 넣어야 한다.
    UBRR0H = (uint8_t)(UBRR_VALUE>>8);
    UBRR0L = (uint8_t) UBRR_VALUE;
    
    //4. USART 설정
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01); //Charecter size : 8비트
    UCSR0C &= ~(1<<USBS0); //stop  bit : 1비트
    UCSR0C &= ~((1<<UPM01)|(1<<UPM00)); // no parity mode
    
    //5. 송수신을 가능하게 한다.
    UCSR0B=(1<<RXEN0)|(1<<TXEN0);
}
 
void transmitByte(uint8_t data) {
 
    //이전 전송이 끝나기를 기다림
    while(!(UCSR0A&(1<<UDRE0))){};
 
    UDR0 = data;                                            /* send data */
}
 
uint8_t receiveByte(void) {
    // 수신 되기를 기다림
    while(!(UCSR0A&(1<<RXC0))){};
    return UDR0;                                /* return register value */
}
 
 
void printString(const char str[]) {
    uint8_t i = 0;
    while (str[i]) {
        transmitByte(str[i]);
        i++;
    }
}
 
void readString(char str[], uint8_t maxLength) {
    char response;
    uint8_t i;
    i = 0;
    while (i < (maxLength - 1)) {                   /* prevent over-runs */
        response = receiveByte();
        transmitByte(response);                                    /* echo */
        if (response == '\r') {                     /* enter marks the end */
            break;
        }
        else {
            str[i] = response;                       /* add in a letter */
            i++;
        }
    }
    str[i] = 0;                          /* terminal NULL character */
}
 
int main(void)
{
    usartInit();
    
    char ch;
 
    while(1)
    {
        ch = receiveByte();
        
        if ( ch == '\r') {
            transmitByte('\r');
            transmitByte('\n');
        }
 
        transmitByte(ch);
    }
}