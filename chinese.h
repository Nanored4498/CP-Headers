#include <vector>
#include <cassert>

using namespace std;

template <typename T>
T xGCD(T a, T b, T &u, T &v) {
	if(b == 0) {
		u = 1;
		v = 0;
		return a;
	}
	int u2, v2, g = xGCD(b, a%b, u2, v2);
	u = v2;
	v = u2 - v2 * (a/b);
	return g;
}

// return x s.t. x % m[i] = a[i]
template <typename T>
T chineseRM(vector<T> &a, vector<T> &m) {
	assert(a.size() == m.size());
	if(a.empty()) return 0;
	T b = a[0], n = m[0];
	for(int i = 1; i < a.size(); ++i) {
		T u, v, g = xGCD(m[i], n, u, v);
		T rg = b % g;
		if((a[i] % g) != rg) return -1;
		n /= g;
		b = u * (m[i] / g) * (b - rg) + v  * n * (a[i] - rg) + rg;
		n *= m[i];
		b %= n;
		if(b < 0) b += n;
	}
	return b;
}