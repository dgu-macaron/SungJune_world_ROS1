#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

void laser_scan_Callback(const sensor_msgs::LaserScan::ConstPtr&msg)
{
    float angle_full = msg->angle_max - msg->angle_min;
    float angle_increment = msg->angle_increment;
    float ranges_count = angle_full/angle_increment;
    float max_range = msg->ranges[0];
    float max_point = 0.0;
    
    for(int i = 0; i < (ranges_count); i++)
    {   
        if((abs(msg->ranges[i+1] - msg->ranges[i]) < 1) or (abs(msg->ranges[i+2] - msg->ranges[i+1]) < 1))
        {
            if( (isinf(msg->ranges[i+1]) == 0) & (msg->ranges[i+1] > max_range) )
            {
                max_range = msg->ranges[i+1];
                max_point = i+1;
                // printf("msg->ranges[i+1] %f - msg->ranges[%d]  %f \n", msg->ranges[i+1],i, msg->ranges[i]);
                // cout << "msg->ranges[i+1] : " << msg->ranges[i+1] <<"   msg->ranges[" << i << "] : "<<  msg->ranges[i] << endl;
            }
            else if(isinf(msg->ranges[i+1]))
            {
                cout << "inf is happen at deg = " << ((i+1) * angle_increment + msg->angle_min)/3.148592*180  << endl;
            }
        }
        else
        {
                        cout << "pop scan val  at deg = " << ((i+1) * angle_increment + msg->angle_min)/3.148592*180 << endl;
        }
    }

    float far_angle = (max_point * angle_increment + msg->angle_min)/3.148592*180;
    ROS_INFO("max_range = %.3f ,  far_Angle(Deg) = %.3f",max_range, far_angle);
}



int main(int argc, char**argv)
{
ros::init(argc, argv, "laser_scan_data_received");
ros::NodeHandle nh;
ros::Subscriber ros_tutorial_sub = nh.subscribe("/scan", 1000, laser_scan_Callback);
ros::spin();
return 0;
}
