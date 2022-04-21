#include <vector>

using namespace std;

// For this structure op(x_1+a, op(x_2+a, op(..., x_n+a))) = op(x_1, op(x_2, op(..., x_n))) + pow_op(a, n)
// exemple:
//    op(a, b) = a+b        pow_op(a, n) = a*n
//    op(a,b) = min(a, b)   pow_op(a, n) = a
template<typename T, typename OP, typename POP>
struct LazySegmentTree {
	int start;

	LazySegmentTree(int n, const OP &_op, const POP &pow_op, T e):
		start(1), op(_op), pow_op(pow_op), e(e) {
		while(start < n) start <<= 1;
		v.assign(start << 1, e);
		lazy.assign(start << 1, 0);
	}

	void setInit(int i, T x) { v[start + i] = x; }
	void init() {
		lazy.assign(start << 1, 0);
		for(int i = start-1; i > 0; --i)
			v[i] = op(v[i<<1], v[(i<<1)+1]);
	}

	void add(int a, int b, T x) { _a=a; _b=b; add(1, 0, start-1, x); }
	void add(int i, T x) {
		aux_add_set(i);
		v[i] += x;
		for(i >>= 1; i > 0; i >>= 1) v[i] = op(v[i<<1], v[(i<<1)+1]);
	}
	void set(int i, T x) {
		aux_add_set(i);
		v[i] = x;
		for(i >>= 1; i > 0; i >>= 1) v[i] = op(v[i<<1], v[(i<<1)+1]);
	}

	T querry(int a, int b) { _a=a; _b=b; return querry(1, 0, start-1); }
	T querry(int i) {
		i += start;
		int s = 1, size=start;
		while(i>>s) ++s;
		while(s > 0) {
			push(i>>(--s), size);
			size >>= 1;
		}
		return v[i];
	}
	T querryAll() { push(1, start); return v[1]; }

private:
	OP op;
	POP pow_op;
	const T e;
	vector<T> v, lazy;
	int _a, _b;

	void push(int i, int size) {
		if(lazy[i] == 0) return;
		v[i] += pow_op(lazy[i], size);
		if(i < start) {
			lazy[i<<1] += lazy[i];
			lazy[(i<<1)+1] += lazy[i];
		}
		lazy[i] = 0;
	}

	inline void aux_add_set(int &i) {
		i += start;
		int s = 1, size = start;
		while(i>>s) ++s;
		-- s;
		push(1, size);
		while(s > 0) {
			-- s;
			size >>= 1;
			push(i>>s, size);
			push((i>>s)^1, size);
		}
	}

	void add(int i, int l, int r, T x) {
		if(r < _a || _b < l) return push(i, r-l+1);
		if(_a <= l && r <= _b) {
			lazy[i] += x;
			return push(i, r-l+1);
		}
		push(i, r-l+1);
		int mid = (l+r) >> 1;
		add(i<<1, l, mid, x);
		add((i<<1)+1, mid+1, r, x);
		v[i] = op(v[i<<1], v[(i<<1)+1]);
	}

	T querry(int i, int l, int r) {
		if(r < _a || _b < l) return e;
		push(i, r-l+1);
		if(_a <= l && r <= _b) return v[i];
		int mid = (l+r) >> 1;
		return op(querry(i<<1, l, mid), querry((i<<1)+1, mid+1, r));
	}
};
