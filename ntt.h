#include <vector>
#include <cassert>

using namespace std;

// Need to compute a genrator g of T before
template <typename T>
void NTT(vector<T> &P, bool invert=false) {
	int n = P.size();
	assert((T::mod-1) % n == 0);
	T g = pow(T::g, (T::mod-1) / n);
	if(invert) g = inv(g);

	// swap indices with their mirror binary
	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j&bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) swap(P[i], P[j]);
	}

	// Transform
	for(int len = 2; len <= n; len <<= 1) {
		int half = len >> 1;
		T wl = g;
		for(int i = len; i < n; i <<= 1) wl *= wl;
		for(int i = 0; i < n; i += len) {
			T w = 1;
			for(int j = 0; j < half; ++j) {
				T even = P[i+j];
				T odd = P[i+half+j] * w;
				P[i+j] = even + odd;
				P[i+half+j] = even - odd;
				w *= wl;
			}
		}
	}

	// Divide by n if inverse
	if(invert) {
		T inv_n = inv(T(n));
		for(T &x : P) x *= inv_n;
	}
}

template <typename T>
void NTT_mult_inplace(vector<T> &P, vector<T> &Q) {
	int size = 1, n = P.size() + Q.size() - 1;
	while(size < n) size <<= 1;
	P.resize(size, 0);
	Q.resize(size, 0);
	NTT<T>(P);
	NTT<T>(Q);
	for(int i = 0; i < size; ++i) P[i] *= Q[i];
	NTT<T>(P, true);
	P.resize(n);
}
