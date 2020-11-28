#pragma once

#include <cstdint>
#include <cstdarg>
#include <ostream>


namespace linalg {
	/*
		@Vector of arbitrary dimension
	*/

	class vec {
	public:

		vec(uint32_t count):
			count_{ count } {
			vals_ = new double[count];
		}

		vec& operator()(va_list args) {
			va_start(args, count_);
			for (int i = 0; i < count_; ++i) {
				vals_[i] = va_arg(args, double);
			}
			return *this;
		}

		double operator[](int32_t idx) {
			if (idx < 0) {
				return vals_[count_ + idx];
			}
			else {
				return vals_[idx];
			}
		}

		/*friend vec operator+(const vec& p, const vec& q) {
			vec out(p.count());

			for (int i = 0; i < p.count(); ++i) {
				out.vals_[i] = p[i] + q[i];
			}
			return out;
		}*/

		friend std::ostream& operator<<(std::ostream& o, vec& v) {
			for (int i = 0; i < v.count(); ++i) {
				o << v[i] << " ";
			}
			putchar('\n');
			
			return o;
		}

	protected:
		inline uint32_t count() const noexcept { return count_; }

	private:
		double* vals_;
		uint32_t count_;
	};


}