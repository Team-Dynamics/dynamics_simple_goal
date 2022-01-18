#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "publish_goal");

    ros::NodeHandle nh("");
    ros::NodeHandle p_nh("~");
    ros::Publisher pub;

    double x, y, theta;
    std::string frame, topic;

    topic = p_nh.param<std::string>("topic", "/move_base_simple/goal");
    frame = p_nh.param<std::string>("frame", "map");
    x = p_nh.param("x", 0.0);
    y = p_nh.param("y", 0.0);
    theta = p_nh.param("theta", 0.0);
    
    pub = nh.advertise<geometry_msgs::PoseStamped>(topic, 1);

    geometry_msgs::PoseStamped msg;
    msg.header.frame_id = frame;
    msg.header.stamp = ros::Time::now();
    msg.pose.position.x = x;
    msg.pose.position.y = y;
    msg.pose.orientation = tf2::toMsg(tf2::Quaternion(0,0,theta));
    
    while (pub.getNumSubscribers() == 0)
    {
        ros::Duration(0.1).sleep();
    }
    
    pub.publish(msg);

    ros::spin();
    return 0;
}
