#include <iostream>

#include "sat2.h"

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

	return 0;
}