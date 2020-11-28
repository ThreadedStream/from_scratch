
#include <iostream>
#include "../tests/matrixops_test.hpp"


using namespace test;

int main(int argc, const char*[])
{
	
	matrixops_test::matrixseq_test<10, 5, 5, 10>(1); 

	return 0;
}

