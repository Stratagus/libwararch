#ifndef main_H
#define main_H

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
#else
#include <inttypes.h>
#endif
#endif