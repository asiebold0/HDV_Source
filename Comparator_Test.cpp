#include "Comparator.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{

	HDV am_in[NUM_CLASSES];
	HDV cv_in;

	RESULT_VECTOR result_out = 1;
	rLog log_out;

	int retval=0;
	ofstream FILE;

	// Create input data

//	am_in[0] = 0b00001111;
//	am_in[1] = 0b00000011;
//	am_in[2] = 0b00111111;
//	am_in[3] = 0b00001111;
//	am_in[4] = 0b01111111;

	for (int jj = 0; jj < NUM_CLASSES; jj++)
	{
//		am_in[jj] = 0b01010101;
		am_in[jj] = 0x5555;
		log_out[jj] = 1.0;
//		std::cout << jj << " " << am_in[jj] << " " << log_out[jj] << std::endl;
	}

	am_in[0] = 0x000F;
	am_in[1] = 0x0055;
	am_in[2] = 0x11AA;
	am_in[3] = 0xFF0F;
	am_in[4] = 0x2E8B;

//	cv_in 	 = 0b10101010;
	cv_in 	 = 0xAAAA;


	// Save the results to a file
	FILE.open ("Comparator_Result.dat");

	// Call the function

	Comparator(am_in, cv_in, &result_out, log_out);

	// Save output data
	for ( int ii=0; ii<NUM_CLASSES; ii++)
	{
		std::cout << "Log for prediction " << ii << " " << log_out[ii] << std::endl;
		FILE << log_out[ii] << std::endl;
	}
	std::cout << "Prediction: " << result_out << std::endl;
	FILE << result_out;
	FILE.close();

	// Compare the results file with the golden results
	retval = system("diff --brief -w Comparator_Result.dat Comparator_Test_Golden.dat");
	if (retval != 0)
	{
		printf("Test failed  !!!\n");
		retval=1;
	}
	else
	{
		printf("Test passed !\n");
	}

	// Return 0 if the test passes
	return retval;
}
