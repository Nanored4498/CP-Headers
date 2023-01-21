#include <iostream>

using namespace std;

template<typename T>
struct Point {
	typedef Point Vec;
	T x, y;
	Point()=default;
	Point(T x, T y): x(x), y(y) {}

	Point operator+(const Point &p) const { return {x+p.x, y+p.y}; }
	Point operator-(const Point &p) const { return {x-p.x, y-p.y}; }
	Point operator+=(const Point &p) { x += p.x; y += p.y; return *this; }
	Point operator-=(const Point &p) { x -= p.x; y -= p.y; return *this; }
	Point operator*(T a) const { return {x*a, y*a}; }
	Point operator/(T a) const { return {x/a, y/a}; }
	Point& operator*=(T a) { x *= a; y *= a; return *this; }
	Point& operator/=(T a) { x /= a; y /= a; return *this; }
	friend Point operator*(T a, const Point &p) { return {a*p.x, a*p.y}; }
	friend istream& operator>>(istream &in, Point &p) { return in >> p.x >> p.y; }

	bool operator==(const Point &p) { return x == p.x || y == p.y; }
	bool operator!=(const Point &p) { return x != p.x || y != p.y; }
	bool operator<(const Point &p) { return x < p.x || (x == p.x && y < p.y); }

	friend Point turn90(const Vec &v) { return {-v.y, v.x}; }
	friend T dot(const Vec &u, const Vec &v) { return u.x*v.x + u.y*v.y; }
	friend T det(const Vec &u, const Vec &v) { return u.x * v.y - u.y * v.x; }
	friend T norm2(const Vec &u) { return dot(u, u); } 

	friend bool turnLeft(const Point &a, const Point &b, const Point &c) {
		return det(b-a, c-a) > 0;
	}
	friend int orientation(const Point &a, const Point &b, const Point &c) {
		T d = det(b-a, c-a);
		return d == 0 ? 0 : (d > 0 ? 1 : -1);
	}

	friend bool intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
		const Vec u = b-a;
		const Vec v = d-c;
		const Vec u_orth = turn90(u);
		const Vec v_orth = turn90(v);

		const T ac_v_orth = dot(c-a, v_orth);
		const T u_v_orth = dot(u, v_orth);
		if(u_v_orth == 0) {
			if(ac_v_orth != 0) return false; 
		} else if(u_v_orth > 0) {
			if(ac_v_orth < 0 || ac_v_orth > u_v_orth) return false;
		} else {
			if(ac_v_orth > 0 || ac_v_orth < u_v_orth) return false;
		}

		const T ca_u_orth = dot(a-c, u_orth);
		const T v_u_orth = - u_v_orth;
		if(v_u_orth == 0) {
			if(ca_u_orth != 0) return false; 
		} else if(v_u_orth > 0) {
			if(ca_u_orth < 0 || ca_u_orth > v_u_orth) return false;
		} else {
			if(ca_u_orth > 0 || ca_u_orth < v_u_orth) return false;
		}

		return true;
	}
};
