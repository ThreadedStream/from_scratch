#pragma once
#include <cstdint>
#include <initializer_list>
#include <algorithm>
#include <type_traits>

namespace handmade{
	template<typename Type>
	class array {
	public:
		array(uint32_t cap = 4) : cap_{ cap }, size_{ 0 } {
			vals_ = new Type[cap_];

		};
		array(const std::initializer_list<Type>& vals):
			size_{ 0 } {
			
			cap_ = vals.size() * 2;
			_copy(vals);
		}

		/*
			@Array invalidation
		*/
		~array() {
			delete[] vals_;
		}
		
		Type operator[](const int32_t idx) {
			if (idx < 0) {
				return vals_[size_ + idx];
			}
			return vals_[idx];
		}

		array& insert_back(Type val) {
			if (size_ == cap_) {
				_renew();
				vals_[size_] = val;
				size_++;
			}
			else {
				vals_[size_] = val;
				size_++;
			}
			return *this;
		}

		array& remove_back() {
			if (std::is_pointer<Type>::value) {
				delete vals_[size_ - 1];
				size_--;
			}
			else {
				vals_[size_ - 1] = NULL;
				size_--;
			}
			return *this;
		}

		array& insert_front(Type val) {
			_shift_to_end();
			vals_[0] = val;
			size_++;

			return *this;
		}

		inline uint32_t size() const noexcept { return size_; }

	private:
		uint32_t cap_;
		uint32_t size_;
		Type* vals_;

		//methods
		/*
			@Function is called only once, in constructor
		*/
		void _copy(const std::initializer_list<Type> from) {
			//Presuming that array is empty.
			vals_ = new Type[from.size() * 2];
			int i = 0;
			for (; i < from.size(); ++i) {
				vals_[i] = *(from.begin() + i);
				size_++;
			}
		}

		void _renew() {
			cap_ = size_ * 4;
			Type* to = new Type[cap_];

			for (int i = 0; i < size_; ++i) {
				to[i] = vals_[i];
			}
			auto temp = vals_;
			
			vals_ = to;

			delete[] temp;
		}

		void _shift_to_end() {
			/*
				utility lambda to shift array values
			*/
			auto shlam = [&]() {
				for (int i = size_; i >= 0; --i) {
					vals_[i + 1] = vals_[i];
				}
			};

			if (size_ + 1 < cap_) {
				shlam();
			}
			else {
				_renew();
				shlam();
			}
		}
	};

	template<typename Type>
	std::ostream& operator<<(std::ostream& o, array<Type>& arr) {
		
		for (int32_t i = 0; i < arr.size(); ++i) {
			o << arr[i] << " ";
		}
		putchar('\n');

		return o;
	}
}
