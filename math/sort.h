#pragma once

#include <cstdint>

template<typename T>
static bool greater(const T& a, const T& b)
{
    return a > b;
}

template <typename T>
void CombSort(T* a, std::uint32_t n)
{
	std::uint32_t gap = n;
	bool swapped = true;

	while ((gap > 1) || swapped) {
		if (gap > 1) {
			gap = (gap * 4) / 5;
		}

		swapped = false;

		for (std::uint32_t i = 0; i + gap < n; i++) {
			if (a[i + gap] > a[i]) {
				T temp = a[i];
				a[i] = a[i + gap];
				a[i + gap] = temp;

				swapped = true;
			}
		}
	}
}
