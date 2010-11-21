#include "Partition.h"
#include "poset homology\tableau.h"
#include <iostream>
#include "poset homology\Perm.h"
#include <stdio.h>

void main(void) {


	cout << "\nTesting constructors";
	Partition lambda, mu;
	lambda.Add(3);
	lambda.Add(2);
	lambda.Add(1);
	lambda.Add(3);
	lambda.Add(1);
	mu.Add(3);
	mu.Add(2);
	mu.Add(2);
	mu.Add(2);
	mu.Add(1);

	Perm sigma(6);
	sigma[1]=6;
	sigma[2]=3;
	sigma[3]=1;
	sigma[4]=2;
	sigma[5]=5;
	sigma[6]=4;
	
	tableau T, U;
	tableau S(lambda);

	T = standard(lambda, mu);

	cout << "\nThe standard tableau of shape ";
	cout << lambda;
	cout << " \n and type ";
	cout << mu;
	cout << T;
	cout << "\nThe element in row 2 col 3 is ";
	cout << T.Get(2, 3);
	cout << "\nWe will set this element to 8";
	T.Set(2, 3, 8);
	cout << T;
	cout << "\nTesting if this is a SSYT ";
	cout << IsSSYT(T);
	cout << "\nTesting if ";
	cout << T;
	cout << "is: ";
	cout << IsSSYT(T);
	cout << "\nTesting if it is SYT ";
	cout << IsSYT(T);
	cout << "\nTesting if ";
	tableau std;
	Partition gamma;
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	gamma.Add(1);
	std = standard(lambda, gamma);
	cout << std;
	cout << "is: " << IsSYT(std);

	Partition A, B;
	A.Add(1);
	A.Add(2);
	A.Add(3);
	B.Add(2);
	B.Add(2);
	B.Add(2);
	cout << "\n\nConstruction all SSYT of shape ";
	cout << A;
	cout << "\nand type ";
	cout << B;
	list<tableau> SSYTlist = SSYT(A, B);
	tableau tabby;
	for(list<tableau>::iterator iter = SSYTlist.begin(); iter != SSYTlist.end(); ++iter) {
		tabby = conjugate(*iter);
		cout << *iter;
		cout << tabby;
		tabby = *iter;
	}

	list<Perm> Clist, Rlist;
	Clist = C(tabby);
	Rlist = R(tabby);
	cout << "\nColumn group";
	for (list<Perm>::iterator iter2 = Clist.begin(); iter2 != Clist.end(); ++iter2) {
		cout << *iter2;
	}
	cout << "\nRow group";
	for (iter2 = Rlist.begin(); iter2 != Rlist.end(); ++iter2) {
		cout << *iter2;
	}

	cout << "\nMapping to a tabloid";
	//tabloid tab1 = TableauToTabloid(tabby, lambda);
	tabloid tab2 = TableauToTabloid(tabby, mu);
	//tabloid tab3 = TableauToTabloid(tabby, gamma);
	Partition delta;
	delta.Add(2);
	delta.Add(2);
	delta.Add(1);
	delta.Add(1);
	//tabloid tab4 = TableauToTabloid(tabby, delta);
	//cout << tab1;
	cout << tab2;
	//cout << tab3;
	//cout << tab4;




	char ch = getchar();
}
