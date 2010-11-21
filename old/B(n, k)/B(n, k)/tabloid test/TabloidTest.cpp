#include <iostream>
#include "poset homology\tabloid.h"
#include "Partition.h"
#include "poset homology\Perm.h"
void main(void) {
	cout << "\nTesting blank constructor";
	tabloid t;

	cout << "\nTesting constructor of a tabloid of shape 311";
	Partition lambda;
	lambda.Add(3);
	lambda.Add(2);
	lambda.Add(1);
	tabloid s(lambda);
	
	cout << "\nGetting the standard tabloid of shape 311";
	s = standardoid(lambda);

	cout << "\nTesting output";
	cout << s;

	cout << "\nTesting Sn action";
	Perm sigma(6);
	sigma[1]=6;
	sigma[2]=3;
	sigma[3]=1;
	sigma[4]=2;
	sigma[5]=5;
	sigma[6]=4;
		cout << "\nApplying ";
	    cout << sigma;
		cout << sigma * s;

	
	cout << "\nNote that ";
	cout << s;
	cout << " has " << s.RowNumber() << " of rows";

	cout << " and the second row is \n";
	rows temp = s.Row(2);
	for (rows::const_iterator iter2 = temp.begin(); iter2 != temp.end(); ++iter2) {
		cout << " " << *iter2;
	}


// reorder the rows of a tabloid Note it no longer have the shape of a paritition

	Perm tau(3);
	tau[1]=2;
	tau[2]=3;
	tau[3]=1;
	
	cout << "\nReordering rows of ";
	cout << s;
	cout << " with ";
	cout << tau;
	tabloid q = reorderrows(tau, s);
	cout << q;

//	void insert(const vector<int> row);
	cout << "\nNow we insert a row of 7, 8, 9";
	vector<int> rowtemp;
	rowtemp.push_back(7);
	rowtemp.push_back(8);
	rowtemp.push_back(9);
	q.insert(rowtemp);
	cout << q;

//	void Add(const int row, const int value);
	cout << "\nNow we add a 10 to row 2";
	q.Add(2,10);
	cout << q;
	int crap;
	cin >> crap;
}