// chain.cpp: implementation of the chain class.
//
//////////////////////////////////////////////////////////////////////

#include "chain.h"

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

chain::chain()
{
	

}

chain::~chain()
{

}



list<set<int> > chain::listofsets(void) {
	return(chain_data);
}

void chain::insert(const set<int> X) {

	bool flag = false;
	
	for(list< set<int> >::iterator iter = chain_data.begin(); iter != chain_data.end(); ++iter) {
		list<set<int> >::const_iterator temp = iter;
		++temp;
		if ( ((*iter != X)  || (temp == chain_data.end()))  || (X < *temp) ) {
			chain_data.insert(iter, X);
			flag = true;
		}
		if (flag) {
			break;
		}
	}
	if (chain_data.size() == 0) {
		chain_data.insert(chain_data.begin(), X);
	}
}
			



void Print(set<int> &X) {
	cout << "{";
	bool flag2 = false;
	for (set<int>::const_iterator iter2 = X.begin(); iter2 != X.end(); ++iter2) {
		if (flag2) {
			cout << ", " << *iter2;
		}
		else {
			cout << *iter2;
			flag2 = true;
		}
	 }
	 cout << "}";
}

bool IsSubset(set<int> A, set<int> B) {
	bool flag = true;
	for(set<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter) {
		bool found = false;
		for(set<int>::const_iterator iter2 = B.begin(); iter2 != B.end(); ++iter2) {
			if (*iter == *iter2) {
				found = true;
				break;
			}
		}
		if (!found) {
			flag = false;
			break;
		}
	}

	return(flag);
}

bool IsChain(chain A, const int k){
	bool flag = true;
	set<int> B;
	for(list< set<int> >::iterator iter = A.chain_data.begin(); iter != A.chain_data.end(); ++iter) {
		if(iter != A.chain_data.begin()) {
			if(IsSubset(*iter, B)) {
				int count = 0;
				for (set<int>::const_iterator iter2 = B.begin(); iter2 != B.end(); ++iter2) {
					set<int>::const_iterator spot = (*iter).find(*iter2);
					if (spot == (*iter).end()) {
						count++;
					}
				}
				if (count > k) {
					flag = false;
				}
			}
			else {
				flag = false;
			}
		}
		B=*iter;
	}
	return(flag);
}







	