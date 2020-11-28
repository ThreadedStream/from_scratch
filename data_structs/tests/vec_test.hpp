#include "../src/vec.hpp"
#include <iostream>
#include <chrono>
#include <vector>

using namespace linalg;

namespace test {
	class vec_test {
	public:
		vec_test() = delete;

		static void test_vec_init(int num_of_iters);

		static void test_vec_add();

		static void test_vec_dot();

	private:
		
	};
}