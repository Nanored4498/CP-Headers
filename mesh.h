#include <vector>

using namespace std;

struct Halfedges {
	vector<int> next, from;
	inline int to(int h) const { return from[h^1]; }
	inline int opp(int h) const { return h^1; }
	inline int size() const { return next.size(); }
	inline int E() const { return size()/2; }

	void swap(int e) {
		int h = 2*e;
		int nh = next[h];
		int ph = next[nh];
		int h2 = 2*e+1;
		int nh2 = next[h2];
		int ph2 = next[nh2];
		next[h] = ph;
		next[ph] = nh2;
		next[nh2] = h;
		next[h2] = ph2;
		next[ph2] = nh;
		next[nh] = h2;
		from[h] = from[ph2];
		from[h2] = from[ph];
	}
};

template <typename P>
struct Mesh : Halfedges {
	vector<P> &X;
	Mesh(vector<pt> &pts): Halfedges(), X(pts) {}
	inline P& org(int h) { return X[from[h]]; }
	inline P& dst(int h) { return X[to(h)]; }
};