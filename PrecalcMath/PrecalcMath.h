#ifndef PrecalcMath_h
#define PrecalcMath_h

#include <stdint.h>

/*
  PrecalcMath.h - Library for sin cos and linearizing led light
  using integer math using precomputed tables.
  Created by Francesco Munafò, November 8, 2018.
  Released into the public domain.
*/



// Please #define SIN_TABLE_SIZE in including file
// Please #define LINERIZE_TABLE_SIZE in including file

// Size of precalculated table: 8 16 32 256, any other value reverts to 16
// Bigger table is smoother

// 256 is much faster (but takes more space), if you have space use 256




#ifndef SIN_TABLE_SIZE
#define SIN_TABLE_SIZE 32
#endif

#ifndef LINERIZE_TABLE_SIZE
#define LINERIZE_TABLE_SIZE 16
#endif







class PrecalcMath {
  
  public:
  static uint8_t linearizeLight(uint8_t l);
  static int8_t sin360(int32_t l);
  static int8_t cos360(int32_t l);
  static int8_t sin255(int32_t l);
  static int8_t cos255(int32_t l);
  inline static int8_t sin255small(uint8_t l);
  inline static int8_t cos255small(uint8_t l);
  static int8_t sin1024(int32_t l);
  static int8_t cos1024(int32_t l);
  
  
  private:
#if LINERIZE_TABLE_SIZE == 256
  static const uint8_t ledLights256[];
#elif LINERIZE_TABLE_SIZE == 32
  static const uint8_t ledLights32[];
#elif LINERIZE_TABLE_SIZE == 16
  static const uint8_t ledLights16[];
#elif LINERIZE_TABLE_SIZE == 8
  static const uint8_t ledLights8[];
#else
  static const uint8_t ledLights16[];
#endif
  
  
#if SIN_TABLE_SIZE == 256
  static const int8_t sinVals256[];
#elif SIN_TABLE_SIZE == 32
  static const int8_t sinVals32[];
#elif SIN_TABLE_SIZE == 16
  static const int8_t sinVals32[];
#elif SIN_TABLE_SIZE == 8
  static const int8_t sinVals8[];
#else
  static const int8_t sinVals16[];
#endif
  
  static int8_t _sin(uint8_t l);

  public:
  static uint8_t uInterpolateFromTable(uint16_t x,const uint8_t table[], uint8_t tableSize);
  static int8_t sInterpolateFromTable(uint16_t x,const int8_t table[], uint8_t tableSize);

};


#endif