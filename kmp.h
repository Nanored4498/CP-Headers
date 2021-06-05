#include <vector>

using namespace std;

template<typename S>
struct KMP {
	S p;
	vector<int> d;

	KMP() = default;
	KMP(const S &p): p(p) { init(); }
	
	void init() {
		d.assign(p.size()+1, -1);
		for(int i = 1; i <= p.size(); ++i) {
			d[i] = d[i-1];
			while(d[i] != -1 && p[d[i]] != p[i-1])
				d[i] = d[d[i]];
			++ d[i];
		}
	}

	vector<int> matches(const S &a) {
		vector<int> ans;
		for(int i = 0, q = 0; i < a.size(); ++i) {
			while(q != -1 && p[q] != a[i])
				q = d[q];
			++ q;
			if(q == p.size()) {
				ans.push_back(i - q + 1);
				q = d[q];
			}
		}
		return ans;
	}
};
