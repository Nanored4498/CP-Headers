#include <algorithm>
#include <vector>

using namespace std;

template<typename pt>
vector<pt> convex_hull(vector<pt>& pts, bool include_collinear=false) {
	if(pts.size() < 3) return pts;
    pt p0 = *min_element(pts.begin(), pts.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(pts.begin(), pts.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if(o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if(include_collinear) {
        auto it = pts.end()-1;
        while(it >= pts.begin() && orientation(p0, *it, pts.back()) == 0) --it;
        reverse(++it, pts.end());
    }
    vector<pt> st;
    for(pt &a : pts) {
        while(st.size() > 1 && orientation(st[st.size()-2], st.back(), a) >= (include_collinear ? 1 : 0))
            st.pop_back();
        st.push_back(a);
    }
    return st;
}