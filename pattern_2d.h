#include "aho_corasick.h"
#include "kmp.h"

using namespace std;
typedef pair<int, int> pii;

template<typename S>
struct BakerBird {
	BakerBird(const vector<S> &p): X(p.size()), Y(p[0].size()), aho(p), kmp() {
		kmp.p.resize(X);
		for(int i = 0; i < X; ++i)
			kmp.p[i] = aho.states(p[i]).back();
		kmp.init();
	}

	vector<pii> matches(const vector<S> &a) {
		int N = a.size();
		if(N < X) return {};
		int M = a[0].size();
		if(M < Y) return {};
		vector<pii> ans;
		vector<vector<int>> states(N);
		for(int i = 0; i < N; ++i) states[i] = aho.states(a[i]);
		vector<int> col(N);
		for(int j = Y-1; j < M; ++j) {
			for(int i = 0; i < N; ++i) col[i] = states[i][j];
			for(int i : kmp.matches(col))
				ans.emplace_back(i, j-Y+1);
		}
		return ans;
	}

private:
	int X, Y;
	AhoCorasick<S> aho;
	KMP<vector<int>> kmp;
};
