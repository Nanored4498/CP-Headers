#include <iostream>
#include <vector>

using namespace std;

template <int MOD>
struct mint {
	typedef long long ll;
	static const int mod = MOD;
	int x;
	constexpr mint(): x(0) {}
	constexpr mint(ll v) {
		x = v % mod;
		if(x < 0) x += mod;
	}

	friend constexpr mint pow(mint a, ll p) {
		mint ans = 1;
		for(; p; p >>= 1, a *= a) if(p&1) ans *= a;
		return ans;
	}
	friend constexpr mint inv(mint a) { return pow(a, mod-2); }

	explicit constexpr operator int() const { return x; }
	friend constexpr bool operator==(const mint &a, const mint &b) { return a.x == b.x; }
	friend constexpr bool operator!=(const mint &a, const mint &b) { return a.x != b.x; }
	friend constexpr bool operator<=(const mint &a, const mint &b) { return a.x <= b.x; }
	friend constexpr bool operator<(const mint &a, const mint &b) { return a.x < b.x; }
	friend ostream& operator<<(ostream &stream, const mint &v) { return stream << v.x; }
	friend istream& operator>>(istream &stream, mint &v) { return stream >> v.x; }
	mint& constexpr operator+=(const mint &b) { if((x += b.x) >= mod) x -= mod; return *this; }
	mint& constexpr operator-=(const mint &b) { if((x -= b.x) < 0) x += mod; return *this; }
	mint& constexpr operator*=(const mint &b) { x = (1LL * x * b.x) % mod; return *this; }
	mint& constexpr operator/=(const mint &b) { return (*this) *= inv(b); }
	mint& constexpr operator%=(const mint &b) { x %= b.x; return *this; }
	mint& constexpr operator++() { return (*this) += 1; }
	mint& constexpr operator--() { return (*this) -= 1; }
	mint constexpr operator-() { return -x; }
	friend constexpr mint operator+(mint a, const mint &b) { return a += b; }
	friend constexpr mint operator-(mint a, const mint &b) { return a -= b; }
	friend constexpr mint operator*(mint a, const mint &b) { return a *= b; }
	friend constexpr mint operator/(mint a, const mint &b) { return a /= b; }
};
