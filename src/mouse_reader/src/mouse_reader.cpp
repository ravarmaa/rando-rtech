#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "mouse_reader");

    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle nh;

    ros::Publisher pub_mouse = nh.advertise<geometry_msgs::PointStamped>("mouse", 100);

    while(ros::ok())
    {   
        geometry_msgs::PointStamped msg;

        int descriptor_ = open("dev/input/mice", O_RDONLY,S_IRWXU);

        int const BUFFER_SIZE = 64;
        struct input_event ibuffer[BUFFER_SIZE];
        int r, events, i;

        // read events to input_event buffer
        r = read(descriptor_, ibuffer, sizeof(struct input_event) * BUFFER_SIZE);
        msg.header.frame_id = "map";
        msg.header.stamp = ros::Time();
        if( r > 0 )
        {
            events = r / sizeof(struct input_event);				// getting the number of events

            // going through all the read events
            for(i=0; i<events; ++i)
            {
                
                struct input_event ev = ibuffer[i];

                switch(ev.type)				// switch to a case based on the event type
                {
                    case EV_SYN:				// this event is always present but no need to do anything
                    //printf("EV_SYN: code=0x%04x, value=0x%08x\n", ev->code, ev->value);
                        break; 
                    case EV_MSC:				// this event is always present but no need to do anything
                    //printf("EV_MSC: code=0x%04x, value=0x%08x\n", ev->code, ev->value);
                        break;
                    case EV_LED:                              // LED event occured (associated with capslock and numlock)
                        break;
                    case EV_ABS:

                        

                        if(ev.code == 0)
                            msg.point.x = ev.value;
                        if(ev.code == 1)
                            msg.point.y = ev.value;

                        msg.point.z = 0;
                        break;
                
                    
                }
            //end for
            }
        }
        pub_mouse.publish(msg);
        ros::Duration(0.01).sleep();
    }   
}