#include "vec_test.hpp"


void test::vec_test::test_vec_init(int num_of_iters)
{
	std::cout << "Testing vector initialization\n";
	std::cout << "*********************************\n";
	auto start = std::chrono::system_clock::now();

	std::cout << "Starting...\n";

	auto arr_up_to_n = [&](uint32_t n) -> std::vector<uint32_t> {
		std::vector<uint32_t> vec;
		
		return vec;
	};

	for (int i = 0; i < num_of_iters; ++i) {
		vec v(i);
	}
}

void test::vec_test::test_vec_add()
{
}

void test::vec_test::test_vec_dot()
{
}
