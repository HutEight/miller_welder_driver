//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    const std::string HMS_QE_IP = "192.168.0.17";
    // if (argc != 2)
    // {
    //   std::cerr << "Usage: client <host>" << std::endl;
    //   return 1;
    // }

    // try
    // {
    //   os32c.open(host);
    //   // RN_note void open(string hostname, string port = "44818", string io_port = "2222");
    //   // 44818 & 2222 are standard dafaults
    // }
    // catch (std::runtime_error ex)
    // {
    //   ROS_FATAL_STREAM("Exception caught opening session: " << ex.what());
    //   return -1;
    // }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
        // std::cout << "RN_DEBUG 01." << std::endl << "tcp::resolver resolver(io_service);" << std::endl;

    tcp::resolver::query query(HMS_QE_IP, "daytime");
        // std::cout << "RN_DEBUG 02." << std::endl << "tcp::resolver::query query(HMS_QE_IP, );" << std::endl;

    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        // std::cout << "RN_DEBUG 03." << std::endl << "tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);" << std::endl;

    tcp::socket socket(io_service);
        // std::cout << "RN_DEBUG 04." << std::endl << "tcp::socket socket(io_service);" << std::endl;

    boost::asio::connect(socket, endpoint_iterator);
        std::cout << "RN_DEBUG 05." << std::endl << "boost::asio::connect(socket, endpoint_iterator);" << std::endl;

    for (;;)
    {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout.write(buf.data(), len);
    }
  }
  // catch (std::exception& e)
  // {
  //   std::cout << "Printing Error:" << std::endl;
  //   std::cerr << e.what() << std::endl;
  // }

  catch (std::runtime_error ex)
  {
    std::cout << "RN: " << ex.what() << std::endl;
    std::cerr << "RN2: " << ex.what() << std::endl;
    return -1;
  }

  return 0;
}
