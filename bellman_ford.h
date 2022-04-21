#include <vector>
#include <limits>

// Distances from i with negative weights in O(nm)
// Return empty vector if negative loop
template<typename L>
std::vector<L> BellmanFord(const std::vector<std::vector<std::pair<int, L>>> &G, int i) {
	std::vector<L> d(G.size(), std::numeric_limits<L>::max());
	d[i] = 0;
	for(int step = 0; step < (int) G.size(); ++step) {
		bool better = false;
		for(int j = 0; j < (int) G.size(); ++j) if(d[j] != std::numeric_limits<L>::max())
			for(const auto [k, l] : G[j]) {
				const L d2 = d[j] + l;
				if(d2 < d[k]) {
					better = true;
					d[k] = d2;
				}
			}
		if(!better) return d;
	}
	return std::vector<L>();
}