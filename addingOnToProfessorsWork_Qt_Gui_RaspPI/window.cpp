#include "window.h"
//#include <stdio.h>
//#include <bcm2835.h>
//#include <cstdio>
#include <cmath>  // for sine stuff
//taken from online  From Airspayce.com written by Mike McCauley
#define PIN RPI_GPIO_P1_11
#define PIN2 RPI_GPIO_P1_12


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
        ls-> initiate(xData, yData);
        ls->start();
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

bcm2835_gpio_write(pin_num,HIGH);
//bcm2835_delay(3);
bcm2835_delayMicroseconds(*hightime);
bcm2835_gpio_write(pin_num,LOW);
//bcm2835_delay(20);
bcm2835_delayMicroseconds(20000);
//printf("In while loop");

}

}


void DaThread::initiate(double xArray[], double yArray[])
{
	//for(int j=0;j<DATA;j++){
      //   xData[j]=amount;
      //   yData[j]=amount;
      //}
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
	//getDataStructure() function for getting the array that has the data
        int counter =0;
        unsigned int micro_seconds=40000;
        int gain=5; 
        int count=0;
        double inVal=0;

                int i, v;
        byte data[20];

        init_i2c("/dev/i2c-1");

        // set mode register to 1 to activate accelerometer
        data[0] = 7;
        data[1] = 1;
        I2cSendData(MMA7660_ADDR,data,2);


        //start the servos around the time the data starts to be read
         uint64_t  ls_time=1900;
         int ls_boolean = 1;

         ServoThread *leftServo =new ServoThread();
         leftServo-> initiate(PIN, &ls_time, &ls_boolean);
         leftServo->start();

         uint64_t  rs_time=1100;
         int rs_boolean = 1;

         ServoThread *rightServo =new ServoThread();
         rightServo-> initiate(PIN2, &rs_time, &rs_boolean);
         rightServo->start();

        
        double v_cm_per_sec=0;
 
        while(counter<100000){

            I2cReadData(MMA7660_ADDR,data,11);
        for (i=0; i<3; i++) {
              v = (data[i]/2^6)*9.81;
              if (v>=0x20) v = -(0x40 - v);  //sign extend negatives
              printf("%c:%3d  ",i+'X',v);
              if(i==0){inVal=v;}
            }

        //remember inVal is the acceleration
        //so we just add on to it
          
        v_cm_per_sec=v_cm_per_sec + inVal*(micro_seconds/1000000.0)*100;    
        inVal=v_cm_per_sec;
      

         counter = counter+1;

        std::cout << "this is in the thread\n";
        //taken from StackOverflow
        //http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
       //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       usleep(micro_seconds);
        
         
        //inVal = gain * sin( M_PI * count/50.0 );
	++count;

	// add the new input to the plot
	memmove( yDataPointer, yDataPointer+1, (DATA-1) * sizeof(double) );
	yDataPointer[DATA-1] = inVal;
      
      } //end of while 
        ls_boolean =0;
        rs_boolean =0; 
}

