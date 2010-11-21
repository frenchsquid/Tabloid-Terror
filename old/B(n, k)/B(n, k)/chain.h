// chain.h: interface for the chain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAIN_H__A8BC3281_C488_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_CHAIN_H__A8BC3281_C488_11D5_8A63_0050BA79228E__INCLUDED_

#pragma warning(disable:4786)

#include <set>
#include <list>
#include "Perm.h"
#include <iostream>
#include <algorithm>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;



class chain  
{
private:


	list< set<int> > chain_data;

public:
	chain();
	chain(list< set<int> > A) {
		chain_data = A;
	}
	virtual ~chain();

	friend void ChainSort(set<int> &A) {
		list<int> temp;
		for(set<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter) {
			temp.push_back(*iter);
		}
		temp.sort();
		set<int> NullSet;
		A = NullSet;
		for(list<int>::iterator iter2 = temp.begin(); iter2 != temp.end(); ++iter2) {
			A.insert(*iter2);
		}
	}

	chain operator* (const Perm sigma) {
		list< set<int> > A = (*this).chain_data;
		chain Answer;
		for(list< set<int> >::iterator iter = A.begin(); iter != A.end(); ++iter) {
			set<int> tempset;
			for(set<int>::iterator B = (*iter).begin(); B != (*iter).end(); ++B) {
				tempset.insert(sigma[*B]);
			}
			ChainSort(tempset);
			Answer.insert(tempset);
		}

		return(Answer);
	}


	void insert(const set<int> X);
	
	// begin points to the first nonempty set
	// end points to the full set
	list<  set <int> > listofsets(void);


	friend bool IsChain(const chain A, const int k);

	friend ostream &operator<< (ostream &out_file, chain &X) {
      
	  bool flag;
	  
	  flag = false;

      for (list< set<int> >::const_iterator iter = X.chain_data.begin(); iter != X.chain_data.end(); ++iter) {
		  if (flag) {
			 out_file << "{";
			 bool flag2 = false;
			 for (set<int>::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); ++iter2) {
					if (flag2) {
						out_file << ", " << *iter2;
					}
					else {
						out_file << *iter2;
						flag2 = true;
					}
			 }
			 out_file << "}";

		  }
		  else {
				out_file << "{";
				bool flag2 = false;
				for (set<int>::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); ++iter2) {
					if (flag2) {
						out_file << ", " << *iter2;
					}
					else {
						out_file << *iter2;
						flag2 = true;
					}
				}
				out_file << "}";
				flag = true;
			}
	
      }

      
      return(out_file);
    }

	inline bool operator == (chain a) {
	/*	for(list< set<int> >::iterator iter = a.chain_data.begin(); iter != a.chain_data.end(); ++iter) {
			ChainSort(*iter);
		}

		for(list< set<int> >::iterator iter2 = chain_data.begin(); iter2 != chain_data.end(); ++iter2) {
			ChainSort(*iter2);
		} */

		return (chain_data == a.chain_data);
	}
};



#endif // !defined(AFX_CHAIN_H__A8BC3281_C488_11D5_8A63_0050BA79228E__INCLUDED_)
