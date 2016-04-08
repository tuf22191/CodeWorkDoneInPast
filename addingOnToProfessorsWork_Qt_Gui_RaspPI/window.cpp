#include "window.h"
//#include <stdio.h>
//#include <bcm2835.h>
//#include <cstdio>
#include <cmath>  // for sine stuff
//taken from online  From Airspayce.com written by Mike McCauley
#define PIN RPI_GPIO_P1_11
#define PIN2 RPI_GPIO_P1_12
#define TARGET_VELOCITY 2
#define SHIFT_FOR_INT 26

Window::Window() : plot( QString("Velocity") ), gain(5), count(0) // <-- 'c++ initialisation list' - google it!
{
      //taken purely from online, not our code! 
      //http://qwt.sourceforge.net/class_qwt_analog_clock.html
	//
	QwtAnalogClock *clock = new QwtAnalogClock();
	clock->scaleDraw()->setPenWidth(3);
	clock->setLineWidth(6);
	clock->setFrameShadow(QwtDial::Sunken);
	clock->setTime(); 
      // update the clock every second
      QTimer *timer = new QTimer(clock);
            timer->connect(timer, SIGNAL(timeout()), clock, SLOT(setCurrentTime()));
            timer->start(1000);





	// set up the gain knob
	knob.setValue(gain);

	// use the Qt signals/slots framework to update the gain -
	// every time the knob is moved, the setGain function will be called
	connect( &knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

	// set up the thermometer
	thermo.setFillBrush( QBrush(Qt::red) );
	thermo.setRange(0, 20);
	//thermo.show();


	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] = gain * sin( M_PI * index/50 );
	}

	// make a plot curve from the data and attach it to the plot
	curve.setSamples(xData, yData, plotDataSize);
	curve.attach(&plot);

	plot.replot();
	plot.show();


	// set up the layout - knob above thermometer
	//vLayout.addWidget(&knob);
	  vLayout.addWidget(clock);
	//vLayout.addWidget(&thermo);


	// plot to the left of knob and thermometer
	hLayout.addLayout(&vLayout);
	hLayout.addWidget(&plot);

	setLayout(&hLayout);

        std::cout << "It is working\n";
        //Below is NOT THE RIGHT WAY TO DO IT, the preferred way is to use 
        // moveToThread() on QObject and then using the Signals and Slots sys-
        //tem. Essentially use the connect function on the QObject instantia-
        //tion to hook up the start() method of the QThread object and the 
        // desired method that does the processing 
        DaThread *ls =new DaThread();

         uint64_t  ls_time=1900;
          int ls_boolean = 1;
          uint64_t  rs_time=1100;
          int rs_boolean = 1;


        ls-> initiate(xData, yData,&ls_time, &ls_boolean, &rs_time,&rs_boolean);
        ls->start();
        std::cout << "It is working\n";

        //start the servos around the time the data starts to be read  

        // ServoThread *leftServo =new ServoThread();
        // leftServo-> initiate(PIN, &ls_time, &ls_boolean);
        // leftServo->start();
 std::cout << "It is working1\n";

         
        // ServoThread *rightServo =new ServoThread();
        // rightServo-> initiate(PIN2, &rs_time, &rs_boolean);
        // rightServo->start();
         
        // ls_boolean =0;
        // rs_boolean =0;
}


void Window::timerEvent( QTimerEvent * ) //should plot every x amount of times
{
	// generate an sine wave input for example purposes - you must get yours from the A/D!
	// only plotting
	curve.setSamples(xData, yData, plotDataSize);
	plot.replot();

	// set the thermometer value
	//thermo.setValue( inVal + 10 );
}




// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}

void ServoThread::initiate(uint8_t pinnumber,uint64_t * uptime, int *boolean){
  pin_num = pinnumber;
  hightime = uptime;
  keepgoing = boolean; 


}

void ServoThread::run(){

while(*keepgoing==1){

//bcm2835_gpio_write(pin_num,HIGH);

//bcm2835_delayMicroseconds(*hightime);
//bcm2835_gpio_write(pin_num,LOW);
//bcm2835_delayMicroseconds(20000);

//printf("In while loop");

}

}


void DaThread::initiate(double xArray[], double yArray[], uint64_t *ls_time, int *ls_boolean, uint64_t *rs_time,
int *rs_boolean)
{
	//for(int j=0;j<DATA;j++){
      //   xData[j]=amount;
      //   yData[j]=amount;
      //}
      ls_Time=ls_time;
      rs_Time=rs_time;
      rs_Boolean=rs_boolean;
      ls_Boolean=ls_boolean;
      xDataPointer=xArray;
      yDataPointer=yArray;
}

void DaThread::I2cSendData(byte addr,byte *data,int len)
{
           if(ioctl(deviceDescriptore,I2C_SLAVE, addr)){
                printf("I2cSendData_device : IOCTL Problem\n");}

        write(deviceDescriptore,data,len);
}

void DaThread::I2cReadData(byte addr,byte *data,int len)
{
 if(ioctl(deviceDescriptore,I2C_SLAVE, addr))
               { printf("I2cReadData_device : IOCTL Problem\n");}

        read(deviceDescriptore,data,len);

}

void DaThread::init_i2c(char *DeviceName)
{
        deviceDescriptore=open(DeviceName, O_RDWR);
        if (deviceDescriptore == -1)
        {
                printf("Error opening device '%s'\n",DeviceName);
                exit(-1);
        }
}

void DaThread::run()
{
///////////////////////////////////////////////
	//general variables
        int counter =0;
        unsigned int micro_seconds=22000;
        int gain=5; 
        int count=0;
        double inVal=0;

///////////////////////////////////////////////
	//this is for the accelerometer use
        int i, v;
        byte data[20];
        init_i2c("/dev/i2c-1");
        // set mode register to 1 to activate accelerometer
        data[0] = 7;
        data[1] = 1;
        I2cSendData(MMA7660_ADDR,data,2);

///////////////////////////////////////////////
	//this is for the servos
// I primarily got the structure of the code from TutorialsPoint website C++ Multithreading, Qthreads I 
// think I read somewhere are object oriented "helpers" of pthreads       
       uint64_t  rs_time=1900;
          int ls_boolean = 1;
          uint64_t  ls_time=1100;
          int rs_boolean = 1;



 bcm2835_init();
pthread_t servo_threads[2];
struct servo_thread_data threads_data[2];

//pin BCM18 should be the first thread delay of below
//delay should be less than 1500 mS
//pin 18 is the left side looking from the back of the vehicle

threads_data[0].pin_num=PIN2;
threads_data[0].hightime=&ls_time;//ls_time<1500
threads_data[0].keepgoing=&ls_boolean;
threads_data[0].id=0;

//pin BCM17
threads_data[1].pin_num=PIN;
threads_data[1].hightime=&rs_time;//ls_time<1500
threads_data[1].keepgoing=&rs_boolean;
threads_data[1].id=1;

//servo running with pin BCM18
pthread_create(&servo_threads[0],NULL,rotateServo, (void *)&threads_data[0]);
//servo running with pin BCM
pthread_create(&servo_threads[1],NULL,rotateServo, (void *)&threads_data[1]);


 //////////////////////////////////////////////////
//while loop reads, calculates on the reading, and should adjust PWM for servos
        double v_cm_per_sec=0;
        double intermediate_double=0;
        while(counter<100000){

        //read in data and then in for loop , FORMAT THE DATA!
        I2cReadData(MMA7660_ADDR,data,11);
        for (i=0; i<3; i++) {

             //v = (data[i]/2^6)*9.81;
              v=data[i];
              v=v&0x0000003F;//int datatype has 4 bytes , set the most significant 26 bits to 0.
                      
             if (v>=0x20)
                {
                  v = -(0x40 - v);
                }  //sign extend negatives <- this clever way was found online 
             else{
                  v=v&0x0000001F;
                 // v= (v<<3)/8;      //<- this other clever way was found in mbed's library
                }
               intermediate_double=v/21.33; //       range for signed 5 bits is -32 to 31. The accel. 
                                            // from +-1.5g. So,  +32/1.5=21.33 approx.  
                                            //I really looked at mbed's library for the MMA7660, but I think
                                            // the math works out
               //look at consel for all three values, X,Y,Z. 
   // we only focus on one access, the forward direction assuming, the accelerometer is parallel to ground
               if(i==0){intermediate_double-=.046882;} //subtracting "x bias" value to get artificial value
               if(i==1){intermediate_double-=.093675;} //subtracting "y bias" value to get artificial value
                                                       //held the accelerometer stationary to get these approx
                                                       //values
               printf("%c in g's:%f  ",i+'X',intermediate_double);
               if(i==0){inVal=intermediate_double;}
            }
               printf("\n");
//inVal is in g's right now
//Physics:vf= velocity_initial + deltaV;
// where deltaV= a*delta_time or
// deltaV= inVal*9.81*(micro_seconds/1000000.0)*100
// inVal*9.81 converst to m/s^2 then multiply by delta_time or (micro_seconds/1000000.0) to get m/s
// and then multiply this by 100 to get cm/s  
        v_cm_per_sec=v_cm_per_sec + inVal*9.81*(micro_seconds/1000000.0)*100;    
        inVal=v_cm_per_sec;
      
        //adjust speed of servo motors
         if (inVal<TARGET_VELOCITY){ //speed up
           ls_time-=100;
           rs_time+=100; 
         }
         else if(inVal>TARGET_VELOCITY){//slow down
           ls_time-=100;
           rs_time+=100; 
         }
         counter = counter+1;

       //SLEEP because we don't want a very large amount of points
       //taken from StackOverflow
       //http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
       //         std::this_thread::sleep_for(std::chrono::milliseconds(1000))
        usleep(micro_seconds);
         
        //inVal = gain * sin( M_PI * count/50.0 );
	++count;

	// add the new input to the plot-Taken from Professor
	memmove( yDataPointer, yDataPointer+1, (DATA-1) * sizeof(double) );
	yDataPointer[DATA-1] = inVal;
      
      } //end of while 
      //the while loops in the servo thread should exit shortly after setting the booleans below to 0
      rs_boolean=0;
      ls_boolean=0;
}//end of run function


void *rotateServo(void *servo_thread_stuff){
struct servo_thread_data *data;
data= (struct servo_thread_data *) servo_thread_stuff;
while(*(data->keepgoing)==1){
bcm2835_gpio_write(data->pin_num,HIGH);
bcm2835_delayMicroseconds(*(data->hightime));
bcm2835_gpio_write(data->pin_num,LOW);
bcm2835_delayMicroseconds(20000);
}
pthread_exit(NULL);
}

