/*
 * rosserial Service Server
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <duckpot_door/Door_controller.h>

ros::NodeHandle  nh;
using duckpot_door::Door_controller;

int i;
bool status_flag;

bool duckpot_door_open_cb(const Door_controller::Request & req, Door_controller::Response & res){
res.result = true;
status_flag = res.result;
return true;
}

bool duckpot_door_close_cb(const Door_controller::Request & req, Door_controller::Response & res){
res.result = false;
status_flag = res.result;
return true;
}

ros::ServiceServer<Door_controller::Request, Door_controller::Response> server("duckpot_door_open",&duckpot_door_open_cb);
ros::ServiceServer<Door_controller::Request, Door_controller::Response> server2("duckpot_door_close",&duckpot_door_close_cb);

std_msgs::Bool str_msg;
ros::Publisher duckpot_door_status("duckpot_door_status", &str_msg);

void setup()
{  
  nh.initNode();
  nh.advertiseService(server);
  nh.advertiseService(server2);
  nh.advertise(duckpot_door_status);
}

void loop()
{
  str_msg.data = status_flag;
  duckpot_door_status.publish( &str_msg );
  nh.spinOnce();
  delay(10);
}
