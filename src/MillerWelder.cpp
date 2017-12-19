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

void MillerWelder::setAttribute_01(EIP_UINT attr_val)
{
  setSingleAttribute(0x73, 1, 4, attr_val); // FIXME
  // mrc_.range_report_format = attr_val;

}

void MillerWelder::setAttribute_02(EIP_UINT attr_val)
{
  setSingleAttribute(0x73, 1, 5, attr_val); // FIXME
  // mrc_.range_report_format = attr_val;

}

void MillerWelder::setAttribute_03(EIP_UINT attr_val)
{
  setSingleAttribute(0x73, 1, 6, attr_val); // FIXME
  // mrc_.range_report_format = attr_val;

}

EIP_UINT MillerWelder::getAttribute_01()
{
  // mrc_.reflectivity_report_format = getSingleAttribute(0x73, 1, 5, (EIP_UINT)0); // FIXME
  // return mrc_.reflectivity_report_format;
}


} // namespace miller_welder_driver
