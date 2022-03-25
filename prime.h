template<typename T>
bool isPrime(T x) {
	typedef __uint128_t u128;
	if(x < 2) return false;
	int s = 0;
	T d = x-1;
	for(; !(d&1); d >>= 1) ++s;
	for(T a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
		if(x == a) return true;
		T b = 1;
		for(T e = d; e; e >>= 1, a = (u128)a*a % x)
			if(e&1) b = (u128)b*a % x;
		if(b == 1) continue;
		bool composite = true;
		for(int r = 0; r < s; ++r, b = (u128)b*b % x)
			if(b == x-1) {
				composite = false;
				break;
			}
    	if(composite) return false;
	}
	return true;
}