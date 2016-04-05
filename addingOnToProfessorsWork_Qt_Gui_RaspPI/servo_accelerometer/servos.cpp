//this is a servos file

#include <wiringPi.h>
#include <softPwm.h>
#include <cstdio>


int main() {

int pin7 = 7;
int pinx= 2;
int result =-1;

result=softPwmCreate(7,15,215);
if(result ==0){

while(1){

printf("In while loop");

}

}




return 0; 
}




