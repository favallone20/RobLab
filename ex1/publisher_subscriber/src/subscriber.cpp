#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>

void chatterCallback(trajectory_msgs::JointTrajectory jt){
    ROS_INFO_STREAM("I heard:"<<jt);
}

int main(int argc, char** argv){
    ros::init(argc, argv,"subscriber");
    ros:: NodeHandle nodeHandle;
    ros::Subscriber sub = nodeHandle.subscribe("chatter",1000, chatterCallback);
    ros::spin();
    ros::shutdown();
}