#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test");
		// TODO: Add more Compression test cases
        TEST_CASE_DESCRIBE(testShortPositiveRun, "Short positive run test");
        TEST_CASE_DESCRIBE(testLongPositiveRun, "Long positive run test");
        TEST_CASE_DESCRIBE(testShortSingleThenPositiveRun, "Short then positive run test");
        // TEST_CASE_DESCRIBE(testPositiveRunThenSingle, "Short positive run then single test");
        TEST_CASE_DESCRIBE(testShortNegativetoPositiveRun, "Short negative to positive run test");
        TEST_CASE_DESCRIBE(testReallyLongPositiveRun, "Really long positive run test");
        TEST_CASE_DESCRIBE(testPositiveThenNegativeRun, "Positive then negative run test");
        TEST_CASE_DESCRIBE(testShortNegativeRun, "Short negative run test");
        TEST_CASE_DESCRIBE(testLongNegativeRun, "Long negative run test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRun, "Really long negative run test");
        TEST_CASE_DESCRIBE(alternatingRun, "Alternating run test");
	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testShortPositiveRun()
    {
        char test[] = "aa";
        char expected[] = "\x02" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testLongPositiveRun()
    {
        char test[] = "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb";
        char expected[] = "\x64" "b";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongPositiveRun()
    {
        char test[] = "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb";
        char expected[] = "\x7f" "b" "\x49" "b";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testShortSingleThenPositiveRun()
    {
        char test[] = "abbbbb";
        char expected[] = "\x01" "a" "\x05" "b";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testPositiveRunThenSingle()
    {
        char test[] = "bbbbba";
        char expected[] = "\x05" "b" "\x01" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testPositiveThenNegativeRun()
    {
        char test[] = "aaaaabcde";
        char expected[] = "\x05" "a" "\xfc" "bcde";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testShortNegativeRun()
    {
        char test[] = "abcd";
        char expected[] = "\xfc" "abcd";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testShortNegativetoPositiveRun()
    {
        char test[] = "abcdddd";
        char expected[] = "\xfd" "abc" "\x04" "d";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testLongNegativeRun()
    {
        char test[] = "abcdefghijklmnopqrstuvwxyz";
        char expected[] = "\xe6" "abcdefghijklmnopqrstuvwxyz";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongNegativeRun()
    {
        char test[] = "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        ;
        char expected[] = "\x81" "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefg"
        "\xb7" "hij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij"
        "abcdefghij";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void alternatingRun()
    {
        char test[] = "abbbbbcacuuuyxdrrrrrrriikkqwe";
        char expected[] = "\x01" "a" "\x05" "b" "\xfd" "cac" "\x03" "u" "\xfd"
        "yxd" "\x07" "r" "\x02" "i" "\x02" "k" "\xfd" "qwe";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRun, "Basic positive run test");
		// TODO: Add more Decompression test  cases
        TEST_CASE_DESCRIBE(testBasicPositiveRunsDecom, "Basic positive runs test decom");
        TEST_CASE_DESCRIBE(testReallyLongPositiveRunDecom, "Really long positive run test decom");
        TEST_CASE_DESCRIBE(testBasicNegativeRunDecom, "Basic negative run test decom");
        TEST_CASE_DESCRIBE(testAlternatingRunDecom, "Alternating run test decom");
	}
	
	void testBasicPositiveRun()
	{
		char test[] = "\x28" "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testBasicPositiveRunsDecom()
    {
        char test[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
        "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
        char expected[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
        "ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongPositiveRunDecom()
    {
        char test[] = "\x7f" "b" "\x49" "b";
        char expected[] = "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb"
        "bbbbbbbbbb";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testBasicNegativeRunDecom()
    {
        char test[] = "\xfc" "abcd";
        char expected[] = "abcd";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternatingRunDecom()
    {
        char test[] = "\x01" "a" "\x05" "b" "\xfd" "cac" "\x03" "u" "\xfd"
        "yxd" "\x07" "r" "\x02" "i" "\x02" "k" "\xfd" "qwe";
        char expected[] = "abbbbbcacuuuyxdrrrrrrriikkqwe";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			break;
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
