// Perm.h: interface for the Perm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERM_H__1E9CDCC4_C3F8_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_PERM_H__1E9CDCC4_C3F8_11D5_8A63_0050BA79228E__INCLUDED_

#include <vector>
#include <list>
#include <iostream>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;

typedef vector<int> VECINT;
class Perm:public vector<int>  
{
public:
	Perm();
	Perm(const int n);
	virtual ~Perm();

	// sigma is in Sn
	int n(void) {
		return((*this).size()-1);
	}

	friend list<Perm> Perms(const int n);
	// return the sign of a permutation
	friend int sign(const Perm sigma);

	// return the permutation sending A to B
	friend Perm PermMake(const list<int> A, const list<int> B);

	friend ostream &operator<< (ostream &out_file, Perm &sigma) {
      out_file << "\nPermutation: (";
	  
	  bool flag = false;
      for (Perm::const_iterator iter = sigma.begin(); iter != sigma.end(); ++iter) {
		  // skip the first 0
		  if (flag) {
			  out_file << " " << *iter;
		  }
		  flag = true;
      }

	  out_file <<")\n";
      
      return(out_file);
    }

	friend Perm operator * (Perm sigma, const Perm tau) {
		Perm Answer(sigma.n());

		for(int i = 1; i <= sigma.n(); i++) {
			Answer[i] = sigma[tau[i]];
		}

		return(Answer);
	}

};

int fact(const int n);

#endif // !defined(AFX_PERM_H__1E9CDCC4_C3F8_11D5_8A63_0050BA79228E__INCLUDED_)
