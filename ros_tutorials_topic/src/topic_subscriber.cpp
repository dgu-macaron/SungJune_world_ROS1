#include "ros/ros.h"
#include "math.h"
#include "ros_tutorials_topic/SungJuneKim.h"

void msgCallback(const ros_tutorials_topic::SungJuneKim::ConstPtr&msg)
{
ROS_INFO("recieve msg = %d", msg->stamp.sec);
ROS_INFO("recieve msg = %d", msg->stamp.nsec);
ROS_INFO("recieve msg = %d", int(pow(msg->data,2)));
}

int main(int argc, char **argv)
{
ros::init(argc, argv, "topic_subscriber");

ros::NodeHandle nh;


ros::Subscriber ros_tutorial_sub = nh.subscribe("ros_tutorial_msg", 100, msgCallback);

ros::spin();

return 0;
}
