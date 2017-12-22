#ifndef TCP_OBJECT_INSTANCE_01_ATTRIBUTE_05_H
#define TCP_OBJECT_INSTANCE_01_ATTRIBUTE_05_H

#include <string>

#include "odva_ethernetip/eip_types.h"
#include "odva_ethernetip/serialization/reader.h"
#include "odva_ethernetip/serialization/writer.h"
#include "odva_ethernetip/serialization/serializable.h"

using std::string;
using eip::serialization::Serializable;
using eip::serialization::Reader;
using eip::serialization::Writer;

namespace miller_welder_driver {

class TcpObjectInstance01Attribute05 : public Serializable
{
public:
  EIP_UDINT IP_address;
  EIP_UDINT Network_mask;
  EIP_UDINT Gateway_address;
  EIP_UDINT Name_server;
  EIP_UDINT Name_server_2;
  EIP_UDINT Domain_name_size;
  EIP_UDINT Domain_name;

  TcpObjectInstance01Attribute05() : IP_address(0), Network_mask(0), Gateway_address(0),
  	Name_server(0), Name_server_2(0), Domain_name_size(0), Domain_name(0)
  	{
      std::cout << "RN_DEBUG: contructing a attribute format" << std::endl;
  	}

  virtual size_t getLength() const
  {
    return 100;
  }

  virtual Writer& serialize(Writer& writer) const
  {
    EIP_UINT reserved = 0;
    writer.write(IP_address);
    writer.write(Network_mask);
    writer.write(Gateway_address);
    writer.write(Name_server);
    writer.write(Name_server_2);
    writer.write(Domain_name_size);
    writer.write(Domain_name);

    return writer;
    }

  virtual Reader& deserialize(Reader& reader, size_t length)
  {
    return deserialize(reader);
  }   


  virtual Reader& deserialize(Reader& reader)
  {
    reader.read(IP_address);
    reader.read(Network_mask);
    reader.read(Gateway_address);
    reader.read(Name_server);
    reader.read(Name_server_2);
    // reader.read(Domain_name_size);
    // reader.read(Domain_name);

    return reader;
  }


};




} // namespace miller_welder_driver 
#endif // TCP_OBJECT_INSTANCE_01_ATTRIBUTE_05_H