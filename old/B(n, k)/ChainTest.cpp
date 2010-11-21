#include "Poset Homology\chain.h"

void main(void) {

	set<int> A, B, C, D, E, F, G, H;
	B.insert(1);
	C.insert(2);
	D.insert(3);
	E.insert(1);
	E.insert(2);
	F.insert(2);
	F.insert(3);
	G.insert(1);
	G.insert(3);
	H.insert(1);
	H.insert(2);
	H.insert(3);

	chain empty, full, single, junk;

	full.insert(A);
	full.insert(B);
	full.insert(E);
	full.insert(H);
	single.insert(A);
	single.insert(B);
	single.insert(H);

	cout << "\n" << empty << "\n";
	cout << "\n" << full << "\n";
	cout << "\n" << single << "\n";
	cout << "\n" << IsChain(empty, 1) << "\n";
	cout << "\n" << IsChain(empty, 2) << "\n";
	cout << "\n" << IsChain(empty, 3) << "\n";
	cout << "\n" << IsChain(full, 1) << "\n";
	cout << "\n" << IsChain(full, 2) << "\n";
	cout << "\n" << IsChain(full, 3) << "\n";
	cout << "\n" << IsChain(single, 1) << "\n";
	cout << "\n" << IsChain(single, 2) << "\n";
	cout << "\n" << IsChain(single, 3) << "\n";

	int i;
	cin >> i; 

		
}