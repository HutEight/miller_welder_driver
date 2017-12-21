#ifndef ASSEMBLY_OUTPUT_INSTANCE_ATTRIBUTE_03_H
#define ASSEMBLY_OUTPUT_INSTANCE_ATTRIBUTE_03_H

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

class AssemblyOutputInstanceAttribute03 : public Serializable
{
public:
    EIP_UINT output_flags;

    // index 33, inches/minute, process dependent
    EIP_UINT wire_feed_speed_cmd;

    /**
     * For MIG processes, desired Voltage in tenths of a volt; 200 is 20.0 volts.
     * For Synergic processes, desired unit-less Arc Length; range is 1-99, 50 is
     * nominal. . A value of zero will be replaced with the nominal (50 Arc Length
     * or 25.0 volts).
     */
    EIP_UINT arc_length_or_voltage_cmd;

    /**
     * For MIG processes, the Inductance is in the lower byte, 0-99, nominally
     * 30, and the Slope is in the upper byte, 1-99, nominally 50. For Synergic
     * processes, Sharp Arc is in the lower byte, 1-50, nominally 25, and the
     * upper byte is ignored. A value of zero will be replaced with the nominal
     * for each.
     */
    EIP_UINT inductance_or_sharp_arc_cmd;

    /**
     * The number which shows in the Program window on the front of the welder.
     * Factory settings allow 1-8, though future enhancements allow 1-98 in
     * this window and may allow a much larger range. A zero in this field will
     * leave whatever Weld List Number was last used and allow front panel
     * control.
     */
    EIP_UINT weld_list_number;

    /**
     * The Part ID is used by Insight and communicated to CenterpointTM for
     * arc data monitoring. The value is 1-9999, and a value of 10,000 is
     * added to the Part ID to indicate the Start of a part. A value of zero
     * is ignored. Alternatively, the most-significant bit may be used as
     * the start flag.
     */
    EIP_UINT part_id_and_start_or_end;

    EIP_UINT weld_id;

    AssemblyOutputInstanceAttribute03() : output_flags(0),
      wire_feed_speed_cmd(0), arc_length_or_voltage_cmd(0),
      inductance_or_sharp_arc_cmd(0),weld_list_number(0)
    {
      std::cout << "RN_DEBUG: contructing a attribute format" << std::endl;
    }

    /**
     * From OM257-675C documentation, it is always 26 bytes
     */
    virtual size_t getLength() const
    {
      return 28;
    }

    virtual Writer& serialize(Writer& writer) const
    {
      EIP_UINT reserved = 0;
      writer.write(output_flags);
      writer.write(wire_feed_speed_cmd);
      writer.write(arc_length_or_voltage_cmd);
      writer.write(inductance_or_sharp_arc_cmd);
      writer.write(weld_list_number);
      writer.write(part_id_and_start_or_end);
      writer.write(weld_id);
      writer.write(reserved); // reserved
      writer.write(reserved);
      writer.write(reserved);
      writer.write(reserved);
      writer.write(reserved);
      writer.write(reserved);
      writer.write(reserved);
      return writer;
    }

    virtual Reader& deserialize(Reader& reader, size_t length)
    {
      return deserialize(reader);
    }

    virtual Reader& deserialize(Reader& reader)
    {
      reader.read(output_flags);
      reader.read(wire_feed_speed_cmd);
      reader.read(arc_length_or_voltage_cmd);
      reader.read(inductance_or_sharp_arc_cmd);
      reader.read(weld_list_number);
      reader.read(part_id_and_start_or_end);
      reader.read(weld_id);
      reader.skip(14);
      return reader;
    }

    virtual void resetAll()
    {
      std::cout << "Resetting the attribute to all 0s." << std::endl;
      output_flags = 0;
      wire_feed_speed_cmd = 0;
      arc_length_or_voltage_cmd = 0;
      inductance_or_sharp_arc_cmd = 0;
      weld_list_number = 0;
      part_id_and_start_or_end = 0;
      weld_id = 0;
    }

};

} // namespace omron_os32c_driver
#endif // ASSEMBLY_OUTPUT_INSTANCE_ATTRIBUTE_3_H
