#include <vector>
#include <cassert>

using namespace std;

template <typename T>
T computeG() {
	vector<int> ps;
	int m2 = T::mod-1;
	for(int p = 2; p <= m2; ++p) if(m2 % p == 0) {
		ps.push_back(p);
		while(m2 % p == 0) m2 /= p;
	}
	T G = 2;
	m2 = T::mod-1;
	while(true) {
		bool good = true;
		for(int p : ps) if(pow(G, m2/p) == 1) {
			good = false;
			break;
		}
		if(good) return G;
		else ++G;
	}
	return G;
}

// Need to compute a genrator g of T before
template <typename T>
void NTT(vector<T> &P, T g, bool invert=false) {
	const int n = P.size();
	assert((T::mod-1) % n == 0);
	g = pow(g, (T::mod-1) / n);
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
		const int half = len >> 1;
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
void NTT_mult_inplace(vector<T> &P, vector<T> &Q, T g) {
	int size = 1, n = P.size() + Q.size() - 1;
	while(size < n) size <<= 1;
	P.resize(size, 0);
	Q.resize(size, 0);
	NTT<T>(P, g);
	NTT<T>(Q, g);
	for(int i = 0; i < size; ++i) P[i] *= Q[i];
	NTT<T>(P, g, true);
	P.resize(n);
}
