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
  ros::init(argc, argv, "miller_welder_node");
  ros::NodeHandle nh;

  string host;
  string frame_id;
  ros::param::param<std::string>("~host", host, "192.168.1.1"); // TODO
  ros::param::param<std::string>("~frame_id", frame_id, "laser");

  boost::asio::io_service io_service;

  shared_ptr<TCPSocket> socket = shared_ptr<TCPSocket>(new TCPSocket(io_service));
  shared_ptr<UDPSocket> io_socket = shared_ptr<UDPSocket>(new UDPSocket(io_service, 2222));
  MillerWelder millerWelder(socket, io_socket);

  try
  {
    millerWelder.open(host);
  }
  catch (std::runtime_error ex)
  {
    ROS_FATAL_STREAM("Exception caught opening session: " << ex.what());
    return -1;
  }

  try
  {
    millerWelder.startUDPIO();
    // millerWelder.sendMeasurmentReportConfigUDP();
  }
  catch (std::logic_error ex)
  {
    ROS_FATAL_STREAM("Could not start UDP IO: " << ex.what());
    return -1;
  }

  return 0;
}
