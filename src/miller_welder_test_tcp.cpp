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
  host = "192.168.1.51";
  ROS_WARN("Using host name 192.168.1.51 \n Modify if you change the ip settings. \n ");
  boost::asio::io_service io_service;

  shared_ptr<TCPSocket> socket = shared_ptr<TCPSocket>(new TCPSocket(io_service));
  ROS_WARN("Expecting TCP port 44818.. \n ");
  shared_ptr<UDPSocket> io_socket = shared_ptr<UDPSocket>(new UDPSocket(io_service, 2222));
  ROS_WARN("Expecting UDP port 2222.. \n ");
  MillerWelder millerWelder(socket, io_socket);

  try
  {
    millerWelder.open(host);
  }
  catch (std::runtime_error ex)
  // catch (std::exception ex)
  {
    ROS_FATAL_STREAM("Exception caught opening session: " << ex.what());
    return -1;
  }
  ROS_INFO("TCP connection establshed through PORT 0xAF12.. \n ");


  millerWelder.resetAll();

  // FIXME may need to change error types for the sets
  try
  {
    // millerWelder.setAttribute03OutputFlag(0x0204);
  	millerWelder.setAttribute03OutputFlag(0xFFFF);
  }
  catch (std::invalid_argument ex)
  // catch (std::exception ex)
  {
    ROS_FATAL_STREAM("Exception caught setting output flags: " << ex.what());
    return -1;
  }
  // ROS_INFO("Output flags set 0x0002 -- 0000 0000 0000 0010 (0x0002) \n ");
  ROS_INFO("Output flags set 0x0002 -- 0000 0010 0000 0010 (0x0204) \n ");
  
  try
  {
    // millerWelder.setAttribute03WireFeedSpeedCmd(10);
    millerWelder.setAttribute03WireFeedSpeedCmd(0xFFFF);
  }
  catch (std::runtime_error ex)
  // catch (std::exception ex)
  {
    ROS_FATAL_STREAM("Exception caught setting wire feed speed cmd: " << ex.what());
    return -1;
  }
  ROS_INFO("Wire feed speed cmd set -- 10 (inches/minute) \n ");


  try
  {
    // millerWelder.setAttribute03PartIdAndStartOrEnd(10000);
    millerWelder.setAttribute03PartIdAndStartOrEnd(0xFFFF);
  }
  catch (std::runtime_error ex)
  // catch (std::exception ex)
  {
    ROS_FATAL_STREAM("Exception caught setting wire feed speed cmd: " << ex.what());
    return -1;
  }
  ROS_INFO("setAttribute03PartIdAndStartOrEnd cmd set -- 10000 \n ");

  // millerWelder.resetAll();

  cout << "Sending the settings--" << endl;
  millerWelder.printSetAttribute();

  try
  {
    millerWelder.sendAttribute03(0x4, 112, 3);
  }
  catch (std::invalid_argument ex)
  // catch (std::exception ex)
  {
    ROS_FATAL_STREAM("Exception caught sending the set cmds: " << ex.what());
    return -1;
  }
  ROS_INFO("Set cmds sent!");

  EIP_UINT outputflag_get = millerWelder.getAttribute03OutputFlag();

  // cout << "Checking the settings by pringing the words--" << endl;
  // millerWelder.printSetAttribute();

  cout << endl << "outputflag_get: " << outputflag_get << endl;

  EIP_UINT object_revision = millerWelder.getTcpObjectRevision();

  millerWelder.getTcpOjbectInstance01Attribute05();

  millerWelder.getIdentityObjectInstance01();

  millerWelder.getAssemblyInputInstanceAttribute03();

  // millerWelder.setgetIdentityObjectInstance01();

  // millerWelder.getAssemblyOutputInstanceAttribute02();

  while (ros::ok())
  {
	   // ROS_INFO("hello2");
  }

  return 0;
}
