// #include <ros/ros.h>

#include "miller_welder_driver/MillerWelder.h"

using std::cout;
using std::endl;
using boost::shared_ptr;
using boost::make_shared;
using boost::asio::buffer;
using eip::Session;
using eip::serialization::SerializableBuffer;
using eip::RRDataResponse;
using eip::CPFItem;
using eip::CPFPacket;
using eip::SequencedAddressItem;
using eip::SequencedDataItem;

namespace miller_welder_driver {

// FIXME
void MillerWelder::startUDPIO()
{
  EIP_CONNECTION_INFO_T o_to_t, t_to_o;
  o_to_t.assembly_id = 0x71;
  o_to_t.buffer_size = 0x006E;
  o_to_t.rpi = 0x00177FA0;
  t_to_o.assembly_id = 0x66;
  t_to_o.buffer_size = 0x0584;
  t_to_o.rpi = 0x00013070;

  connection_num_ = createConnection(o_to_t, t_to_o);
}

void MillerWelder::setAttribute03OutputFlag(EIP_UINT new_output_flags)
{
  attribute_03_.output_flags = new_output_flags;
}

void MillerWelder::setAttribute03WireFeedSpeedCmd(EIP_UINT new_wire_feed_speed_cmd)
{
  attribute_03_.wire_feed_speed_cmd = new_wire_feed_speed_cmd;
}

void MillerWelder::setAttribute03ArcLengthOrVoltageCmd(EIP_UINT new_arc_length_or_voltage_cmd)
{
  attribute_03_.arc_length_or_voltage_cmd = new_arc_length_or_voltage_cmd;
}

void MillerWelder::setAttribute03WeldListNumber(EIP_UINT new_weld_list_number)
{
  attribute_03_.weld_list_number = new_weld_list_number;
}

void MillerWelder::setAttribute03PartIdAndStartOrEnd(EIP_UINT new_part_id_and_start_or_end)
{
  attribute_03_.part_id_and_start_or_end = new_part_id_and_start_or_end;
}

void MillerWelder::setAttribute03WeldId(EIP_UINT new_weld_id)
{
  attribute_03_.weld_id = new_weld_id;
}

void MillerWelder::resetAll()
{
  attribute_03_.resetAll();
}

void MillerWelder::sendAttribute03(EIP_USINT class_id, EIP_USINT instance_id, EIP_USINT attribute_id)
// 0x4, 112, 3
{
  shared_ptr<AssemblyOutputInstanceAttribute03> data =
    make_shared<AssemblyOutputInstanceAttribute03>();
  *data = attribute_03_;
  // RRDataResponse resp_data = sendRRDataCommand(0x10,
  //   eip::Path(class_id, instance_id, attribute_id), data);
  setSingleAttributeSerializable(class_id, instance_id, attribute_id, data);
}

EIP_UINT MillerWelder::getAttribute03OutputFlag()
{
  AssemblyOutputInstanceAttribute03 attribute_03;

  // attribute_03.resetAll();
  getSingleAttributeSerializable(0x4, 112, 3, attribute_03);

  cout << endl << "\e[34m attribute_03.output_flags: \033[0m" << attribute_03.output_flags << endl
    << "\e[34m attribute_03.wire_feed_speed_cmd: \033[0m" << attribute_03.wire_feed_speed_cmd << endl
    << "\e[34m attribute_03.arc_length_or_voltage_cmd: \033[0m" << attribute_03.arc_length_or_voltage_cmd << endl
    << "\e[34m attribute_03.inductance_or_sharp_arc_cmd: \033[0m" << attribute_03.inductance_or_sharp_arc_cmd << endl
    << "\e[34m attribute_03.weld_list_number: \033[0m" << attribute_03.weld_list_number << endl
    << "\e[34m attribute_03.part_id_and_start_or_end: \033[0m" << attribute_03.part_id_and_start_or_end << endl
    << "\e[34m attribute_03.weld_id: \033[0m" << attribute_03.weld_id << endl;

  return attribute_03.output_flags;
}

EIP_UINT MillerWelder::getTcpObjectRevision()
{

  EIP_UINT TCP_object_revision = getSingleAttribute(0xF5, 0, 1, (EIP_UINT)0);
  cout << "TCP_object_revision: " << TCP_object_revision << endl;
}

void MillerWelder::getTcpOjbectInstance01Attribute05()
{
  TcpObjectInstance01Attribute05 get_result;
  getSingleAttributeSerializable(0xF5, 1, 5, get_result);
  cout << endl << "TcpOjbectInstance01Attribute05.IP_address: " << get_result.IP_address << endl
    << "TcpOjbectInstance01Attribute05.Network_mask: " << get_result.Network_mask << endl;

}

void MillerWelder::getIdentityObjectInstance01()
{
  EIP_UINT result;
  result = getSingleAttribute(0x01, 1, 1, (EIP_UINT)0);
  cout << endl << "\e[32mIdentityObjectInstance01-VenderNumber:\033[0m " << result << endl;
  result = getSingleAttribute(0x01, 1, 2, (EIP_UINT)0);
  cout << endl << "\e[32mIdentityObjectInstance01-DeviceType:\033[0m " << result << endl;  
}

void MillerWelder::getAssemblyInputInstanceAttribute03()
{ 
  cout << "RN_DEBUG" << endl;
  AssemblyInputInstanceAttribute03 get_result;
  getSingleAttributeSerializable(0x04, 100, 3, get_result);
  cout << endl << "AssemblyInputInstanceAttribute03.input_flags: " << get_result.input_flags << endl
    << "AssemblyInputInstanceAttribute03.actual_wire_feed_speed: " << get_result.actual_wire_feed_speed << endl
    << "AssemblyInputInstanceAttribute03.actual_arc_current: " << get_result.actual_arc_current << endl
    << "AssemblyInputInstanceAttribute03.acutal_arc_voltage: " << get_result.acutal_arc_voltage << endl
    << "AssemblyInputInstanceAttribute03.error_type: " << get_result.error_type << endl;

}

void MillerWelder::printSetAttribute()
{
    // cout << endl << "\e[34m attribute_03_.output_flags: \033[0m" << attribute_03_.output_flags << endl
    // << "\e[34m attribute_03_.wire_feed_speed_cmd: \033[0m" << attribute_03_.wire_feed_speed_cmd << endl
    // << "\e[34m attribute_03_.arc_length_or_voltage_cmd: \033[0m" << attribute_03_.arc_length_or_voltage_cmd << endl
    // << "\e[34m attribute_03_.inductance_or_sharp_arc_cmd: \033[0m" << attribute_03_.inductance_or_sharp_arc_cmd << endl
    // << "\e[34m attribute_03_.weld_list_number: \033[0m" << attribute_03_.weld_list_number << endl
    // << "\e[34m attribute_03_.part_id_and_start_or_end: \033[0m" << attribute_03_.part_id_and_start_or_end << endl
    // << "\e[34m attribute_03_.weld_id: \033[0m" << attribute_03_.weld_id << endl;

}




// EIP_UINT MillerWelder::getAttribute_01()
// {
//   // mrc_.reflectivity_report_format = getSingleAttribute(0x73, 1, 5, (EIP_UINT)0); // FIXME
//   // return mrc_.reflectivity_report_format;
// }


} // namespace miller_welder_driver
