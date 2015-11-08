 /**
   * Author 		: Yudha Pane 
   * Created on		: Aug 13th
   * Last updated	: Nov 7th
   * Description 	: A node which reads the Heidenhain encoder measurement
   */


#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include "ros/node_handle.h"


#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <iostream>

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	// set-up the serial communication
	struct termios tio;
	struct termios stdio;
	struct termios config;
	int tty_fd;
	fd_set rdset;
	int iReadStatus = 0;
	int encoderData_old = 0;
	char data[4];
	unsigned char c = '1';
	int iHomePos    = 0;
	float fAngle = 0.0;
	
	//char encoderData[4];
	std_msgs::Int16 encoderData;
	std_msgs::Float32 fAngleData;
	
    int b0, b1, b2, b3;
        
/*    
    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=0;
    stdio.c_cc[VTIME]=0;
    //tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    //tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking


    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;
*/
    tty_fd=open("/dev/ttyACM1", O_RDWR | O_NONBLOCK);
  	if (tty_fd>0)
	{
		printf("USB Serial Port Opened! Status:%d \n", tty_fd);
	}
	else
	{	
		printf("USB Serial Port Open Failed! Status:%d \n", tty_fd);
		sleep(1);
		return 0;
	}    
	
	
	if(tcgetattr(tty_fd, &config) < 0) 
	{ 
		printf("serial config can't be obtained!");
		sleep(1);
		return 0;
	}
	
	 //
	 // Input flags - Turn off input processing
	 //
	 // convert break to null byte, no CR to NL translation,
	 // no NL to CR translation, don't mark parity errors or breaks
	 // no input parity check, don't strip high bit off,
	 // no XON/XOFF software flow control
	 //
	 config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
		                 INLCR | PARMRK | INPCK | ISTRIP | IXON);

	 //
	 // Output flags - Turn off output processing
	 //
	 // no CR to NL translation, no NL to CR-NL translation,
	 // no NL to CR translation, no column 0 CR suppression,
	 // no Ctrl-D suppression, no fill characters, no case mapping,
	 // no local output processing
	 //
	 // config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
	 //                     ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
	 config.c_oflag = 0;

	 //
	 // No line processing
	 //
	 // echo off, echo newline off, canonical mode off, 
	 // extended input processing off, signal chars off
	 //
	 config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

	 //
	 // Turn off character processing
	 //
	 // clear current char size mask, no parity checking,
	 // no output processing, force 8 bit input
	 //
	 config.c_cflag &= ~(CSIZE | PARENB);
	 config.c_cflag |= CS8;

	 //
	 // 4 input bytes is enough to return from read()
	 // Inter-character timer off
	 //
	 config.c_cc[VMIN]  = 4;
	 config.c_cc[VTIME] = 0;

	 //
	 // Communication speed (simple version, using the predefined
	 // constants)
	 //
	 if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0) 
	  {
	 	printf("serial speed can't be set \n");
		sleep(1);
	 	return 0;
	 }

	 //
	 // Finally, apply the configuration
	 //
	 if(tcsetattr(tty_fd, TCSANOW, &config) < 0) 
	 {
	 	printf("serial config can't be set \n");
		sleep(1);
	 	return 0;
	 }
 
 /*
    cfsetospeed(&config,B9600);            // 9600 baud
    cfsetispeed(&config,B9600);            // 9600 baud

    tcsetattr(tty_fd,TCSANOW,&config);
*/

	// create ros node
 	ros::init(argc, argv, "encoderPublisher");
  	ros::NodeHandle n;

  	ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("encoder_data", 1);

  	ros::Rate loop_rate(100);
  	int counter = 0;
  	int counter_out = 0;
  	while (ros::ok())
  	{
        memset(data, 0, sizeof(data));
        write(tty_fd,&c,1);
        iReadStatus = read(tty_fd,data,4);
		
		if (iReadStatus>0)
		{
		
		    if (strcmp(data,"none")==0)
            {
            	printf("none \n");
            }
            else
            {
                b0 = (int)data[0]-48;
                b1 = (int)data[1]-48;
                b2 = (int)data[2]-48;
                b3 = (int)data[3]-48;
                if((b0>=0)&&(b1>=0)&&(b2>=0)&&(b3>=0))
                {	
                	if (counter == 0)
                	{
                		iHomePos = atoi(data);
                	}
                	//encoderData[0] = b0;
                	//encoderData[1] = b1;
                	//encoderData[2] = b2;                	
                	//encoderData[3] = b3;
                	//strncpy(encoderData, data, 18);    
                	//encoderData.data = b0*1000+b1*100+b2*10+b3;
                	encoderData.data = atoi(data);  
                	encoderData_old  = encoderData.data;         	 
                	fAngleData.data  = ((float)encoderData.data - (float)iHomePos)/22.7556;               	                	
                    //printf("%d%d%d%d\n",b0,b1,b2,b3);
            		//write(STDOUT_FILENO,data,iReadStatus);              // if new data is available on the serial port, print it out
            		counter++; 	
            	}
            	else
            	{
            		encoderData.data = encoderData_old;
            		//counter++;
            	}            	            	            	    			
            }
            
		//	printf("here2 \n");
		//	data = atoi(buf);
		
		//	printf("encoder data: %d\n", data);
		
    	//	std_msgs::String msg;

    	//	std::stringstream ss;
    	//	ss << buf;
    	//	msg.data = ss.str();


    	}
    	else
    	{
    		printf("read is failed! \n");
    	}
 	   	counter_out++;
 	   	//ROS_INFO("%d", encoderData.data);
 	   	printf("%f\n", fAngleData.data);
		//fprintf(stderr,"%d ---- counter:%d \n", encoderData.data, counter);
		//printf("-------- counter:%d \n",counter);
		//printf("******** counter:%d \n",counter_out);
		fflush(stdout); 
   		encoder_pub.publish(fAngleData);
    	if(tcflush(tty_fd, TCIOFLUSH)<0)
    	{
    		printf("Failed to flush! \n");
    		sleep(1);
    		return 0;
    	}

    	ros::spinOnce();
    	loop_rate.sleep();
    	
  	}
    close(tty_fd);
  return 0;
}

