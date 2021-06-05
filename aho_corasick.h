#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

template<typename S>
struct AhoCorasick {
	typedef typename S::value_type T;
	vector<vector<int>> ends;

	AhoCorasick(const vector<S> &ps, bool everyEnds = false): ends(1), _next(1), _back(1, -1) {
		for(int i = 0; i < ps.size(); ++i) {
			int n = 0;
			for(T x : ps[i]) {
				if(!_next[n].count(x)) {
					_next[n][x] = _next.size();
					ends.emplace_back();
					_next.emplace_back();
					_back.push_back(-1);
				}
				n = _next[n][x];
			}
			ends[n].push_back(i);
		}
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()) {
			int n = Q.front();
			Q.pop();
			if(everyEnds && _back[n] != -1)
				ends[n].insert(ends[n].end(), ends[_back[n]].begin(), ends[_back[n]].end());
			for(const auto [x, nn] : _next[n]) {
				_back[nn] = next(_back[n], x);
				Q.push(nn);
			}
		}
	}

	int next(int n, T x) {
		while(n != -1 && !_next[n].count(x)) n = _back[n];
		return n == -1 ? 0 : _next[n][x];
	}

	vector<int> states(const S &a) {
		int n = 0;
		vector<int> ans(a.size());
		for(int i = 0; i < a.size(); ++i)
			ans[i] = n = next(n, a[i]);
		return ans;
	}

private:
	vector<unordered_map<T, int>> _next;
	vector<int> _back;
};
