#include <ros/ros.h>

#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include "custom_img_transport/mesaj.h"
#include <sensor_msgs/Image.h>

#include <iostream>

void image_callback(const custom_img_transport::mesaj &msg)
{
    try
    {
       //afisare frame_id
       std::cout<< "[" << msg.image.header.frame_id << "]";
       long t_now = ros::Time::now().toNSec();
       long t_recv = msg.image.header.stamp.toNSec();
       std::cout << "[" << (double)(t_now - t_recv)/1e6 << " ms] ";
       std::cout <<"[" << msg.image.header.seq << "] " << "imu_X: " << msg.imu_x << " imu_Y: " << msg.imu_y
             << " imu_Z: " << msg.imu_z << std::endl;

        cv_bridge::CvImagePtr cvImg = cv_bridge::toCvCopy(msg.image, "bgr8");

        cv::imshow("view", cvImg->image);
        cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
        std::cout <<"Error: [" << msg.image.header.seq << "]" << std::endl;
       //ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
		//Initializare ros
		ros::init(argc, argv, "subscriberToMessage");
		ros::NodeHandle n;

		//Starting the window to view the frames
		cv::namedWindow("view");
		cv::startWindowThread();

		//Abonare la topicul specificat
		ros::Subscriber subscriber = n.subscribe("camera/image", 1, image_callback);
		ros::spin();

		cv::destroyWindow("view");

		return 0;
}
