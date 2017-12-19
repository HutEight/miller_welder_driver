#include <ros/ros.h>
#include <boost/shared_ptr.hpp>
#include "odva_ethernetip/socket/tcp_socket.h"
#include "odva_ethernetip/socket/udp_socket.h"

#include "miller_welder_driver/MillerWelder.h"

using std::cout;
using std::endl;
using boost::shared_ptr;
using eip::socket::TCPSocket;
using eip::socket::UDPSocket;
using namespace miller_welder_driver;

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "miller_welder_test_tcp");
  ros::NodeHandle nh;

  cout << "\n\e[41m LONSBERRY ENGINEERING \e[0m" << endl << endl
  	<< "    \e[4mTCP Connection test node\e[24m" << endl << endl;


  string host;
  string frame_id;
  // ros::param::param<std::string>("~host", host, "192.168.1.1"); // TODO
  // ros::param::param<std::string>("~frame_id", frame_id, "laser");
  host = "192.168.1.55";
  ROS_WARN("Using host name 192.168.1.55 \n Modify if you change the ip settings.");
  boost::asio::io_service io_service;

  shared_ptr<TCPSocket> socket = shared_ptr<TCPSocket>(new TCPSocket(io_service));
  ROS_WARN("Expecting TCP port 44818..");
  shared_ptr<UDPSocket> io_socket = shared_ptr<UDPSocket>(new UDPSocket(io_service, 2222));
  ROS_WARN("Expecting UDP port 2222..");
  MillerWelder millerWelder(socket, io_socket);

  try
  {

    millerWelder.open(host);

  }
  // catch (std::runtime_error ex)
  catch (std::exception ex)
  {
    ROS_FATAL_STREAM("Exception caught opening session: " << ex.what());
    return -1;
  }

  ROS_INFO("TCP connection establshed through PORT 0xAF12..");
  
  // FIXME
  try
  {
    millerWelder.setAttribute_01(RANGE_MEASURE_50M);
    millerWelder.setAttribute_02(REFLECTIVITY_MEASURE_TOT_4PS);
    // millerWelder.setAttribute_03(start_angle, end_angle);
  }
  catch (std::invalid_argument ex)
  {
    ROS_FATAL_STREAM("Invalid arguments in sensor configuration: " << ex.what());
    return -1;
  }


  // try
  // {
  //   millerWelder.startUDPIO();
  //   millerWelder.sendMeasurmentReportConfigUDP();
  // }
  // catch (std::logic_error ex)
  // {
  //   ROS_FATAL_STREAM("Could not start UDP IO: " << ex.what());
  //   return -1;
  // }

  // int ctr = 10;


  while (ros::ok())
  {

	ROS_INFO("hello2");


  }
  return 0;
}
