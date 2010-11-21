#include "RankSet.h"
#include <iostream>
#include <stdio.h>

void main(void) {


	cout <<"\nWe first test composition";
	list< RankSet > comp = composition(4);
	for(list< RankSet >::const_iterator iter = comp.begin(); iter != comp.end(); ++iter) {
		cout <<"\n";
		for(RankSet::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); ++iter2) {
			cout << *iter2;
		}
	}

	RankSet example;
	cout << "\nNow we test ComputeRanks";
	list<RankSet> Ranks = ComputeRanks(6,2,2);
	for(list< RankSet >::const_iterator iter3 = Ranks.begin(); iter3 != Ranks.end(); ++iter3) {
		cout <<"\n";
		for(RankSet::const_iterator iter4 = (*iter3).begin(); iter4 != (*iter3).end(); ++iter4) {
			cout << *iter4;
		}
	}

	example.push_back(1);
	example.push_back(2);
	example.push_back(1);

	cout << "\nThis last has shape";
	cout << example.Shape();

	cout << "\nWe now compute the tabloids of this shape";
	list<tabloid> listab = example.ComputeTabloids();

	for (list<tabloid>::iterator iter5 = listab.begin(); iter5 != listab.end(); ++iter5) {
		cout << *iter5;
		cout << ConvertFromTabloid(*iter5);
	}

	char ch = getchar();
}
