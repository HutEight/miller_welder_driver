#ifndef ASSEMBLY_INPUT_INSTANCE_ATTRIBUTE_03_H
#define ASSEMBLY_INPUT_INSTANCE_ATTRIBUTE_03_H

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

class AssemblyInputInstanceAttribute03 : public Serializable
{
public:
    EIP_UINT input_flags;

    // index 33, inches/minute, process dependent
    EIP_UINT actual_wire_feed_speed;

    EIP_UINT actual_arc_current;

    EIP_UINT acutal_arc_voltage;

    EIP_UINT error_type;

    // EIP_UINT whatever;

    // EIP_UINT part_id_and_start_or_end;

    // EIP_UINT weld_id;

    AssemblyInputInstanceAttribute03() : input_flags(1),
      actual_wire_feed_speed(2), actual_arc_current(3),
      acutal_arc_voltage(4),error_type(5)
    {
      std::cout << "RN_DEBUG: contructing a attribute format" << std::endl;
    }

    /**
     * From OM257-675C documentation, it is always 26 bytes
     */
    virtual size_t getLength() const
    {
      return 28; // FIXME
    }

    virtual Writer& serialize(Writer& writer) const
    {
      EIP_UINT reserved = 0;
      writer.write(input_flags);
      writer.write(actual_wire_feed_speed);
      writer.write(actual_arc_current);
      writer.write(acutal_arc_voltage);
      writer.write(error_type);
      // writer.write(part_id_and_start_or_end);
      // writer.write(weld_id);
      // writer.write(reserved); // reserved
      // writer.write(reserved);
      // writer.write(reserved);
      // writer.write(reserved);
      // writer.write(reserved);
      // writer.write(reserved);
      // writer.write(reserved);
      return writer;
    }

    virtual Reader& deserialize(Reader& reader, size_t length)
    {
      return deserialize(reader);
    }

    virtual Reader& deserialize(Reader& reader)
    {
      reader.read(input_flags);
      reader.read(actual_wire_feed_speed);
      reader.read(actual_arc_current);
      reader.read(acutal_arc_voltage);
      reader.read(error_type);
      // reader.read(whatever);
      // reader.read(weld_id);
      // reader.skip(14);
      return reader;
    }


};

} // namespace miller_welder_driver 
#endif // ASSEMBLY_INPUT_INSTANCE_ATTRIBUTE_03_H
