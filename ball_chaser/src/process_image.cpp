#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Moving the robot");
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the drive_bot service and pass the requested velocities
    if (!client.call(srv))
        ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    int points_white_pixel_found=0;
    bool found_ball = false;
    int column_index = 0;
    int left_white=0;
    int mid_white=0;
    int right_white=0;
   // TODO: Loop through each pixel in the image and check if there's a bright white one
    for (int i=0; i < img.height * img.step; i++)
    {    int red =img.data[i];
         int green=img.data[i+1];
         int blue =img.data[i+2];
         
         /*divde Image into 3 section left , center ,right
         data[height*step]
          step------------------------------------------> 
         ------------------------------------------------ 
 height  | left section |center section | right section |
         |--------------|---------------|---------------|*/

         int section= img.step/3;
        if ((red == 255) && (green == 255) && (blue == 255))
        {

            column_index = i % img.step;
            //points_white_pixel_found+=1;
           //go_left 
            if (column_index < section && section<section*2)
                 {//left_white+=3;
                  drive_robot(0.1, 0.5);
                            }
           // to move to second section in the image
            else if (column_index < (section * 2) && (section*2) < (section*3))
                //go_forward
                {// mid_white+=3 ;
                  drive_robot(0.5, 0.0); 
                 }
           //go_right
            else if ((section * 3)>section && (section * 3)> (section *2) )
                { //right_white+=3;
                 drive_robot(0.1, -0.5);
                     }
              // if the white pixel full all the image robot have to stop
           // else if (left_white + mid_white + right_white== img.data[i+2])
             // drive_robot(0.0, 0.0);
            found_ball = true; 
            break;
        }
      //else if ((left_white + mid_white + right_white)== img.data[i])// can't move < ,or slow walk with >= ,:move to half of distance==
          //drive_robot(0.0, 0.0); 
     }
      
    // printf ("white_pixels= %d",points_white_pixel_found);
     if (found_ball == false)
         drive_robot(0.0, 0.0);             
    }

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/dirve/ball_chaser");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
