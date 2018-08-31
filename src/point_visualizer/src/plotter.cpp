#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include <sstream>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "plotter");

  ros::NodeHandle n;


  ros::Publisher plotter_pub = n.advertise<geometry_msgs::PointStamped>("info", 1000);

  ros::Rate loop_rate(10);


  while (ros::ok())
  {
 
    geometry_msgs::PointStamped msg;

    msg.header.frame_id = "map";
    msg.header.stamp = ros::Time();
    msg.point.x = rand() % 10;
    msg.point.y = rand() % 10;
    msg.point.z = rand() % 10;

    plotter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}

