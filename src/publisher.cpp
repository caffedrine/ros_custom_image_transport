#include <ros/ros.h>

//OpenCv and the company
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

//Mesajul nostru personalizat
#include "custom_img_transport/mesaj.h"

//C++ Libs
#include <iostream>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle n;

    ros::Publisher publisher = n.advertise<custom_img_transport::mesaj>("camera/image", 1);

    //Video editing and all the stuff
    // Convert the passed as command line parameter index for the video device to an integer
    std::istringstream video_sourceCmd("0");
    int video_source;

    if(!(video_sourceCmd >> video_source)) return 1;

    cv::VideoCapture cap(video_source);

    // Check if video device can be opened with the given index
    if(!cap.isOpened()) return 1;
    cv::Mat frame;

    //Message
    custom_img_transport::mesaj msg;
    unsigned int counter = 0;

    ros::Rate loop_rate(20);  //Vrei mai multe cadre pe secunda? Modifica asta :)
    while (n.ok())
    {
        ///////////////////////////////////////////////////////
        //Update IMU here :)
        msg.imu_x = 123;
        msg.imu_y = 456;
        msg.imu_z = 789;

        //Also is usefull to define the header
        std_msgs::Header header;
        header.seq = counter++;
        header.stamp = ros::Time::now();

        /// ///////////////////////////////////////////////////
        cap >> frame;
        // Check if grabbed frame is actually full with some content
        if(!frame.empty())
        {
            cv_bridge::CvImage img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, frame);
            img_bridge.toImageMsg(msg.image);

            //Send a message before
            std::cout <<"[" << msg.image.header.seq << "] " << "imu_X: " << msg.imu_x << " imu_Y: " << msg.imu_y
                     << " imu_Z: " << msg.imu_z << std::endl;

            publisher.publish(msg);
            cv::waitKey(1);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}
