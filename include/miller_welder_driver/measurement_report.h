
#ifndef OMRON_OS32C_DRIVER_MEASUREMENT_REPORT_H
#define OMRON_OS32C_DRIVER_MEASUREMENT_REPORT_H

#include <string>
#include <vector>

#include "odva_ethernetip/eip_types.h"
#include "odva_ethernetip/serialization/reader.h"
#include "odva_ethernetip/serialization/writer.h"
#include "odva_ethernetip/serialization/serializable.h"
#include "miller_welder_driver/measurement_report_header.h"

using std::vector;
using eip::serialization::Serializable;
using eip::serialization::Reader;
using eip::serialization::Writer;

namespace miller_welder_driver {

/**
 * Data structure and operators for OS32C specific Measurement Report data
 * as defined in the OS32C-DM Ethernet/IP Addendum. Used for both range and
 * reflectance data.
 */
class MeasurementReport : public Serializable
{
public:
  MeasurementReportHeader header;
  vector<EIP_UINT> measurement_data;

  /**
   * Size of this message including all measurement data
   */
  virtual size_t getLength() const
  {
    return header.getLength() + measurement_data.size() * sizeof(EIP_UINT);
  }

  /**
   * Serialize data into the given buffer
   * @param writer Writer to use for serialization
   * @return the writer again
   * @throw std::length_error if the buffer is too small for the header data
   */
  virtual Writer& serialize(Writer& writer) const
  {
    header.serialize(writer);
    writer.writeBytes(&measurement_data[0], measurement_data.size() * sizeof(EIP_UINT));
    return writer;
  }

  /**
   * Extra length information is not relevant in this context. Same as deserialize(reader)
   */
  virtual Reader& deserialize(Reader& reader, size_t length)
  {
    deserialize(reader);
    return reader;
  }

  /**
   * Deserialize data from the given reader without length information
   * @param reader Reader to use for deserialization
   * @return the reader again
   * @throw std::length_error if the buffer is overrun while deserializing
   */
  virtual Reader& deserialize(Reader& reader)
  {
    header.deserialize(reader);
    measurement_data.resize(header.num_beams);
    reader.readBytes(&measurement_data[0], measurement_data.size() * sizeof(EIP_UINT));
    return reader;
  }
};

} // namespace omron_os32c_driver

#endif  // OMRON_OS32C_DRIVER_MEASUREMENT_REPORT_H
