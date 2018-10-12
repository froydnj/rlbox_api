#include "libtest.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

unsigned long simpleAddNoPrintTest(unsigned long a, unsigned long b)
{
	return a + b;
}

int simpleAddTest(int a, int b)
{
	printf("simpleAddTest\n");
	fflush(stdout);
	return a + b;
}

size_t simpleStrLenTest(const char* str)
{
	printf("simpleStrLenTest\n");
	fflush(stdout);
	return strlen(str);
}


int simpleCallbackTest(unsigned a, const char* b, CallbackType callback)
{
	int ret;
	
	printf("simpleCallbackTest\n");
	fflush(stdout);

	ret = callback(a + 1, b, &a);
	return ret;
}

int simpleWriteToFileTest(FILE* file, const char* str)
{
	printf("simpleWriteToFileTest\n");
	fflush(stdout);
	return fputs(str, file);
}

char* simpleEchoTest(char * str)
{
	printf("simpleEchoTest\n");
	fflush(stdout);
	return str;
}

float simpleFloatAddTest(const float a, const float b)
{
	printf("simpleFloatAddTest\n");
	return a + b;
}

double simpleDoubleAddTest(const double a, const double b)
{
	printf("simpleDoubleAddTest\n");
	return a + b;
}

unsigned long simpleLongAddTest(unsigned long a, unsigned long b)
{
	printf("simpleLongAddTest\n");
	fflush(stdout);
	return a + b;
}

struct testStruct simpleTestStructVal()
{
	struct testStruct ret;
	ret.fieldLong = 7;
	ret.fieldString = "Hello";
	ret.fieldBool = 1;
	strcpy(ret.fieldFixedArr, "Bye");
	return ret;
}

struct testStruct* simpleTestStructPtr()
{
	struct testStruct* ret = (struct testStruct*) malloc(sizeof(struct testStruct));
	ret->fieldLong = 7;
	ret->fieldString = "Hello";
	ret->fieldBool = 1;
	strcpy(ret->fieldFixedArr, "Bye");
	return ret;
}

struct testStruct simpleTestStructValBadPtr()
{
	struct testStruct ret = simpleTestStructVal();
	//explicitly mess up the top bits of the pointer. The sandbox checks outside the sandbox should catch this
	#if defined(_M_IX86) || defined(__i386__)
		ret.fieldString = (char *)((((uintptr_t) ret.fieldString) & 0x3FFFFFFF) | 0xC0000000);
	#else
		ret.fieldString = (char *)((((uintptr_t) ret.fieldString) & 0xFFFFFFFF) | 0x1234567800000000);
	#endif
	return ret;
}

struct testStruct* simpleTestStructPtrBadPtr()
{
	struct testStruct* ret = simpleTestStructPtr();
	//explicitly mess up the top bits of the pointer. The sandbox checks outside the sandbox should catch this
	#if defined(_M_IX86) || defined(__i386__)
		ret->fieldString = (char *)((((uintptr_t) ret->fieldString) & 0x3FFFFFFF) | 0xC0000000);
	#else
		ret->fieldString = (char *)((((uintptr_t) ret->fieldString) & 0xFFFFFFFF) | 0x1234567800000000);
	#endif
	return ret;
}

int* echoPointer(int* pointer)
{
	return pointer;
}

double simplePointerValAddTest(double* ptr, double val)
{
	printf("simplePointerValAddTest\n");
	return val + *ptr;
}

struct pointersStruct initializePointerStruct(void* initVal)
{
	struct pointersStruct ret;
	ret.firstPointer = initVal;
	ret.pointerArray[0] = (void*) (((uintptr_t) initVal) + 1);
	ret.pointerArray[1] = (void*) (((uintptr_t) initVal) + 2);
	ret.pointerArray[2] = (void*) (((uintptr_t) initVal) + 3);
	ret.pointerArray[3] = (void*) (((uintptr_t) initVal) + 4);
	ret.lastPointer =     (void*) (((uintptr_t) initVal) + 5);
	return ret;
}