#include <vector>

using namespace std;

template<typename T>
struct FlowEdge {
	int to, opp;
	T c, f;
	FlowEdge(int to, int opp, T c, T f=0): to(to), opp(opp), c(c), f(f) {}
};

template<typename T>
struct FlowAlgo {
	int N;
	vector<vector<FlowEdge<T>>> G;
	FlowAlgo(int N): N(N), G(N) {}
	void addEdge(int a, int b, T c) {
		G[a].emplace_back(b, G[b].size(), c);
		G[b].emplace_back(a, G[a].size()-1, 0);
	}
};

// O(E^2 log(C))
template<typename T>
struct FlowCapScaling : FlowAlgo<T> {
	using FlowAlgo<T>::G;
	FlowCapScaling(int N): FlowAlgo<T>(N) {}

	T maxFlow(int s, int t) {
		C = 0;
		for(const auto &g : G)
			for(const auto &e : g)
				C = max(C, e.c);
		seen.assign(FlowAlgo<T>::N, 0);
		step = 1;
		_t = t;
		
		T ans = 0;
		while(C > 0) {
			++ step;
			if(dfs(s)) ans += C;
			else C /= 2;
		}
		return ans;
	}

private:
	vector<int> seen;
	int step, _t;
	T C;

	bool dfs(int i) {
		if(i == _t) return true;
		seen[i] = step;
		for(auto &e : G[i])
			if(seen[e.to] < step && e.f + C <= e.c && dfs(e.to)) {
				e.f += C;
				G[e.to][e.opp].f -= C;
				return true;
			}
		return false;
	}
};
