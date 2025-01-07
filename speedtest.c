#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

#define CHECKMALLOC(ptr) do{\
	if(ptr == NULL){\
		fprintf(stderr, "Failed to alloc mem\n");\
		exit(1);\
	}\
}while(0)

#define ITERATIONS 1000000000

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
	start = clock(); \
	for(size_t i = 1; i < ITERATIONS; i += 2){ \
		intType += randomData[i-1] % randomData[i]; \
	} \
	end = clock(); \
	printf( # type " modulus time: %f\n", (double)(end - start) / CLOCKS_PER_SEC); \
	free(randomData); \
	printf("Dump: %d\n", (int) intType); \
	printf("===\n"); \
}while(0)

int main(int argc, char* argv[]){
	long pid = (long)getpid();
	printf("PID: %ld, press enter to continue\n", pid);
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

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		floatTest += (randomFloatData[i-1] / randomFloatData[i] - (int)(randomFloatData[i-1] / randomFloatData[i])) * randomFloatData[i-1];
	}
	end = clock();
	printf("float modulus time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

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

	start = clock();
	for(size_t i = 0; i < ITERATIONS; i++){
		doubleTest += fmod(randomDoubleData[i-1], randomDoubleData[i]);
	}
	end = clock();
	printf("double modulus time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	free(randomDoubleData);

	printf("Dump: %f\n", unsignedTest + signedTest + floatTest + doubleTest);


	return 0;
}
