#include <vector>

using namespace std;

struct SCC {
	const vector<vector<int>> &G;
	vector<int> id, stack;
	int next_id;
	vector<vector<int>> cs;

	SCC(const vector<vector<int>> &G): G(G) {}

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
			for(int j : cs.back()) id[j] = -2;
		}
		return min_id;
	}

	void compute() {
		id.assign(G.size(), -1);
		next_id = 0;
		cs.clear();
		for(int i = 0; i < (int) G.size(); ++i) if(id[i] == -1) dfs(i);
	}
};