#ifndef ODVA_ETHERNETIP_SERIALIZATION_SERIALIZABLE_PRIMITIVE_ARRAY_H
#define ODVA_ETHERNETIP_SERIALIZATION_SERIALIZABLE_PRIMITIVE_ARRAY_H

#include "odva_ethernetip/serialization/serializable.h"
#include "odva_ethernetip/serialization/writer.h"
#include "odva_ethernetip/serialization/reader.h"

namespace eip {
namespace serialization {

template <typename T>
class SerializablePrimitiveArray : public Serializable
{
public:
  
  T data[];
  int data_size;

  SerializablePrimitiveArray() { }

  SerializablePrimitiveArray(const T& array_addr, int& array_size) : data_size(array_size) { }

  virtual size_t getLength()
  {
  	return sizeof(T);
  }

  virtual Writer& serializable(Writer& writer)
  {
  	for(int i = 0; i < data_size; i++)
  	{
  	  writer.write(data_size)

  	}
  }




} // namespace serialization
} // namespace eip
#endif  // ODVA_ETHERNETIP_SERIALIZATION_SERIALIZABLE_PRIMITIVE_ARRAY_H