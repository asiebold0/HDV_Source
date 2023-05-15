#ifndef _HDV_TOP_
#define _HDV_TOP_

#include <stdio.h>
#include "ap_int.h"
#include "HD_Object.h"
#include "Comparator.h"
#include "Encoder.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define AXI_LEN 32

typedef ap_axiu<32, 0, 0, 0> pkt;

struct axi_st
{
	ap_uint<32>		data;
	ap_uint<1>		last;
};

//typedef hls_stream<axi_st> axi_stream;
typedef hls::stream<pkt> axi_stream;
typedef ap_uint<3> MODE;

static HDV am_store[NUM_CLASSES];
static HDV pm_store[IM_TOTAL];
static HDV gm_store[Q_SIZE];
static IM_VAL im_store[IM_TOTAL];

//void HDV_Top(HDV am[NUM_CLASSES], HDV pm[IM_TOTAL], HDV gm[Q_SIZE], IM_VAL im[IM_TOTAL], RESULT_VECTOR *result);
//void HDV_Top(axi_stream *am_stream, axi_stream *pm_stream, axi_stream *gm_stream, axi_stream *im_stream, axi_stream *result, MODE mode);
//void HDV_Top(axi_stream m_stream, axi_stream im_stream, axi_stream result, MODE mode);
void HDV_Top(axi_stream &dstream, axi_stream &result, MODE mode);

#endif
