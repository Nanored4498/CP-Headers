#include <vector>
#include <complex>
#include <numbers>
#include <cmath>

using namespace std;

void fft(vector<complex<double>> &P, bool invert=false) {
	const int n = P.size();

	// swap indices with their mirror binary
	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j&bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) swap(P[i], P[j]);
	}

	// Transform
	for(int len = 2; len <= n; len <<= 1) {
		const int half = len >> 1;
		const double a = 2 * numbers::pi / len * (invert ? -1. : 1.);
		for(int j = 0; j < half; ++j) {
			const complex<double> mul(cos(j*a), sin(j*a));
			for(int i = 0; i < n; i += len) {
				const complex<double> even = P[i+j], odd = P[i+j+half] * mul;
				P[i+j] = even + odd;
				P[i+j+half] = even - odd;
			}
		}
	}

	// Divide by n if inverse
	if(invert) for(auto &x : P) x /= n;
}

void fft_mult_inplace(vector<complex<double>> &P, vector<complex<double>> &Q) {
	int size = 1, n = P.size() + Q.size() - 1;
	while(size < n) size <<= 1;
	P.resize(size, 0);
	Q.resize(size, 0);
	fft(P);
	fft(Q);
	for(int i = 0; i < size; ++i) P[i] *= Q[i];
	fft(P, true);
	P.resize(n);
}