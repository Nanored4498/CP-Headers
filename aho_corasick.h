#include <vector>
#include <unordered_map>
#include <queue>

template<typename S>
struct AhoCorasick {
	typedef typename S::value_type T;
	std::vector<std::vector<int>> ends;
	std::vector<int> back;

	AhoCorasick() = default;
	AhoCorasick(const std::vector<S> &ps, bool everyEnds = false): ends(1), _next(1) {
		for(int i = 0; i < ps.size(); ++i) {
			int n = 0;
			for(T x : ps[i]) {
				if(!_next[n].count(x)) {
					_next[n][x] = _next.size();
					ends.emplace_back();
					_next.emplace_back();
				}
				n = _next[n][x];
			}
			ends[n].push_back(i);
		}
		back.assign(_next.size(), -1);
		for(std::queue<int> Q({0}); !Q.empty(); Q.pop()) {
			int n = Q.front();
			if(everyEnds && back[n] != -1)
				ends[n].insert(ends[n].end(), ends[back[n]].begin(), ends[back[n]].end());
			for(const auto [x, nn] : _next[n]) {
				back[nn] = next(back[n], x);
				Q.push(nn);
			}
		}
	}

	int next(int n, T x) {
		while(n != -1 && !_next[n].count(x)) n = back[n];
		return n == -1 ? 0 : _next[n][x];
	}

	std::vector<int> states(const S &a) {
		int n = 0;
		std::vector<int> ans(a.size());
		for(int i = 0; i < a.size(); ++i)
			ans[i] = n = next(n, a[i]);
		return ans;
	}

private:
	std::vector<std::unordered_map<T, int>> _next;
};
