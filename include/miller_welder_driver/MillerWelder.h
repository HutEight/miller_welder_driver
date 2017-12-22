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

#include "miller_welder_driver/assembly_output_instance_attribute_03.h"
#include "miller_welder_driver/assembly_input_instance_attribute_03.h"
#include "miller_welder_driver/tcp_object_instance_01_attribute_05.h"

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

// TEMO
typedef enum
{
  NO_TOF_MEASUREMENTS       = 0,
  RANGE_MEASURE_50M         = 1,
  RANGE_MEASURE_32M_PZ      = 2,
  RANGE_MEASURE_16M_WZ1PZ   = 3,
  RANGE_MEASURE_8M_WZ2WZ1PZ = 4,
  RANGE_MEASURE_TOF_4PS     = 5,
} OS32C_RANGE_FORMAT;

typedef enum
{
  NO_TOT_MEASUREMENTS               = 0,
  REFLECTIVITY_MEASURE_TOT_ENCODED  = 1,
  REFLECTIVITY_MEASURE_TOT_4PS      = 2,
} OS32C_REFLECTIVITY_FORMAT;



class MillerWelder : public Session
{
public:

  MillerWelder(shared_ptr<Socket> socket, shared_ptr<Socket> io_socket)
    : Session(socket, io_socket) {}

  void startUDPIO();
  void sendMeasurmentReportConfigUDP();
  // MeasurementReport receiveMeasurementReportUDP();

  // void setAttribute_01(EIP_UINT attr_val);
  // void setAttribute_02(EIP_UINT attr_val);
  // void setAttribute_03(EIP_UINT attr_val);

  // EIP_UINT getAttribute_01();
  // EIP_UINT getAttribute_02();
  // EIP_UINT getAttribute_03();

  void setAttribute03OutputFlag(EIP_UINT new_output_flags);
  void setAttribute03WireFeedSpeedCmd(EIP_UINT new_wire_feed_speed_cmd);
  void setAttribute03ArcLengthOrVoltageCmd(EIP_UINT new_arc_length_or_voltage_cmd);
  void setAttribute03WeldListNumber(EIP_UINT new_weld_list_number);
  void setAttribute03PartIdAndStartOrEnd(EIP_UINT new_part_id_and_start_or_end);
  void setAttribute03WeldId(EIP_UINT new_weld_id);

  void resetAll();

  void sendAttribute03(EIP_USINT class_id, EIP_USINT instance_id, EIP_USINT attribute_id);

  EIP_UINT getAttribute03OutputFlag();

  EIP_UINT getTcpObjectRevision();

  void getTcpOjbectInstance01Attribute05();

  void getAssemblyInputInstanceAttribute03();

  void getIdentityObjectInstance01();

  void printSetAttribute();

private:

  // data for sending to lidar to keep UDP session alive
  int connection_num_;

  AssemblyOutputInstanceAttribute03 attribute_03_;

};






} // namespace miller_welder_driver


#endif // MILLER_WELDER_DRIVER_H
