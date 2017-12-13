#ifndef MILLER_WELDER_DRIVER_H
#define MILLER_WELDER_DRIVER_H

#include <gtest/gtest_prod.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>

#include <ros/ros.h>

#include "odva_ethernetip/session.h"
#include "odva_ethernetip/socket/socket.h"
#include "odva_ethernetip/serialization/serializable_buffer.h"
#include "odva_ethernetip/cpf_packet.h"
#include "odva_ethernetip/cpf_item.h"
#include "odva_ethernetip/sequenced_address_item.h"
#include "odva_ethernetip/sequenced_data_item.h"

// #include Data structure

using std::vector;
using boost::shared_ptr;
using eip::Session;
using eip::socket::Socket;

namespace miller_welder_driver {

typedef enum
{
    ARC_DETECTION = 0,
    MOTOR_RETRACTING = 1,
    MOTOR_FEEDING = 2,
    GAS_ON = 3,
    TOUCHED = 4,
    ERROR_TYPE_PROCESS = 5,
    ERROR_ACTIVE = 6,
    WELD_OUTPUT_ON = 7,
    WELD_STATE_STATUS = 8,
    TOUCH_SEARCHING = 9,
    JOB_STARTED = 10,
    PART_STARTED = 11,
    SYNERGIC_PROCESS = 12,
} MILLER_INFLAG;

typedef enum
{
  MOTOR_RETRACT_COMMAND = 1,
  MOTOR_FORWARD_COMMAND = 2,
  GAS_ON_COMMAND = 3,
  TRIGGER_DISABLE = 4,
  IGNORE_WELD = 5,
  ADVANCE_CENTERPOINT_SLIDE = 6,
  RESST_PROCESS_ERRORS = 7,
  CONTACTOR_COMMAND = 8,
  TOUCH_SENSE_ON_COMMAND = 9,
  CELL_STATE_1 = 10,
  CELL_STATE_2 = 11,
  CELL_STATE_3 = 12,
  CELL_STATE_4 = 13,
} MILLER_OUTFLAG;



class MillerWelder : public Session
{
public:

  MillerWelder(shared_ptr<Socket> socket, shared_ptr<Socket> io_socket)
    : Session(socket, io_socket) {}

  void startUDPIO();
  void sendMeasurmentReportConfigUDP();
  MeasurementReport receiveMeasurementReportUDP();

  void setAttribute_01(EIP_UINT attr_val);
  void setAttribute_02(EIP_UINT attr_val);
  void setAttribute_03(EIP_UINT attr_val);

  EIP_UINT getAttribute_01();
  EIP_UINT getAttribute_02();
  EIP_UINT getAttribute_03();

private:


};






} // namespace miller_welder_driver


#endif // MILLER_WELDER_DRIVER_H
