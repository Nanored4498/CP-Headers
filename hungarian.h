#include <vector>
#include <limits>

using namespace std;

template<typename Scal>
struct Hungarian {
	int N, M;
	vector<int> xy, yx;
	vector<vector<Scal>> w;

	Hungarian(int N, int M):
		N(N), M(M),
		xy(N, -1), lx(N, numeric_limits<Scal>::max()),
		yx(M, -1), ly(M, 0),
		slack(M), slackx(M),
		w(N, vector<int>(M)) { }

	void solve() {
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < M; ++j)
				lx[i] = min(lx[i], w[i][j]);
		for(int i = 0; i < N; ++i) augment();
	}
	
private:
	vector<bool> S, T;
	vector<int> slackx;
	vector<Scal> lx, ly, slack;

	bool add(int j) {
		T[j] = true;
		int i = yx[j];
		if(i == -1) {
			while(j >= 0) swap(j, xy[yx[j] = slackx[j]]);
			return true;
		}
		if(S[i]) return false;
		S[i] = true;
		for(int j2 = 0; j2 < M; ++j2) if(!T[j2]) {
			Scal new_slack = w[i][j2] - lx[i] - ly[j2];
			if(new_slack < slack[j2]) {
				slack[j2] = new_slack;
				slackx[j2] = i;
				if(new_slack == 0 && add(j2)) return true;
			}
		}
		return false;
	}

	void augment() {
		S.assign(N, false);
		T.assign(M, false);
		int i = 0;
		while(xy[i] != -1) ++i;
		S[i] = true;
		for(int j = 0; j < M; ++j) {
			slackx[j] = i;
			slack[j] = w[i][j] - lx[i] - ly[j];
		}
		while(true) {
			for(int j = 0; j < M; ++j)
				if(!T[j] && slack[j] == 0 && add(j))
					return;
			Scal delta = numeric_limits<Scal>::max();
			for(int j = 0; j < M; ++j) if(!T[j]) delta = min(delta, slack[j]);
			for(int i = 0; i < N; ++i) if(S[i]) lx[i] += delta;
			for(int j = 0; j < M; ++j)
				if(T[j]) ly[j] -= delta;
				else slack[j] -= delta;
		}
	}

};
