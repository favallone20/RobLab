#include <ros/ros.h>
#include<tf/tf.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>

void printTrasform(geometry_msgs::TransformStamped transformStamped)
{
    ROS_INFO_STREAM("Translation:" << transformStamped.transform.translation);
    tf::Quaternion q (transformStamped.transform.rotation.x, transformStamped.transform.rotation.y,
        transformStamped.transform.rotation.z, transformStamped.transform.rotation.w);
    
    tf::Matrix3x3 rotMat(q);

    ROS_INFO_STREAM("Quaternion:" << q<<"\n");

    double printMat [3][3];
    for (int i = 0; i < 3; i++)
    {
        printMat[0][i]=rotMat.getRow(0)[i];
        printMat[1][i]=rotMat.getRow(1)[i];
        printMat[2][i]=rotMat.getRow(2)[i];
    }
    
    ROS_INFO("\n\nRotation Matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        ROS_INFO_STREAM("\t["<<printMat[i][0]<<", "<<printMat[i][1]<<", "<<printMat[i][2]<<"]");
    }

     //Euler Angles
    double roll,pitch,yaw;
    rotMat.getRPY(roll,pitch,yaw);
    ROS_INFO_STREAM("\n\nEuler angles:\nroll:\t"<<roll<<"\npitch:\t"<<pitch<<"\nyaw:\t"<< yaw);

    //Axis angles
    tf::Vector3 axis = q.getAxis();
    double tetha = q.getAngle();

    ROS_INFO_STREAM("\n\nAxis-Angle:\nr:\t[" << axis[0] << " " << axis[1] << " " << axis[2] << "], tetha: " << tetha<<"\n");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf2_listener");
    const char* vet[8] = {"base_link", "link1", "link2", "link3", "link4", "link5", "link6","link7"};
    ros::NodeHandle nodeHandle;
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);
    ros::Rate rate(10.0);
    while (nodeHandle.ok())
    {
        geometry_msgs::TransformStamped transformStamped;
        try
        {
            for (int i = 0; i < 7; i++)
            {
                ROS_INFO_STREAM(" ----------------------------------- LINK"<<i+1<<"-----------------------------------");
                transformStamped = tfBuffer.lookupTransform(vet[i], "link7", ros::Time(0));
                printTrasform(transformStamped);
            }
        }
        catch (tf2::TransformException &exception)
        {
            ROS_WARN("%s", exception.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        rate.sleep();
    }
    return 0;
}