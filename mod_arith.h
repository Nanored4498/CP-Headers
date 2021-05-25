#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

template <int MOD>
struct mint {
	static const int mod = MOD;
	int x;
	mint(): x(0) {}
	mint(ll v) {
		x = v % MOD;
		if(x < 0) x += MOD;
	}

	friend mint pow(mint a, ll p) {
		mint ans = 1;
		for(; p; p >>= 1, a *= a) if(p&1) ans *= a;
		return ans;
	}
	friend mint inv(mint a) { return pow(a, mod-2); }

	explicit operator int() const { return x; }
	friend bool operator==(const mint &a, const mint &b) { return a.x == b.x; }
	friend bool operator!=(const mint &a, const mint &b) { return a.x != b.x; }
	friend ostream& operator<<(ostream &stream, const mint &v) { return stream << v.x; }
	friend istream& operator>>(istream &stream, mint &v) { return stream >> v.x; }
	mint& operator+=(const mint &b) { if((x += b.x) >= mod) x -= mod; return *this; }
	mint& operator-=(const mint &b) { if((x -= b.x) < 0) x += mod; return *this; }
	mint& operator*=(const mint &b) { x = (1LL * x * b.x) % mod; return *this; }
	mint& operator/=(const mint &b) { return (*this) *= inv(b); }
	mint& operator++() { return (*this) += 1; }
	mint& operator--() { return (*this) -= 1; }
	mint operator-() { return -x; }
	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }

	// use as follow after defining mi as mint<MOD>
	// template<> mi mi::g = mi::computeG();
	// usefull for NTT
	static mint g;
	static mint computeG() {
		vector<int> ps;
		int m2 = mod-1;
		for(int p = 2; p <= m2; ++p) if(m2 % p == 0) {
			ps.push_back(p);
			while(m2 % p == 0) m2 /= p;
		}
		mint G = 2;
		m2 = mod-1;
		while(true) {
			bool good = true;
			for(int p : ps) if(pow(G, m2/p) == 1) {
				good = false;
				break;
			}
			if(good) return G;
			else ++G;
		}
	}
};
