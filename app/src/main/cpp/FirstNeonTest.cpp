//
// Created by finalreality on 2019/8/29.
//
#include <string>
#include <sstream>

#if(HAVE_NEON)
#include <arm_neon.h>
#endif

#include "FirstNeonTest.h"
#include "log.h"

#define TEST_WIDTH 320
#define TEST_HEIGHT 240
unsigned char testData[TEST_WIDTH * TEST_HEIGHT];

unsigned char addData[8] = {1, 1, 1, 1, 1, 1, 1, 1};

void dumpData(int dataWidth, int dataHeight, int showWidth, int showHeight, int bytesPerData = 1)
{
	std::stringstream ss;
	LOGI("DATA:");


	for (int h = 0; h < showHeight; h++) {
		for (int w = 0; w < showWidth; w++) {
			ss << (int) testData[h * dataWidth * bytesPerData + w];
			ss << ' ';
		}

		LOGI("\n[LINE %3d] %s", h, ss.str().c_str());
		ss.str("");
	}
}

void prepareData(int customValue = 0)
{
	if(customValue == 0) {
		for (int h = 0; h < TEST_HEIGHT; h++) {
			for (int w = 0; w < TEST_WIDTH; w++) {
				testData[h * TEST_WIDTH + w] = (unsigned char) w;
			}
		}
	} else {
		for (int h = 0; h < TEST_HEIGHT; h++) {
			for (int w = 0; w < TEST_WIDTH; w++) {
				testData[h * TEST_WIDTH + w] = customValue;
			}
		}
	}

	//dumpData(TEST_WIDTH, 240, 200, 100);
}

void addTest1()
{
	prepareData();

	for (int h = 0; h < TEST_HEIGHT; h++) {
		for (int w = 0; w < TEST_WIDTH; w += 8) {
			uint8x8_t v = vld1_u8(&testData[h*TEST_WIDTH+w]);
#if 0
			uint8x8_t add = vld1_u8(addData);
			v = vadd_u8(v, add);
#else
			v = vadd_u8(v, v);
#endif
			vst1_u8(&testData[h*TEST_WIDTH+w], v);
		}
	}

	dumpData(TEST_WIDTH, TEST_HEIGHT, 100, 50);
}


void addTest()
{
	prepareData(255);

	for (int h = 0; h < TEST_HEIGHT; h++) {
		for (int w = 0; w < TEST_WIDTH; w += 8) {
			uint8x8_t v = vld1_u8(&testData[h*TEST_WIDTH+w]);
#if 1
			uint16x8_t mul;
			uint8x8_t factor = vdup_n_u8(3);
			mul = vmull_u8(v, factor);
			uint8x8_t result = vshrn_n_u16(mul, 8);
#else
			uint8x8_t result = vmovn_u16(mul);
#endif
			vst1_u8(&testData[h*TEST_WIDTH+w], result);
		}
	}

	dumpData(TEST_WIDTH, TEST_HEIGHT, 100, 50);
}

unsigned short int A[] = {1,2,3,4}; // array with 4 elements

void addTest2()

{
	uint16x4_t v; // declare a vector of four 16-bit lanes
	v = vld1_u16(A); // load the array from memory into a vector
	v = vadd_u16(v, v); // double each element in the vector
	vst1_u16(A, v); // store the vector back to memory

	for(int i=0; i<4; i++) {
		LOGI("A[%d]: %d", i, A[i]);
	}
}

unsigned char B[] = {1,2,3,4}; // array with 4 elements

void addTest3()

{
	uint16x4_t v; // declare a vector of four 16-bit lanes
	v = vld1_u16(A); // load the array from memory into a vector
	v = vadd_u16(v, v); // double each element in the vector
	vst1_u16(A, v); // store the vector back to memory

	for(int i=0; i<4; i++) {
		LOGI("A[%d]: %d", i, A[i]);
	}
}