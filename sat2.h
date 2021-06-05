#include "scc.h"

// 2*i --> not x_i  ||  2*i+1 --> x_i
struct SAT2 {
	int n;
	vector<vector<int>> G;
	vector<bool> values;

	SAT2(int n): n(n), G(2*n) {}

	void addClause(int a, int b) {
		G[a^1].push_back(b);
		G[b^1].push_back(a);
	}

	bool solve() {
		SCC scc(G);
		scc.compute();
		for(int i = 0; i < n; ++i) if(scc.c[2*i] == scc.c[2*i+1]) return false;
		values.resize(n);
		vector<bool> seen(n, false);
		for(const vector<int> c : scc.cs) if(!seen[c[0]/2]) {
			for(int i : c) {
				seen[i/2] = true;
				values[i/2] = i&1;
			}
		}
		return true;
	}
};
