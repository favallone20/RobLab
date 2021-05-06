#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nodeHandle;
    trajectory_msgs::JointTrajectory jt;
    ros::Publisher pub = nodeHandle.advertise<trajectory_msgs::JointTrajectory>("chatter", 1000);
    ros::Rate loopRate(1);

    while (ros::ok())
    {
        jt.joint_names.resize(6);   
        for (int i = 0; i < 6; i++)
        {
             jt.joint_names[i]="joint_"+to_string(i);
        }

        vector<trajectory_msgs::JointTrajectoryPoint> jtp; 
        jtp.resize(6);
        jt.points.resize(6);

        for (int i = 0; i < 6; i++)
        { 
            jtp[i].positions.resize(5);
            for (int j = 0; j < 5; j++)
            {
                jtp[i].positions[j] = rand();
            }

            jt.points[i] = jtp[i];
        }

        pub.publish(jt);
        ros::spinOnce();
        loopRate.sleep();
    }
    ros::shutdown();
    return 0;
}