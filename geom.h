template<typename T>
struct Point {
	T x, y;
	Point()=default;
	Point(T x, T y): x(x), y(y) {}

	Point operator+(const Point &p) { return {x+p.x, y+p.y}; }
	Point operator-(const Point &p) { return {x-p.x, y-p.y}; }
	Point operator*(T a) { return {x*a, y*a}; }
	Point operator/(T a) { return {x/a, y/a}; }
	Point& operator*=(T a) { x *= a; y *= a; return *this; }
	Point& operator/=(T a) { x /= a; y /= a; return *this; }
	friend Point operator*(T a, const Point &p) { return {a*p.x, a*p.y}; }
	friend istream& operator>>(istream &in, Point &p) { return in >> p.x >> p.y; }

	friend Point turn90(const Point &p) { return {-p.y, p.x}; }
	friend T dot(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
};