#include "window.h"

#include <cmath>  // for sine stuff


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
        ls->start();
}


void Window::timerEvent( QTimerEvent * )
{
	// generate an sine wave input for example purposes - you must get yours from the A/D!
	double inVal = gain * sin( M_PI * count/50.0 );
	++count;

	// add the new input to the plot
	memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = inVal;
	curve.setSamples(xData, yData, plotDataSize);
	plot.replot();

	// set the thermometer value
	thermo.setValue( inVal + 10 );
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}
 

void DaThread::run()
{
	//getDataStructure() function for getting the array that has the data
        int counter =0;
        unsigned int millionMicroseconds=1000000;
        while(counter<7){
        counter = counter+1;

        std::cout << "this is in the thread\n";
        //taken from StackOverflow
        //http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
       //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       usleep(millionMicroseconds);
        }
}

