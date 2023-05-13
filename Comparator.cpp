#include "Comparator.h"

using namespace std;

void Comparator(HDV am[NUM_CLASSES], HDV cv, RESULT_VECTOR *result, float result_log[NUM_CLASSES])
{
	#pragma HLS DATAFLOW
	#pragma HLS INTERFACE ap_fifo port=am
	#pragma HLS INTERFACE ap_fifo port=result_log

//	static RESULT_VECTOR tempResult = 0;
	RESULT_VECTOR tempResult = 0;
	float tempLog[NUM_CLASSES];
//	static float curAcc = 0;
	float curAcc = 0;

	INITIAL_LOOP:
	for (int ii = 0; ii<NUM_CLASSES; ii++)
	#pragma HLS UNROLL
		tempLog[ii] = 0.0;

	CALC_LOOP:
	for (int ii = 0; ii<NUM_CLASSES; ii++)
	{
//		#pragma HLS UNROLL
		tempLog[ii] = Hamming_Dist(am[ii], cv);
	}

	COMPARISON_LOOP:
	for (int ii = 0; ii<NUM_CLASSES; ii++)
	{
		#pragma HLS PIPELINE off
		if(tempLog[ii] > curAcc)
		{
			tempResult = ii;
			curAcc = tempLog[ii];
		}
		result_log[ii] = tempLog[ii];
	}

	(*result) = tempResult;
}

float Hamming_Dist(HDV first, HDV second)
{
	#pragma HLS INLINE
//	static float result = 0;
	float result = 0;

//	std::cout << "first " << first << std::endl;
//	std::cout << "second " << second << std::endl;

	HDV count = 0;

	HAMMING_LOOP:
	for (int ii = 0; ii<HD; ii++)
	{
//		#pragma HLS UNROLL
//		count += ((first >> ii) & HDV(0x01)) == ((second >> ii) & HDV(0x01));
		if ( ((first >> ii) & HDV(0x01)) == ((second >> ii) & HDV(0x01)) )
				count += 1;
	}

	result = float(count)/float(HD);

//	std::cout << "result " << result << std::endl;

	return result;
}
