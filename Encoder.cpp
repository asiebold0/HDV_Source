#include "Encoder.h"

void Encoder(HDV pm[IM_TOTAL], HDV gm[Q_SIZE], IM_VAL im[IM_TOTAL], HDV *result)
{
	#pragma HLS INTERFACE ap_fifo port=pm
	#pragma HLS INTERFACE ap_fifo port=gm
	#pragma HLS INTERFACE ap_fifo port=im

	int pos = 0;
	HDV temp = 0;
	sum_vec tempSum[HD];

//	#pragma HLS DATAFLOW
	INITIALIZE_LOOP:
	for (HDV ii = 0; ii < HD; ii++)
	{
//		#pragma HLS UNROLL
		tempSum[ii] = 0;
	}

	IM_ROW_LOOP:
	for (int ii = 0; ii < IM_SIZE; ii++)
	{
//		#pragma HLS UNROLL
		IM_COL_LOOP:
		for (int jj = 0; jj < IM_SIZE; jj++)
		{
//			#pragma HLS UNROLL
			temp = pm[pos] ^ gm[im[pos]];
			HDV_SUM_LOOP:
			for (int kk = 0; kk < HD; kk++)
			{
				#pragma HLS PIPELINE II=1 enable_flush
				tempSum[kk] = tempSum[kk] + ((temp >> (HD-kk-1)) & 0x01);
			}
			pos++;
		}
	}

//	(*result) = Normalize_HDV(tempSum, IM_TOTAL);

	HDV tempResult = 0;
	NORMALIZE_LOOP:
	for (int ii = 0; ii < HD; ii++)
	{
//		#pragma HLS PIPELINE
//		tempResult = tempResult + (( tempSum[ii] > (IM_TOTAL >> 1) ) << (HD-ii-1));
		if ( tempSum[ii] > (IM_TOTAL >> 1) )
		{
			tempResult = tempResult + (1 << (HD-ii-1));
		}
	}
	(*result) = tempResult;
}

HDV Normalize_HDV(sum_vec pre[HD], int loopNum)
{
//	#pragma HLS INLINE
	HDV result = 0;
	NORMALIZE_LOOP:
	for (int ii = 0; ii < HD; ii++)
	{
//		#pragma HLS PIPELINE
//		result = result + (( pre[ii] > (loopNum >> 1) ) << (HD-ii-1));
		if ( pre[ii] > (loopNum >> 1) )
		{
			result = result + (1 << (HD-ii-1));
		}
	}
	return result;
}
