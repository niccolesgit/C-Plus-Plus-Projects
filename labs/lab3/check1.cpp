#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

void compute_squares(unsigned int* a, unsigned int* b, int n) {
	for (int i = 0; i < n; i++) {
		*(b + i) = *(a + i) * *(a + i);
		std::cout << *(b + i) << std::endl;
	}
}

int main() {
	unsigned int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	unsigned int b[10];
	compute_squares(a, b, 10);
}
