// Perm.cpp: implementation of the Perm class.
//
//////////////////////////////////////////////////////////////////////

#include "Perm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Perm::Perm()
{

}

Perm::Perm(const int n)
{
	// insert an extra 0  b/c indexing begins at 0!
	for (int i = 1; i <= n+1; i++) {
		push_back(0);
	}


}

Perm::~Perm()
{

}

// we need to get around C++ bad modulus command

int Mod(const int x, const int y) {
	if ( x >= 0) {
		return(x % y);
	}
	else {
		return(y + (x % y));
	}
}

Perm NextPerm(const Perm Old, int &m) {
	// This uses Wilf and Nijenhuis' algorithm
	// from "Combinatorial Algorithms"
	// page 55

    int n, h, m1, B, j, m2, j1;
	n = Old.size()-1;
	Perm Newperm(n);

	if (m == 6 && n == 3) {
		Newperm[1] = 1;
		Newperm[2] = 3;
		Newperm[3] = 2;
		m++;
		return(Newperm);
	}

    Newperm = Old;
    if (Mod(m, 2) == 1) {
     
      Newperm[1] = Newperm[2];
      Newperm[2] = Old[1];
      m++;
	}
	else {
	    h=3;
	    m1 = m/2;
		do {
			B = Mod(m1, h);
			if (B == 0) {
				m1 = m1/h;
				h++;
				}
			} while (B == 0);
		
      
      m1 = n;
      j=0;
      do {
		j++;
        m2 = Mod((Old[j] - Old[h]), n);
        if (m2 < m1) {
          m1 = m2;
          j1 =j;
        }
		if (j ==h-1) {
			break;
		}
		
      } while (j != h-1);

      Newperm[j1] = Old[h];
      Newperm[h] = Old[j1];
     
      m++;
    }
    return(Newperm);
}

int fact(const int n) {
	if (n == 1) {
		return(1);
	}
	else {
		return(n * fact(n-1));
	}
}

list<Perm> Perms(const int n) {
	list<Perm> Answer;

	// we start with the trivial permutation
	// insert an extra 0  b/c indexing begins at 0!
	Perm initial;
	initial.push_back(0);
	for (int i = 1; i <= n; i++) {
		initial.push_back(i);
	}


	int m = 1;
	// now we keep getting the next permutation
	// until we get initial back
	
	Answer.push_back(initial);
	for (Perm Next = NextPerm(initial, m); m != fact(n)+1; Next = NextPerm(Next, m)) {
		Answer.push_back(Next);
	}

	return(Answer);
}

// return the sign of a permutation
int sign(const Perm sigma) {
	// This uses Wilf and Nijenhuis' algorithm
	// from "Combinatorial Algorithms"
	// page 222

	int Answer;
	int cycles=0; // the number of cycles of the input permutation;
	int N = sigma.size()-1;
	int M;
	Perm temp = sigma;

	for (int I = 1; I <= N; I++) {
		temp[I] = -temp[I];
	}
	
	for (int i = 1; i <= N; i++) {
		if (temp[i]  < 0 ) {
			cycles++;
			M = i;
			do {
				temp[M] = - temp[M];
				M = temp[M];
			} while (M != i);
		}
	}
	Answer = 1 - 2 *(Mod(N+cycles, 2));
	return(Answer);
}


// return the permutation sending A to B
Perm PermMake(const list<int> A, const list<int> B) {
	Perm Answer(A.size());

	int domain = 1;
	for (list<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter) {
		int range = 1;
		for (list<int>::const_iterator iter2 = B.begin(); iter2 != B.end(); ++iter2) {
			if (*iter == *iter2) {
				Answer[domain] = range;
			}
			range++;
		}
		domain++;
	}

	return(Answer);
}
