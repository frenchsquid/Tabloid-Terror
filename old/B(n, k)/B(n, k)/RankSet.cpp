// RankSet.cpp: implementation of the RankSet class.
//
//////////////////////////////////////////////////////////////////////

#include <set>
#include "RankSet.h"
#include "tabloid.h"
#include "Perm.h"
#include "Partition.h"
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


RankSet::RankSet()
{

}



RankSet::~RankSet()
{

}


RankSet NexCom(const int n, const list<int> S, const bool mtc) {
	// taken from Wilf page 44
	// convert S into a vector
	vector<int> R;

	for (int count = 1; count <= n; count++) {
		R.push_back(0);
	}
	

	// is this the first composition? If so R will be trash
	if (mtc) {
		int count = 0;
		for(list<int>::const_iterator iter = S.begin(); iter != S.end(); ++iter) {
			R[count]=*iter;
			count++;
		}
		int i = 1;
		int j=1;
		bool flag = true;
		for(vector<int>::const_iterator iter2 = R.begin(); iter2 != R.end(); ++iter2) {
			if (*iter2 != 0 && flag) {
				i=j;
				flag = false;
			}
			j++;
		}
		int t = R[i-1];
		R[i-1]=0;
		R[0]=t-1;
		R[i]=R[i]+1;
	}
	else {
		for(int count = 1; count < n; count++) {
			R[count] = 0;
		}
		R[0]=n;
	}

	RankSet Answer;
	for (int count2 = 0; count2 < n; count2++) {
		Answer.push_back(R[count2]);
	}

	return(Answer);
}
	
/* int fact(const int n) {
	if (n == 1) {
		return(1);
	}
	else {
		return(n * fact(n-1));
	}
} */

list< RankSet > composition(const int n) {
	list<RankSet> Answer;

	// first we get all weak compositions of n
	set<RankSet> Weak;
	RankSet u, v;
	u=NexCom(n, u, false);
	for (int i = 1; i <= fact(2*n - 1)/(fact(n)*fact(n-1))-1; i++) {
        // now we remove all zeros
		v=u;
		v.remove(0);
		Weak.insert(v);
		u = NexCom(n,u,true);
	}
	
	u.remove(0);
	Weak.insert(u);

	// now we need to convert to a list
	
	for (set<RankSet>::const_iterator iter = Weak.begin(); iter != Weak.end(); ++iter) {
		Answer.push_back(*iter);
	}

	return(Answer);

}            

list<RankSet> ComputeRanks(const int n, const int k) {
	list< RankSet > potentials = composition(n);

	// now we need to test each potential set
	// if it is good we tack on NULL and FULL
	// and add it to answer.
	
	
	list<RankSet> Answer;
	
	for (list< RankSet >::iterator iter = potentials.begin(); iter != potentials.end(); ++iter) {
		// we test to make sure that there are r+2 parts.
		bool flag = true;

		for (list<int>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); ++iter2) {
			if( *iter2 > k) {
				flag = false;
			}
		}

		
		// if it passed all our tests we add it to our answer.
		if (flag) {
			Answer.push_back(*iter);
		}
	}
	return(Answer);
}

	


Partition RankSet::Shape(void) {
	Partition lambda;

	RankSet::iterator temp;
	temp = begin();

	for (RankSet::iterator iter = begin(); iter != end(); ++iter) {
			lambda.Add(*iter);
	}
	return(lambda);
}



list<tabloid> RankSet::ComputeTabloids(void){

	list<tabloid> Answer;

	// We first need to get the shape of these tabloids
	Partition lambda = Shape();

	// Now we create the standard tabloid
	tabloid std = standardoid(lambda);

	// Now we reshape it
	std = reorderrows(ReShape(), std);

	// get all permutations
	list<Perm> Sn = Perms(lambda.Size());

	// apply every perm to our std tabloid
	set<tabloid> tempset;
	tabloid temp;
	for (list<Perm>::iterator iter= Sn.begin(); iter != Sn.end(); ++iter) {
		temp = (*iter) * std;
		tempset.insert(temp);
	}

	for(set<tabloid>::const_iterator iter2 = tempset.begin(); iter2 != tempset.end(); ++iter2) {
		Answer.push_back(*iter2);
	}

	return(Answer);

}

	
list<int> RankSet::Convert(void) {
	list<int> Answer;
	for (RankSet::const_iterator iter = begin(); iter != end(); ++iter) {
		Answer.push_back(*iter);
	}
	return(Answer);
}

Perm RankSet::ReShape(void) {

	// now we sort this set keeping track of transpositions
	list<int> A, B;
	A = Convert();
	Perm sigma(A.size());
	for (int i = 1; i <= A.size(); i++) {
		sigma[i]=i;
	}
	
	list<int>::iterator max;
	for(int count = 1; count <= A.size(); count++) {
		max = A.begin();
		int where;
		int count2 = 1;
		for (list<int>::iterator iter = A.begin(); iter != A.end(); ++iter) {
			if (*max < *iter) {
				max = iter;
				where = count2;
			}
			count2++;
		}

		Perm transposition(A.size());
		for (i = 1; i <= A.size(); i++) {
			transposition[i]=i;
		}
		transposition[count] = where;
		transposition[where] = count;
		sigma = sigma * transposition;

		// set max to -2
		*max = -2;
	}

	return(sigma);
}


chain ConvertFromTabloid(tabloid t) {


	// scroll through the rows of t
	// get the row set
	// add to a chain
	int count = 0;
	chain Answer;
	set<int> nullset;
	Answer.insert(nullset);

	set<int> currentset;

	for (int i = 1; i <= t.RowNumber(); i++) {
		set<int> currentrow = t.Row(i);
		for (set<int>::const_iterator iter = currentrow.begin(); iter != currentrow.end(); ++iter) {
			currentset.insert(*iter);
		}
		Answer.insert(currentset);
	}
	return(Answer);
}
		