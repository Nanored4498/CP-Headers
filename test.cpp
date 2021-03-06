#include <iostream>
#include <cmath>

#include "sat2.h"
#include "flow.h"
#include "pattern_2d.h"
#include "chinese.h"
#include "prime.h"

using namespace std;
typedef long long ll;

double inv(double x) { return 1./x; }
#include "arith_utils.h"

int main() {
	SAT2 sat(4);
	sat.addClause(3, 0);
	sat.addClause(0, 2);
	sat.addClause(1, 5);
	sat.addClause(2, 4);
	sat.addClause(1, 7);
	if(sat.solve()) {
		for(bool b : sat.values) cout << b << ' ';
		cout << endl;
	} else cout << "IMPOSSIBLE" << endl;

	sat = SAT2(3);
	sat.addClause(1, 3);
	sat.addClause(1, 2);
	sat.addClause(0, 5);
	sat.addClause(0, 4);
	if(sat.solve()) {
		for(bool b : sat.values) cout << b << ' ';
		cout << endl;
	} else cout << "IMPOSSIBLE" << endl;

	FlowCapScaling<int> maxFlow(6);
	maxFlow.addEdge(0, 1, 5);
	maxFlow.addEdge(0, 3, 4);
	maxFlow.addEdge(1, 2, 6);
	maxFlow.addEdge(2, 4, 8);
	maxFlow.addEdge(2, 5, 5);
	maxFlow.addEdge(3, 1, 3);
	maxFlow.addEdge(3, 4, 1);
	maxFlow.addEdge(4, 5, 2);
	cout << maxFlow.maxFlow(0, 5) << endl;

	KMP<string> kmp("AABA");
	for(int i : kmp.matches("AABAACAADAABAABA")) cout << i << ' ';
	cout << endl;

	vector<string> aho_pattern;
	aho_pattern.push_back("he");
	aho_pattern.push_back("she");
	aho_pattern.push_back("hers");
	aho_pattern.push_back("his");
	AhoCorasick aho(aho_pattern, true);
	vector<int> states = aho.states("ahishers");
	for(int i = 0; i < states.size(); ++i)
		for(int j : aho.ends[states[i]])
			cout << i-aho_pattern[j].size()+1 << ' ' << i << ' ' << aho_pattern[j] << endl;
	
	vector<string> pattern2D;
	pattern2D.push_back("aabba");
	pattern2D.push_back("aaabb");
	pattern2D.push_back("ababa");
	pattern2D.push_back("aabba");
	pattern2D.push_back("aaabb");
	vector<string> search2D;
	search2D.push_back("aabbaaabba");
	search2D.push_back("aaabbaaabb");
	search2D.push_back("ababaababa");
	search2D.push_back("aabbaaabba");
	search2D.push_back("aaabbaaabb");
	search2D.push_back("baaabbabab");
	search2D.push_back("aababaabba");
	search2D.push_back("aaabbaaabb");
	search2D.push_back("baaabbaaab");
	BakerBird bb(pattern2D);
	for(auto [i, j] : bb.matches(search2D)) cout << i << ',' << j << ' ';
	cout << endl;

	{
	vector<int> a = {3, 4, 2}, m = {5, 7, 3};
	cout << chineseRM(a, m) << ' ';
	a[1] = 18, a[2] = 5;
	m[0] = 10; m[1] = 35; m[2] = 6;
	cout << chineseRM(a, m) << ' ';
	a[1] = 21;
	cout << chineseRM(a, m) << endl;
	}

	{
	vector<pair<ll, bool>> ps {{299210837LL, true}, {193LL*407521LL, false}, {1795265047LL, true}, {9780517LL*45077531LL, false}};
	for(const auto &[x, a] : ps) if(isPrime(x) != a) cout << "Prime Error " << x << ' ' << a << ' ' << isPrime(x) << endl;
	}

	{
	AU<double> utils;
	double n = 15, p = 5;
	double snp = 0;
	for(double i = 1; i <= n; ++i) snp += pow(i, p) + pow(i, p+1);
	cout << utils.sumPow(n, p) + utils.sumPow(n, p+1) - snp << endl;
	}

	return 0;
}