//this is a servos file



#include <stdio.h>
#include <bcm2835.h>
//#include <wiringPi.h>
//#include <softPwm.h>
#include <cstdio>


//taken from online  From Airspayce.com written by Mike McCauley
#define PIN RPI_GPIO_P1_11
//#define PIN RPI_GPIO_P1_12

int main() {


if(!bcm2835_init()){return 1;}

bcm2835_gpio_write(PIN,HIGH);


int pin7 = 7;
int pinx= 18;
int result =-1;



result=0;
//result=softPwmCreate(pinx,0,215);
if(result ==0){

while(result<600){

bcm2835_gpio_write(PIN,HIGH);
//bcm2835_delay(3);
bcm2835_delayMicroseconds(1400);
bcm2835_gpio_write(PIN,LOW);
//bcm2835_delay(20);
bcm2835_delayMicroseconds(20000);
//printf("In while loop");
result++;
}
result=0;
while(result<600){

bcm2835_gpio_write(PIN,HIGH);
//bcm2835_delay(3);
bcm2835_delayMicroseconds(1350);
bcm2835_gpio_write(PIN,LOW);
//bcm2835_delay(20);
bcm2835_delayMicroseconds(20000);
//printf("In while loop");
result++;
}

result=0;
while(result<600){

bcm2835_gpio_write(PIN,HIGH);
//bcm2835_delay(3);
bcm2835_delayMicroseconds(1275);
bcm2835_gpio_write(PIN,LOW);
//bcm2835_delay(20);
bcm2835_delayMicroseconds(20000);
//printf("In while loop");
result++;
}



result=0;
while(result<600){

bcm2835_gpio_write(PIN,HIGH);
//bcm2835_delay(3);
bcm2835_delayMicroseconds(1100);
bcm2835_gpio_write(PIN,LOW);
//bcm2835_delay(20);
bcm2835_delayMicroseconds(20000);
//printf("In while loop");
result++;
}





}

bcm2835_close();


return 0; 
}




