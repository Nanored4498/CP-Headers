#include <vector>
#include <algorithm>

using namespace std;

// Components are given in reverse topological order
struct SCC {
	const vector<vector<int>> &G;
	vector<vector<int>> cs;
	vector<int> c;
	vector<vector<int>> DAG;

	SCC(const vector<vector<int>> &G): G(G) {}

	void compute() {
		id.assign(G.size(), -1);
		c.resize(G.size());
		cs.clear();
		next_id = 0;
		for(int i = 0; i < (int) G.size(); ++i) if(id[i] == -1) dfs(i);
	}

	void computeDAG() {
		DAG.assign(cs.size(), vector<int>());
		for(int i = 0; i < (int) G.size(); ++i)
			for(int j : G[i]) if(c[j] != c[i])
				DAG[c[i]].push_back(c[j]);
		for(vector<int> &g : DAG) {
			sort(g.begin(), g.end());
			g.resize(unique(g.begin(), g.end()) - g.begin());
		}
	}

private:
	vector<int> id, stack;
	int next_id;

	int dfs(int i) {
		int min_id = id[i] = next_id++;
		int start = stack.size();
		stack.push_back(i);
		for(int j : G[i]) if(id[j] != -2) {
			if(id[j] == -1) min_id = min(min_id, dfs(j));
			else if(id[j] != -2 && id[j] < min_id) min_id = id[j];
		}
		if(id[i] == min_id) {
			cs.emplace_back(stack.begin()+start, stack.end());
			stack.resize(start);
			for(int j : cs.back()) {
				c[j] = cs.size()-1;
				id[j] = -2;
			}
		}
		return min_id;
	}
};
