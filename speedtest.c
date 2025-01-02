#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define CHECKMALLOC(ptr) do{\
	if(ptr == NULL){\
		fprintf(stderr, "Failed to alloc mem\n");\
		exit(1);\
	}\
}while(0)

#define ITERATIONS 250000000

#define MAKE_INT_TEST(type) do{ \
	type * randomData = malloc(sizeof(type) * ITERATIONS); \
	CHECKMALLOC(randomData); \
	for(size_t i = 0; i < ITERATIONS; i++){ \
		randomData[i] = (type)rand(); \
		if(randomData[i] == 0){ \
			randomData[i] = 1; \
		} \
	} \
	type intType = 0; \
	start = clock(); \
	for(size_t i = 0; i < ITERATIONS; i++){ \
		intType += randomData[i]; \
	} \
	end = clock(); \
	printf( # type " addition time: %f\n", (double)(end - start) / CLOCKS_PER_SEC); \
	start = clock();\
	for(size_t i = 1; i < ITERATIONS; i += 2){ \
		intType += randomData[i-1] * randomData[i]; \
	} \
	end = clock(); \
	printf( # type " multiplication time: %f\n", (double)(end - start) / CLOCKS_PER_SEC); \
	start = clock(); \
	for(size_t i = 1; i < ITERATIONS; i += 2){ \
		intType += randomData[i-1] + randomData[i]; \
	} \
	end = clock(); \
	printf( # type " division time: %f\n", (double)(end - start) / CLOCKS_PER_SEC); \
	free(randomData); \
	printf("Dump: %d\n", (int) intType); \
	printf("===\n"); \
}while(0)

int main(int argc, char* argv[]){
	getchar();
	/*
	if(argc != 2){
		fprintf(stderr, "Usage: ./speedtest <ITERATIONS>\n");
		return 1;
	}
	*/
	//size_t ITERATIONS = strtoul(argv[1], NULL, 10);
	//printf("ITERATIONS: %lu\n", iterations);

	clock_t start, end;
	srand(time(NULL));
	
	uint32_t unsignedTest = 0;
	int32_t signedTest = 0;

	float floatTest = 0;
	double doubleTest = 0;

	//void* randomData = malloc(ITERATIONS * sizeof(uint32_t));
	uint32_t* randomUnsignedData;
	int32_t* randomSignedData;
	float* randomFloatData;
	double* randomDoubleData;

	MAKE_INT_TEST(uint8_t);
	MAKE_INT_TEST(int8_t);
	MAKE_INT_TEST(uint16_t);
	MAKE_INT_TEST(int16_t);
	MAKE_INT_TEST(uint32_t);
	MAKE_INT_TEST(int32_t);
	MAKE_INT_TEST(uint64_t);
	MAKE_INT_TEST(int64_t);

	randomUnsignedData = malloc(ITERATIONS * sizeof(*randomUnsignedData));
	CHECKMALLOC(randomUnsignedData);


	/*
	for(size_t i = 0; i < ITERATIONS; i++){
		randomUnsignedData[i] = (uint32_t)rand();
		if(randomUnsignedData[i] == 0){
			randomUnsignedData[i] = 1;
		}
	}
	
	// unsigned int loops
	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		unsignedTest += randomUnsignedData[i]; // This is a bit hacky but is valid
	}
	end = clock();
	printf("u32 addition time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		unsignedTest *= randomUnsignedData[i];
	}
	end = clock();
	printf("u32 multiplication time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		unsignedTest /= randomUnsignedData[i];
	}
	end = clock();
	printf("u32 division time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	free(randomUnsignedData);

	printf("===\n");

	randomSignedData = malloc(ITERATIONS * sizeof(*randomSignedData));
	CHECKMALLOC(randomSignedData);

	for(size_t i = 0; i < ITERATIONS; i++){
		randomSignedData[i] = (int32_t)rand();
		if(randomSignedData[i] == 0){
			randomSignedData[i] = 1;
		}
	}

	// signed int loops
	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		signedTest += randomSignedData[i];
	}
	end = clock();
	printf("i32 addition time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		signedTest *= randomSignedData[i];
	}
	end = clock();
	printf("i32 multiplication time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		signedTest /= randomSignedData[i];
	}
	end = clock();
	printf("i32 division time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	free(randomSignedData);
	*/

	randomFloatData = malloc(ITERATIONS * sizeof(*randomFloatData));
	CHECKMALLOC(randomFloatData);

	for(size_t i = 0; i < ITERATIONS; i++){
		randomFloatData[i] = ((float)rand() / RAND_MAX) * FLT_MAX;
		randomFloatData[i] *= -1 * rand() % 2;
		if(randomFloatData[i] == 0){
			randomFloatData[i] = 1;
		}
	}

	// float loops
	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		floatTest += randomFloatData[i];
	}
	end = clock();
	printf("float addition time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 1; i < ITERATIONS; i += 2){
		floatTest += randomFloatData[i-1] * randomFloatData[i];
	}
	end = clock();
	printf("float multiplication time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		floatTest += randomFloatData[i-1] / randomFloatData[i];
	}
	end = clock();
	printf("float division time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	free(randomFloatData);

	printf("===\n");
	
	randomDoubleData = malloc(ITERATIONS * sizeof(*randomDoubleData));
	CHECKMALLOC(randomDoubleData);

	for(size_t i = 0; i < ITERATIONS; i++){
		randomDoubleData[i] = ((float)rand() / RAND_MAX) * DBL_MAX;
		randomDoubleData[i] *= -1 * rand() % 2;
		if(randomDoubleData[i] == 0){
			randomDoubleData[i] = 1;
		}
	}

	// double loops
	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		doubleTest += randomDoubleData[i];
	}
	end = clock();
	printf("double addition time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 1; i < ITERATIONS; i += 2){
		doubleTest += randomDoubleData[i-1] * randomDoubleData[i];
	}
	end = clock();
	printf("double multiplication time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for(size_t i = 1; i < ITERATIONS; i += 2){
		doubleTest /= randomDoubleData[i-1] / randomDoubleData[i];
	}
	end = clock();
	printf("double division time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	free(randomDoubleData);

	printf("Dump: %f\n", unsignedTest + signedTest + floatTest + doubleTest);


	return 0;
}
