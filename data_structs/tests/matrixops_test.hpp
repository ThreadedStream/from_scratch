#pragma once
#include <iostream>
#include "../src/matrixops.hpp"
#include <chrono>
#include <vector>
#include <random>

namespace test {
	using namespace linalg;
	class matrixops_test {
	public:

		template<int r, int c>
		static std::vector<std::shared_ptr<mat<r,c>>> 
			generate_matrices(int num_of_mats) {

			std::uniform_real_distribution<float> dist(1.0, 60.0);
			std::default_random_engine generator;
			std::vector<std::shared_ptr<mat<r, c>>> out;
			while (num_of_mats--) {
				std::shared_ptr<mat<r, c>> m = std::make_shared<mat<r,c>>();
				for (int i = 0; i < r; ++i) {
					for (int j = 0; j < c; ++j) {
						m->vals_[i][j] = dist(generator);
					}
				}
				out.emplace_back(m);
			}

			return out;
		}

		template<int r, int c, int p, int q>
		static void matrixseq_test(int iters) {

			std::cout << "Testing "<<iters<<" sequential matrix multiplications\n";
			std::cout << "Dimensionality of matrices: ( [" << r << "," << c << "]; [" << p << "," << q << "] )\n";
			std::cout << "**********************************************\n";
			auto start = std::chrono::system_clock::now();
			
			auto vec0 = generate_matrices<r,c>(iters);
			auto vec1 = generate_matrices<p,q>(iters);

			for (int i = 0; i < iters; ++i) {
				matrixops::mulseq<r, c, p, q>(*(vec0[i].get()), *(vec1[i].get()));
			}

			auto end = std::chrono::system_clock::now();
			std::cout << "Finishing a computation stage...\n";
			std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
		}
		template<int r, int c, int p, int q>
		static void matrixpar_test(int iters) {
			std::cout << "Testing "<<iters<<" parallel matrix multiplications\n";
			std::cout << "Dimensionality of matrices: ( [" << r << "," << c << "]; [" << p << "," << q << "] )\n";
			std::cout << "**********************************************\n";
			auto start = std::chrono::system_clock::now();

			auto vec0 = generate_matrices<r, c>(iters);
			auto vec1 = generate_matrices<p, q>(iters);

			for (int i = 0; i < iters; ++i) {
				matrixops::mulpar<r, c, p, q>(*(vec0[i].get()), *(vec1[i].get()));
			}

			auto end = std::chrono::system_clock::now();

			std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
		}
	};
}
