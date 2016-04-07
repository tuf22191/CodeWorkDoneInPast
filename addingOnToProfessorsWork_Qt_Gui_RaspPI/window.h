#ifndef WINDOW_H
#define WINDOW_H
//help taken from TutorialsPoint

//Below taken from : http://stackoverflow.com/questions/5961072/problems-with-using-qtimer
//
#include <QThread>
#include <QTimer>
#include <qwt/qwt_analog_clock.h>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <iostream>
#include <QBoxLayout>

//taken from Stack Overflow
//#include <chrono>
//#include <thread>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
//#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <math.h>
#include <fcntl.h>
//#include <linux/i2c-dev.h>
#include <time.h>
#include <sys/time.h>
#include <cstdio>

#include <sys/ioctl.h>

//for using the bcm library
//#include <cstdint>
#include <bcm2835.h>
#include <stdint.h>


#define MMA7660_ADDR  0x4c


// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(); // default constructor - called when a Window is declared without arguments

	void timerEvent( QTimerEvent * );
    



public slots:
	void setGain(double gain);

// internal variables for the window class
private:
  // graphical elements from the Qwt library - http://qwt.sourceforge.net/annotated.html
	QwtKnob      knob;
	QwtThermo    thermo;
	QwtPlot      plot;
	QwtPlotCurve curve;

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  vLayout;  // vertical layout
	QHBoxLayout  hLayout;  // horizontal layout

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData[plotDataSize];

	double gain;
	int count;
};

//Below is really not my work:
//below was taken from website:
//http://cep.xray.aps.anl.gov/software/qt4-x11-4.2.2/threads.html
 class DaThread : public QThread
 {
     Q_OBJECT



public:
     void run();
     void initiate(double xArray[],double yArray[]);
	//AGAIN, BELOW is just taken from what Professor Had
      static const int DATA = 100;

	// data arrays for the plot
	double *xDataPointer;
	double *yDataPointer;

      typedef unsigned char byte;

      int deviceDescriptore;

      void I2cSendData(byte addr,byte *data,int len);

      void I2cReadData(byte addr,byte *data,int len);
      
	void init_i2c(char *DeviceName);

 };

//this is basically threading for the Servos
//I built from the DaThread example, on which I got a lot of help online
//to do it. I got a lot help from websites like StackOverflow and CplusPlus.com
//and learncpp.com
class ServoThread : public QThread
 {
     Q_OBJECT



public:
     void run();
     void initiate(uint8_t pinnumber,uint64_t * uptime, int *boolean);
	      
       uint8_t pin_num;
       uint64_t *hightime;
       int *keepgoing;

 };

            


#endif // WINDOW_H
