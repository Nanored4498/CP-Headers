#include <algorithm>
#include <vector>

using namespace std;

// Return a clockwise convex hull
template<typename pt>
vector<pt> convex_hull(vector<pt>& pts, bool include_collinear=false) {
	if(pts.size() < 3) return pts;
    pt p0 = *min_element(pts.begin(), pts.end(), [](const pt &a, const pt &b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(pts.begin(), pts.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if(o == 0) return norm2(a-p0) < norm2(b-p0);
        return o < 0;
    });
    if(include_collinear) {
        auto it = pts.end()-1;
        while(it >= pts.begin() && orientation(p0, *it, pts.back()) == 0) --it;
        reverse(++it, pts.end());
    }
    vector<pt> st;
    for(const pt &a : pts) {
        while(st.size() > 1 && orientation(st[st.size()-2], st.back(), a) >= (include_collinear ? 1 : 0))
            st.pop_back();
        st.push_back(a);
    }
    return st;
}