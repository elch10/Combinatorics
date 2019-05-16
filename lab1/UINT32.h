#ifndef UINT32_H
#define UINT32_H

#include <iosfwd>
#include <limits>

typedef unsigned int uint;
typedef unsigned char byte;

class UINT32
{
public:
  UINT32();
  UINT32(const UINT32&); // copy-constructor
  UINT32(uint); // immerse 
  ~UINT32() = default;
  // operators:
  UINT32 &operator =(const UINT32 &); // assignment 
  UINT32 operator + (const UINT32 &) const;
  UINT32 operator - (const UINT32 &) const;
  UINT32 operator * (const UINT32 &) const;
  UINT32 operator / (const UINT32 &) const;
  UINT32 operator * (byte) const;
  UINT32 operator / (byte) const;
  // accumulators:
  UINT32 &operator += (const UINT32 &);
  UINT32 &operator -= (const UINT32 &);
  UINT32 &operator *= (const UINT32 &);
  UINT32 &operator /= (const UINT32 &);
  UINT32 &operator *= (byte);
  UINT32 &operator /= (byte);

  // stream IO:
  friend std::ostream & operator << (std::ostream &, const UINT32 &); 
private:
  uint value_;
};

const UINT32 MAX_UINT32 = std::numeric_limits<uint>::max();
void CheckUINT32();


#endif //UINT32_H