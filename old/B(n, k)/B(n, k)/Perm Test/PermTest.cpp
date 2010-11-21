#include "poset homology\Perm.h"
#include <iostream>
#include <stdio.h>

void main(void) {
	
	cout << "\nTesting constructor";

	Perm sigma;
	Perm tau(3);
	list<Perm> Sn;

	cout << "\nGetting list of all permutations of a 4 element set";
	Sn = Perms(3);
	char ch = getchar();
	Sn = Perms(4);
	

	cout << "\nThere were " << Sn.size() << " permutations";
	cout << "\n Here they are along with their signs";
	for (list<Perm>::iterator iter = Sn.begin(); iter != Sn.end(); ++iter) {
	 	cout << "\n" << *iter;
		cout << " has sign " << sign(*iter);
	}

	cout << "\nThere were " << Sn.size() << " permutations";



	// Also will test PermMake here
	list<int> A, B;

	A.push_back(1);
	A.push_back(3);
	A.push_back(2);
	B.push_back(2);
	B.push_back(3);
	B.push_back(1);

	Perm sigma2 = PermMake(A, B);
	cout << sigma2;
	int i;
	cin >> i;
	
}