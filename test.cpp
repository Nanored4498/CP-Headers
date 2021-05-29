#include <iostream>

#include "sat2.h"
#include "flow.h"

using namespace std;

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

	return 0;
}