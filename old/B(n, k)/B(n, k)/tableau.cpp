// tableau.cpp: implementation of the tableau class.
//
//////////////////////////////////////////////////////////////////////

#include "tableau.h"
#include "Perm.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tableau::tableau()
{

}

tableau::tableau(Partition lambda) {
	shape = lambda;
	for (int i = lambda.maxpart(); i != 0; --i) {
		for (int j = 1; j <= lambda.M(i); j++) {
			tabrows temp;
			for (int k = 1; k <= i; k++) {
			
				temp.push_back(0);
			}
			table.push_back(temp);
		}
	}
}




tableau::~tableau()
{

}

// this permutes the spots
tableau operator * (const Perm sigma, tableau T) {
	// we loop through all elements of T
	tableau Answer(T.shape);
	int count = 0;
	vector<int> word;
	for (int row = 1; row <= (T.shape).l(); row++) {
		for (int col = 1; col <= T.shape[row]; col++) {
			word.push_back( (T.table[row-1])[col-1] );
			count++;
		}
	}

	vector<int> newword;
	for (int i = 1; i <= count; i++) {
		newword.push_back(word[sigma[i]-1]);
	}

	count = 0;
	for (row = 1; row <= (T.shape).l(); row++) {
		for (int col = 1; col <= T.shape[row]; col++) {
			(Answer.table[row-1])[col-1] = newword[count];	
			count++;
		}
	}

	return(Answer);
}

tableau standard(Partition lambda, Partition mu) {
	tableau Answer(lambda);

	// first we make mu into a word
	vector<int> word;
	for (int row = 1; row <= mu.l(); row++) {
		int limit = mu[row];
		for (int col = 1; col <= limit; col++) {
			word.push_back(row);
		}
	}

	// now we move through lambda adding the next elt of word

	int count = 1;
	for (row = 1; row <= lambda.l(); row++) {
		vector<int> temp;
		for (int col = 1; col <= lambda[row]; col++) {
			temp.push_back(word[count-1]);
			count++;
		}
		(Answer.table)[row-1] = temp;
	}

	return(Answer);
}

tableau standard(Partition lambda, RankSet mu) {
	tableau Answer(lambda);

	// first we make mu into a word
	vector<int> word;
	int where = 0;
	where++;
	for (RankSet::const_iterator iter = mu.begin(); iter != mu.end(); ++iter ) {
		for(int count = 1; count <= *iter; count++) {
			word.push_back(where);
		}
		where++;
	}

	// now we move through lambda adding the next elt of word

	int count = 1;
	for (int row = 1; row <= lambda.l(); row++) {
		vector<int> temp;
		for (int col = 1; col <= lambda[row]; col++) {
			temp.push_back(word[count-1]);
			count++;
		}
		(Answer.table)[row-1] = temp;
	}

	return(Answer);
}
int tableau::Get(const int row, const int col) {
	tabrows temp = table[row-1];
	return(temp[col-1]);
}

void tableau::Set(const int row, const int col, const int value) {
	(table[row-1])[col-1] = value;
}

bool IsSSYT(tableau T) {
	// first we check rows
	bool flag = true;
	for (int row = 1; row <= (T.shape).l(); row++) {
		for (int col = 1; col < (T.shape)[row]; col++) {
			if (T.Get(row, col) > T.Get(row, col+1)) {
				flag = false;
			}
		}
	}

	// now check columns
	Partition conj = lprime(T.shape);
	for (row = 1; row <= conj.l(); row++) {
		for (int col = 1; col < conj[row]; col++) {
			if (T.Get(col, row) >= T.Get(col+1, row)) {
				flag = false;
			}
		}
	}

	return(flag);
}

bool IsSYT(tableau T) {
	// first we check rows
	bool flag = true;
	for (int row = 1; row <= (T.shape).l(); row++) {
		for (int col = 1; col < T.shape[row]; col++) {
			if (T.Get(row, col) >= T.Get(row, col+1)) {
				flag = false;
			}
		}
	}

	// now check columns
	Partition conj = lprime(T.shape);
	for (row = 1; row <= conj.l(); row++) {
		for (int col = 1; col < conj[row]; col++) {
			if (T.Get(col, row) >= T.Get(col+1, row)) {
				flag = false;
			}
		}
	}

	return(flag);
}

list<tableau> SSYT(Partition lambda, Partition mu) {
	list<tableau> Answer;

	// we first construct the standard SSYT of shape lambda type mu
	tableau std = standard(lambda, mu);

	// now we get all permutations of n
	list<Perm> Sn = Perms(lambda.Size());
	
	// and then we apply all of them
	for (list<Perm>::iterator iter = Sn.begin(); iter != Sn.end(); ++iter) {
		tableau temp = *iter * std;
		if (IsSSYT(temp)) {
			bool flag = true;
			for(list<tableau>::const_iterator iter2 = Answer.begin(); iter2 != Answer.end(); ++iter2) {
				if (*iter2 == temp) {
					flag = false;
				}
			}
			if(flag) {
				Answer.push_back(temp);
			}
		}
	}

	return(Answer);
}

list<tableau> SSYT(Partition lambda, RankSet mu) {
	list<tableau> Answer;

	// we first construct the standard SSYT of shape lambda type mu
	tableau std = standard(lambda, mu);


	// now we get all permutations of n
	list<Perm> Sn = Perms(lambda.Size());
	
	// and then we apply all of them
	for (list<Perm>::iterator iter = Sn.begin(); iter != Sn.end(); ++iter) {
		tableau temp = *iter * std;

		if (IsSSYT(temp)) {
			bool flag = true;
			for(list<tableau>::const_iterator iter2 = Answer.begin(); iter2 != Answer.end(); ++iter2) {
				if (*iter2 == temp) {
					flag = false;
				}
			}
			if(flag) {
				Answer.push_back(temp);
			}
		}
	}

	return(Answer);
}



tableau conjugate(tableau T) {
	tableau S(lprime(T.shape));

	for (int row = 1; row <= T.shape.l(); row++) {
		for (int col = 1; col <= T.shape[row]; col++) {
			S.Set(col, row, T.Get(row, col));
		}
	}
	return(S);
}

// this permuters the numbers
tableau Apply(const Perm sigma, tableau T) {
	// we loop through all elements of T
	tableau Answer(T.shape);
	
	for (int row = 1; row <= (T.shape).l(); row++) {
		for (int col = 1; col <= T.shape[row]; col++) {
			(Answer.table[row-1])[col-1] = sigma[(T.table[row-1])[col-1]];	
		}
	}

	return(Answer);
}

bool RowEqual(tableau t, const tableau s) {

	bool flag = true;
	for(int row = 1; row <= (t.shape).l(); row++) {
		set<int> A, B;
		for(int col = 1; col <= t.shape[row]; col++) {
			A.insert( (t.table[row-1])[col-1] );
			B.insert( (s.table[row-1])[col-1] );
		}
		if (A != B ) {
			flag = false;
		}
	}

	return(flag);
}

int maxentry(tableau T) {

	int Answer = 0;

	for (int row = 1; row <= (T.shape).l(); row++) {
		for (int col = 1; col <= (T.shape)[row]; col++) {
			if ((T.table[row-1])[col-1] > Answer) {
				Answer = (T.table[row-1])[col-1];
			}
		}
	}

	return(Answer);
}
			
// return the column group of T
list<Perm> C(tableau T) {
	// we test all permutations
	list<Perm> Sn = Perms(maxentry(T));
	list<Perm> Answer;

	tableau transform = conjugate(T);

	for (list<Perm>::const_iterator iter = Sn.begin(); iter != Sn.end(); iter++) {
		if(RowEqual(transform, Apply(*iter, transform))) {
			Answer.push_back(*iter);
		}
	}
	return(Answer);
}

			

// return the row group of T
list<Perm> R(tableau T) {
	// we test all permutations
	list<Perm> Sn = Perms(maxentry(T));
	list<Perm> Answer;

	for (list<Perm>::const_iterator iter = Sn.begin(); iter != Sn.end(); iter++) {
		if (RowEqual(T, Apply(*iter, T))) {
			Answer.push_back(*iter);
		}
	}
	return(Answer);
}


// return all tableau row equiv to T:
list<tableau> Braceof(const tableau T) {
	list<Perm> Rgroup = R(T);
	list<tableau> tablist;

	for(list<Perm>::const_iterator iter = Rgroup.begin(); iter != Rgroup.end(); ++iter) {
		tablist.push_back(Apply(*iter, T));
	}

	return(tablist);
}


tabloid TableauToTabloid(tableau T, const Partition lambda) {
	// NOTE: THIS IS NOT THE SAME AS CONVERTING
	// here we use that funny map
	// and end up with a tabloid of shape lambda
	// and type T.shape

	tabloid tab(lambda);


	// each number of a standard tab  goes to the row# T[spot of that number]
	// so for instance  1 3
	//					2
	// goes to 1 
	//		   3
	//         2

	int count = 1;
	for (int row = 1; row <= T.shape.l(); row++) {
		for (int col = 1; col <= (T.shape)[row]; col++) {
			tab.Add(T.Get(row, col), count);
			count++;
		}
	}

	return(tab);
}




	
