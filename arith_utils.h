#include <vector>

using namespace std;

template <typename T>
struct AU {
	vector<T> _fact, _ifact, _bernoulli;
	
	AU(): _fact(1, 1), _ifact(1, 1), _bernoulli(1, 1) {}

	T fact(int n) {
		if(n >= _fact.size()) {
			int i = _fact.size();
			_fact.resize(n+1);
			for(; i <= n; ++i) _fact[i] = i * _fact[i-1];
		}
		return _fact[n];
	}

	T ifact(int n) {
		if(n >= _ifact.size()) {
			int i0 = _ifact.size();
			_ifact.resize(n+1);
			for(int j = n; j >= i0; --j) _ifact[j] = inv(fact(j));
		}
		return _ifact[n];
	}

	T C(int n, int k) {
		if(k < 0 || k > n) return 0;
		return fact(n) * ifact(k) * ifact(n-k);
	}

	T Bernoulli(int n) {
		if(n >= _bernoulli.size()) {
			int i = _bernoulli.size();
			_bernoulli.resize(n+1);
			for(;i <= n; ++i) {
				_bernoulli[i] = 0;
				for(int j = 0; j < i; ++j)
					_bernoulli[i] -= C(i, j) * _bernoulli[j] / (i - j + 1);
			}
		}
		return _bernoulli[n];
	}

	// 0^p + 1^p + ... + N^p
	T sumPow(T N, int p) {
		if(p == 0) return N+1;
		T ans = 0;
		for(int k = 0; k <= p; ++k)
			ans += Bernoulli(k) * C(p+1, k) * pow(N+1, p+1-k);
		return ans / (p+1);
	}
};
