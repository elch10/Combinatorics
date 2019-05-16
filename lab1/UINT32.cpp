#include "UINT32.h"
#include <stdexcept>
#include <iostream>
#include "ArihmeticError.h"

using std::cout;
using std::endl;

UINT32::UINT32():
  value_(0)
{}

// copy-constructor:
UINT32::UINT32(const UINT32 &A):
  value_(A.value_)
{} // UINT32::UINT32(UINT32 & A)

// immerse: 
UINT32::UINT32(uint aa):
  value_(aa)
{} // UINT32::UINT32(uint & aa)

// operators:
// assignment: 
UINT32 & UINT32::operator = (const UINT32 & B) {
  value_ = B.value_;
  return *this; 
} // UINT32 & UINT32::operator = (UINT32 & B) 

UINT32 UINT32::operator + (const UINT32 & B) const {
  if (MAX_UINT32.value_ - value_ < B.value_)
    throw ArihmeticError(ErrorType::ADD);
  return UINT32(value_ + B.value_); 
} // UINT32 UINT32::operator + (UINT32 & B)

UINT32 UINT32::operator - (const UINT32 & B) const {
  if (value_ < B.value_)
    throw ArihmeticError(ErrorType::SUBTRACT);
  return UINT32(value_ - B.value_);
} // UINT32 UINT32::operator - (UINT32 & B) 

UINT32 UINT32::operator * (const UINT32 & B) const {
  if ( double(MAX_UINT32.value_) / value_ < B.value_)
    throw ArihmeticError(ErrorType::MULTIPLY);
  return UINT32(value_ * B.value_);
} // UINT32 UINT32::operator * (UINT32 & B) 

UINT32 UINT32::operator / (const UINT32 & B) const {
  if (B.value_ == 0)
    throw ArihmeticError(ErrorType::ZERO_DIVISION);
  return UINT32(value_ / B.value_);
} // UINT32 UINT32::operator / (UINT32 & B)

UINT32 UINT32::operator * (byte b) const {
  return UINT32(value_) * UINT32(b);
} // UINT32 UINT32::operator * (byte b) 

UINT32 UINT32::operator / (byte b) const {
  return UINT32(value_) / UINT32(b);
} // UINT32 UINT32::operator / (byte b)

// accumulators:
UINT32 &UINT32::operator += (const UINT32 & B) {
  *this = UINT32(value_) + UINT32(B.value_);
  return *this;
} // void UINT32::operator += (UINT32 & B)

UINT32 &UINT32::operator -= (const UINT32 & B) {
  *this = UINT32(value_) - UINT32(B.value_);
  return *this;
} // void UINT32::operator -= (UINT32 & B) 

UINT32 &UINT32::operator *= (const UINT32 & B) {
  *this = UINT32(value_) * UINT32(B.value_);
  return *this;
} // void UINT32::operator *= (UINT32 & B) 

UINT32 &UINT32::operator /= (const UINT32 & B) {
  *this = UINT32(value_) / UINT32(B.value_);
  return *this;
} // void UINT32::operator /= (UINT32 & B)

UINT32 &UINT32::operator *= (byte b) {
  *this = UINT32(value_) * UINT32(b);
  return *this;
} // void UINT32::operator *= (byte b) 

UINT32 &UINT32::operator /= (byte b) {
  *this = UINT32(value_) / UINT32(b);
  return *this;
} // void UINT32::operator /= (byte b)

//friend
std::ostream &operator << (std::ostream &ostr, const UINT32 & A){
  ostr << A.value_;
  return ostr;  
} // ostream & operator << (UINT32 & A)

void CheckUINT32() {
  UINT32 hMAX_UINT32(0x7FFFFFFFU), TwoPow16(0x1UL << 16), TwoPow31(0x1UL << 31)
     , rMAX_UINT32(0xFFFFU), One(1), Twopow16(rMAX_UINT32 + One);
  cout << "Checking class UINT32 operators:" << endl;
  cout << "MAX_UINT32 = " << MAX_UINT32 << endl;
  cout << "TwoPow31 = " << TwoPow31 << endl;
  cout << "hMAX_UINT32 = " << hMAX_UINT32 << endl;
  cout << "rMAX_UINT32 = " << rMAX_UINT32 << endl;
  cout << "TwoPow16 = " << TwoPow16 << endl;
  cout << "Twopow16 = " << Twopow16 << endl;

  // check `+` overflow: 
  cout << "(hMAX_UINT32 + TwoPow31) = ";
  try {
    cout << (hMAX_UINT32 + TwoPow31) << endl;
  } catch (ArihmeticError &err) {
    cout << err.what() << endl;
    // cout << "(UINT32 + UINT32) overflow" << endl;
  }

  // check `+` overflow: 
  cout << "(MAX_UINT32 + One) = ";
  try {
    cout << (MAX_UINT32 + One) << endl;
  } catch (ArihmeticError &err) {
    cout << err.what() << endl;
    // cout << "(UINT32 + UINT32) overflow" << endl;
  }

    // check `-` overflow: 
  cout << "(hMAX_UINT32 - hMAX_UINT32) = ";
  try {
    cout << (hMAX_UINT32 - hMAX_UINT32) << endl;
  } catch (ArihmeticError &err) {
    cout << err.what() << endl;
    // cout << "(UINT32 - UINT32) overflow" << endl;
  }

  cout << "(rMAX_UINT32 - TwoPow16) = ";
  try {
    cout << (rMAX_UINT32 - TwoPow16) << endl;
  } catch (ArihmeticError &err) {
    cout << err.what() << endl;
    // cout << "(UINT32 - UINT32) overflow" << endl;
  }

  // check `*` overflow: 
  cout << "(rMAX_UINT32 * (TwoPow16 + One)) = ";
  try {
    cout << (rMAX_UINT32 * (TwoPow16 + One)) << endl;
  } catch (ArihmeticError &err) {
    cout << err.what() << endl;
    // cout << "(UINT32 * UINT32) overflow" << endl;
  }

  cout << "(TwoPow16 * Twopow16) = ";
  try {
    cout << (TwoPow16 * Twopow16) << endl;
  } catch (ArihmeticError &err) {
    cout << err.what() << endl;
    // cout << "(UINT32 * UINT32) overflow" << endl;
  }
} // CheckUINT32() 

