#include <vector>
#include <functional>

using namespace std;

template<typename T>
struct Fenwick {
	inline static int LSB(int i) { return i&(-i); }
	vector<T> v;

	Fenwick() = default;
	Fenwick(int n): v(n+1, 0) {}

	void init() {
		for(int i = 1; i < (int) v.size(); ++i) v[i] += v[i-1];
		for(int i = v.size()-1; i > 0; --i) v[i] -= v[i-LSB(i)];
	}

	void add(int i, T x) {
		for(; i < (int) v.size(); i += LSB(i)) v[i] += x;
	}
	void set(int i, T x) { add(i, x - querry(i, i)); }

	T querry(int i) {
		T ans = 0;
		for(; i > 0; i -= LSB(i)) ans += v[i];
		return ans;
	}
	T querry(int a, int b) { return querry(b) - querry(a-1); }
};

template<typename T, typename OP>
struct SegmentTree {
	OP op;
	const T e;
	vector<T> v;
	int start;

	SegmentTree(int n, const OP &op, const T &e): op(op), e(e), start(1) {
		while(start < n) start <<= 1;
		v.assign(start << 1, e);
	}

	void set(int i, const T &x) {
		v[i+=start] = x;
		while((i >>= 1) > 0) v[i] = op(v[i<<1], v[(i<<1)+1]);
	}
	void add(int i, const T &x) { set(i, v[start+i]+x); }

	T querry(int a, int b) {
		T xa = e, xb = e;
		for(a += start, b += start; a <= b; a >>= 1, b >>= 1) {
			if(a&1) xa = op(xa, v[a++]);
			if(!(b&1)) xb = op(v[b--], xb);
		}
		return op(xa, xb);
	}
};
