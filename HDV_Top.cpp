#include "HDV_Top.h"

#define RESET 0
#define PROCESS 1
#define STORE_AM 2
#define STORE_PM 3
#define STORE_GM 4
#define LOAD_IM 5

//void HDV_Top(axi_stream *am_stream, axi_stream *pm_stream, axi_stream *gm_stream, axi_stream *im_stream, axi_stream *result, MODE mode)
//void HDV_Top(axi_stream m_stream, axi_stream im_stream, axi_stream result, MODE mode)
void HDV_Top(axi_stream &dstream, axi_stream &result, MODE mode)
{
//	#pragma HLS INTERFACE s_axilite register clock=control
	#pragma HLS CLOCK domain=default
//	#pragma HLS INTERFACE ap_ctrl_none port=return
//	#pragma HLS INTERFACE axis port=mode
//	#pragma HLS INTERFACE axis port=m_stream
//	#pragma HLS INTERFACE axis port=im_stream
//	#pragma HLS INTERFACE axis port=result
	#pragma HLS INTERFACE axis register_mode=both register port=dstream
	#pragma HLS INTERFACE axis register_mode=both register port=result
//	#pragma HLS PIPELINE II=1 enable_flush
	#pragma HLS PIPELINE II=1 style=flp

	static int am_pos = 0;
	static int pm_pos = 0;
	static int gm_pos = 0;
	static int im_pos = 0;

//	axi_stream *streamStore;
//	streamStore->data = m_stream->data;
//	streamStore->last = m_stream->last;
//
//	axi_stream *imStore;
//	imStore->data = im_stream->data;
//	imStore->last = im_stream->last;
//
//	axi_stream *outStore;
//	outStore->data = 0;
//	outStore->last = 1;

	pkt pkt_buf;
	axi_st data_buf;

	switch (mode)
	{
	case RESET:
	{
		am_pos = 0;
		pm_pos = 0;
		gm_pos = 0;
		im_pos = 0;
		break;
	}
	case PROCESS:
		{
//			HDV *im_HDV;
//			(*im_HDV) = 0;
			HDV im_HDV = 0;

//			std::cout << im_HDV << std::endl;
//			std::cout << &im_HDV << std::endl;

			Encoder(pm_store, gm_store, im_store, &im_HDV);

			RESULT_VECTOR prediction = 0;
			float log[NUM_CLASSES];

			Comparator(am_store, &im_HDV, &prediction, log);

//			data_buf = {(*prediction), 1};
			data_buf.data = prediction;
			pkt_buf.data = data_buf.data;
			pkt_buf.keep = -1;
			pkt_buf.last = 1;
			result.write(pkt_buf);
//			result->last = im_stream->last;
//			outStore->last = 1;
			break;
		}
	case STORE_AM:
		{
			do
			{
				#pragma HLS PIPELINE

				pkt_buf = dstream.read();
//				data_buf = {pkt.data, pkt.last};
				data_buf.data = pkt_buf.data;
				data_buf.last = pkt_buf.last;
				am_store[am_pos] = (HDV)data_buf.data;

				if(data_buf.last == 1)
					am_pos = 0;
				else
					am_pos++;
			} while (!data_buf.last);

			break;
		}
	case STORE_PM:
		{
			do
			{
				#pragma HLS PIPELINE

				pkt_buf = dstream.read();
				data_buf.data = pkt_buf.data;
				data_buf.last = pkt_buf.last;
				pm_store[pm_pos] = (HDV)data_buf.data;

				if(data_buf.last == 1)
					pm_pos = 0;
				else
					pm_pos++;
			} while (!data_buf.last);

			break;
		}
	case STORE_GM:
		{
			do
			{
				#pragma HLS PIPELINE

				pkt_buf = dstream.read();
				data_buf.data = pkt_buf.data;
				data_buf.last = pkt_buf.last;
				gm_store[gm_pos] = (HDV)data_buf.data;

				if(data_buf.last == 1)
					gm_pos = 0;
				else
					gm_pos++;
			} while (!data_buf.last);

			break;
		}
	case LOAD_IM:
		{
			do
			{
				#pragma HLS PIPELINE

				pkt_buf = dstream.read();
				data_buf.data = pkt_buf.data;
				data_buf.last = pkt_buf.last;
				im_store[im_pos] = (IM_VAL)data_buf.data;

				if(data_buf.last == 1)
					im_pos = 0;
				else
					im_pos++;
			} while (!data_buf.last);

			break;
		}
	default:
		{
//			outStore->data = 0;
//			outStore->last = 1;
			data_buf.data = 0;
			pkt_buf.data = data_buf.data;
			pkt_buf.keep = -1;
			pkt_buf.last = 1;
			result.write(pkt_buf);
		}

	}

//	result->data = outStore->data;
//	result->last = outStore->last;
}
