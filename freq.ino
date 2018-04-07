#include<avr/io.h>
#include<avr/interrupt.h>
long int t=0,t1=0,flag=0;
double timeperiod=0;
double freq=0;

void usart_int(void)
{
  UCSR0A=0x00;
  UCSR0B=(1<< RXEN0)|(1<< TXEN0);//TRANSMIT AND RECEIVE ENABLE
  UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//ASYNCHRONOUS, 8 BIT TRANSFER
  UBRR0L= 0x67 ; //BAUD RATE 9600
  
}


void usart_send(int ch )
{
  while(UCSR0A!=(UCSR0A|(1<<UDRE0)));//waiting for UDRE to become high
  UDR0= ch;
}


void dis(char a[100])
{int i=0;
  while(a[i])
  {usart_send(a[i]);
  i++;
}
}

void disp(long int a)
{
  int flag=0;
  long int t=a;
  char dis[10];
  while(t>0)
  {
    flag++;
    t/=10;
    }
    t=a;
    int g=1,l=0;
    while(t>0)
    {
      l=t%10;
      dis[flag-g]=l+48;
      t/=10;
      g++;
      
      }
    for(int i=0;i<flag-2;i++)
    usart_send(dis[i]);
    usart_send('.');
    for(int i=flag-2;i<flag;i++)
    usart_send(dis[i]);
 
     }



int main()
{
  DDRD=0xFF;
DDRB=0x00;
char ch;
usart_int();
dis("Press 's' to start sampling");
do
{
  //while(UCSR0A!= (UCSR0A|(1<<RXC0)));
   ch=UDR0;
  }while(ch!='s');

sei();


DDRB=0x00;
  DDRD=0xFF;
  TCCR0A=0b01000010;
  TCCR0B=0b00000101;
  
  OCR0A=100;
 TCCR1A=0; 
 TCCR1B|=0b01000011; 

TIMSK1=0b00100000;
while(1)
 { 
 }

}

  ISR(TIMER1_CAPT_vect)
  {PINB=0x00;
  
  flag++;
  if(flag==10)
  t=ICR1;
  if(flag==11)
    {t1=ICR1;
     timeperiod=(t1-t)*4;
     freq=1000000/timeperiod;
      dis("Frequency is ");
      freq*=100;
      disp(freq);
      if(freq>20&&freq<20000)
      OCR0A=16000000/(1024*freq);
 flag=0;
 TCNT1=0;
    }
    TIFR1|=(1<<ICF1);
    }
