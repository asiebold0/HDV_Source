#ifndef _HD_OBJECT_
#define _HD_OBJECT_

#include "hls_math.h"

#define NUM_CLASSES 10	// Number of potential classes in the test set
#define HD 16			// Size of the Hyper-Dimensional Vector (HDV)
#define QUANTIZE 4		// Number of bits to hold the magnitude of value of each pixel in the image
#define IM_SIZE 4		// Length of a side of the **Square** image
#define IM_TOTAL 16		// Should be the following function: IM_SIZE*IM_SIZE
#define HD_PIECE_MAX 1024	// Maximum number of bits for a single piece of the HD Vector
#define HD_PIECE (HD/HD_PIECE_MAX + 1) // Number of HDV needed to realize the HD Vector
#define SUM_SIZE 10	// Should be the following function: (int(log(IM_SIZE*IM_SIZE)/log(2)) + 1); 10 is when IM_SIZE = 28
#define Q_SIZE 16 // Should be the following function: int(pow(2,QUANTIZE))

typedef ap_uint<HD> HDV;

#endif
