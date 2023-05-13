#ifndef _Encoder_
#define _Encoder_

#include <stdio.h>
#include "ap_int.h"
#include "HD_Object.h"

typedef ap_uint<QUANTIZE> IM_VAL;
typedef ap_uint<SUM_SIZE> sum_vec;

void Encoder(HDV pm[IM_TOTAL], HDV gm[Q_SIZE], IM_VAL im[IM_TOTAL], HDV *result);

HDV Normalize_HDV(sum_vec pre[HD], int loopNum);

#endif
