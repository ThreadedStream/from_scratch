#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <omp.h>

namespace linalg {

	template<uint32_t m, uint32_t n>
	struct mat {
		double** vals_;

		inline mat() {
			vals_ = twodee(m, n);
		}
		inline static auto twodee = [&](int k, int j) -> double** {
			double** c = new double*[k];

			for (int i = 0; i < k; ++i) {
				c[i] = new double[j];
			}
			return c;
		};

		*inline ~mat() {
			delete[] vals_;
		}

		//double operator()(const int32_t idx0, const int32_t idx1) const{
		//	return vals_[idx0][idx1];
		//}

	};

	struct matrixops {
		/*
			@Returns result of multiplication of two matrices a and b;
			Params:
				@@a - matrix a
				@@b - matrix b
				@@dim_a - dimensionality of a
				@@dim_b - dimensionality of b

		*/

		template<int dima_0, int dima_1, int dimb_0, int dimb_1>
		static std::shared_ptr<mat<dima_0, dimb_1>>
			mulseq(const mat<dima_0, dima_1>& a,
				const mat<dimb_0, dimb_1>& b) {

			if (dima_1 != dimb_0) {
				std::cout << "Invalid dimensionality!!!\n";
				return nullptr;
			}

			std::shared_ptr<mat<dima_0, dimb_1>> c = std::make_shared<mat<dima_0, dimb_1>>();

			for (int i = 0; i < dima_1; ++i) {
				for (int j = 0; j < dimb_0; ++j) {
					c->vals_[i][j] = 0;
					for (int k = 0; k < dimb_1; ++k) {
						c->vals_[i][j] += a.vals_[i][k] * b.vals_[k][j];
					}
				}
			}

			return c;
		}
		
		template<int dima_0, int dima_1, int dimb_0, int dimb_1>
		static std::shared_ptr<mat<dima_0, dimb_1>>
			mulpar(const mat<dima_0, dima_1>& a,
				   const mat<dimb_0, dimb_1>& b) {
			
			std::shared_ptr<mat<dima_0, dimb_1>> c = std::make_shared<mat<dima_0, dimb_1>>();
			int i, j, k;

#pragma omp parallel shared(a,b,c) private(i,j,k)
			{
			#pragma omp for schedule(static)
				for (i = 0; i < dima_1; i++) {
					for (j = 0; j < dimb_0; ++j) {
						c->vals_[i][j] = 0;
						for (int k = 0; k < dimb_1; ++k) {
							c->vals_[i][j] = (c->vals_[i][j]) + (a.vals_[i][k] * b.vals_[k][j]);
						}
					}
				}
			}

			return c;
		}
	};

	template<int k, int n>
	std::ostream& operator<<(std::ostream& o, mat<k, n>& m) {
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < n; ++j) {
				o << m.vals_[i][j] << " ";
			}
			putchar('\n');
		}

		return o;
	}
}




