#ifndef _COMPARATOR_
#define _COMPARATOR_

#include <stdio.h>
#include "ap_int.h"
#include "HD_Object.h"

//typedef ap_uint<(NUM_CLASSES/2) + 1> RESULT_VECTOR;
typedef ap_uint<4> RESULT_VECTOR;

typedef float rLog[NUM_CLASSES];

void Comparator(HDV am[NUM_CLASSES], HDV cv, RESULT_VECTOR *result, float result_log[NUM_CLASSES]);

float Hamming_Dist(HDV first, HDV second);

#endif
