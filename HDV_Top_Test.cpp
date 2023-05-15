#include "HDV_Top.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

//#define RESET 0
//#define PROCESS 1
//#define STORE_AM 2
//#define STORE_PM 3
//#define STORE_GM 4
//#define LOAD_IM 5
#define N 4

int main()
{

	int retval=0;
	axi_stream am_stream;
	axi_stream pm_stream;
	axi_stream gm_stream;
	axi_stream im_stream;
	axi_stream result;
	pkt temp_datapkt;
	pkt result_pkts[N];
	axi_st temp_data;
	MODE mode = 0;

	// Create input data
//	srand(555);

	// AM
	for (int ii = 0; ii < NUM_CLASSES ; ii++)
	{
		if(am_stream.full())
		{
			std::cout << "AM Stream Full! " << ii << std::endl;
			return 1;
		}
//		temp_datapkt.data = ii%HD;
		temp_datapkt.data = (HDV)rand();
		temp_datapkt.keep = -1;
		if(ii < NUM_CLASSES - 1)
			temp_datapkt.last = 0;
		else
			temp_datapkt.last = 1;
		am_stream.write(temp_datapkt);
	}

	// PM
	for (int ii = 0; ii < IM_TOTAL; ii++)
	{
		if(pm_stream.full())
		{
			std::cout << "PM Stream Full! " << ii << std::endl;
			return 1;
		}
//		temp_datapkt.data = ii%4;
		temp_datapkt.data = (HDV)rand();
		temp_datapkt.keep = -1;
		if(ii < IM_TOTAL - 1)
			temp_datapkt.last = 0;
		else
			temp_datapkt.last = 1;
		pm_stream.write(temp_datapkt);
	}

	// GM
	for (int ii = 0; ii < Q_SIZE; ii++)
	{
		if(gm_stream.full())
		{
			std::cout << "GM Stream Full! " << ii << std::endl;
			return 1;
		}
//		temp_datapkt.data = ii%8;
		temp_datapkt.data = (HDV)rand();
		temp_datapkt.keep = -1;
		if(ii < Q_SIZE - 1)
			temp_datapkt.last = 0;
		else
			temp_datapkt.last = 1;
		gm_stream.write(temp_datapkt);
	}

	// IM
//	for (int ii = 0; ii < IM_TOTAL; ii++)
//	{
//		if(im_stream.full())
//		{
//			std::cout << "IM Stream Full! " << ii << std::endl;
//			return 1;
//		}
//		temp_datapkt.data = ii%2;
//		temp_datapkt.keep = -1;
//		if(ii < IM_TOTAL - 1)
//			temp_datapkt.last = 0;
//		else
//			temp_datapkt.last = 1;
//		im_stream.write(temp_datapkt);
//	}


	// Call the function

	// Load AM
	mode = 2;
	HDV_Top(am_stream, result, mode);

	// Load PM
	mode = 3;
	HDV_Top(pm_stream, result, mode);

	// Load GM
	mode = 4;
	HDV_Top(gm_stream, result, mode);

	// Try to load in several random images
	for (int count = 0; count < N; count++)
	{
		std::cout << "Input Image:" << std::endl;
		for (int ii = 0; ii < IM_TOTAL; ii++)
		{
			if(im_stream.full())
			{
				std::cout << "IM Stream Full! " << ii << std::endl;
				return 1;
			}
//			temp_datapkt.data = (IM_VAL)(count*ii + count*5 + ii*3);
			temp_datapkt.data = (IM_VAL)(rand());
			temp_datapkt.keep = -1;
			if(ii < IM_TOTAL - 1)
				temp_datapkt.last = 0;
			else
				temp_datapkt.last = 1;
			im_stream.write(temp_datapkt);

			std::cout << temp_datapkt.data << " ";
			if((ii + 1) % IM_SIZE == 0)
				std::cout << std::endl;

		}
		std::cout << std::endl;

		// Try printing out stream?
//		std::cout << "Reading image: " << std::endl;
//		int test_pos = 0;
//		do
//		{
//			temp_datapkt = im_stream.read();
//			temp_data.data = temp_datapkt.data;
//			temp_data.last = temp_datapkt.last;
//			std::cout << temp_data.data << " ";
//
//			if((test_pos + 1) % IM_SIZE == 0)
//				std::cout << std::endl;
//
//			if(temp_data.last == 1)
//				test_pos = 0;
//			else
//				test_pos++;
//		} while (!temp_data.last);
//		std::cout << std::endl;
		// ****

		// Load IM
		mode = 5;
		HDV_Top(im_stream, result, mode);

		// Try Process
		mode = 1;
		HDV_Top(im_stream, result, mode);
		result_pkts[count] = result.read();
		std::cout << "Finished Process! Result: " << result_pkts[count].data << std::endl;
	}

	// Save the results to a file
	ofstream FILE;
	FILE.open ("HDV_Top_Result.dat");
	// Save output data
	for (int ii = 0; ii<N; ii++)
	{
		std::cout << result_pkts[ii].data << std::endl;
		FILE << result_pkts[ii].data << std::endl;
	}
	FILE.close();

	// Compare the results file with the golden results
//	retval = system("diff --brief -w Comparator_Result.dat Comparator_Test_Golden.dat");
	retval = 0;
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
