// basis.h: interface for the basis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASIS_H__1E9CDCC2_C3F8_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_BASIS_H__1E9CDCC2_C3F8_11D5_8A63_0050BA79228E__INCLUDED_

#include "Partition.h"
#include "chain.h"
#include <algorithm>
#include <set>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct term {
		double coefficient;
		chain element;
};

typedef list<term> sum;

class basis  
{
private:

	sum sumsofterms;
	

public:
	basis();
	virtual ~basis();
	//list<basis> ComputeBasis(const Partition lambda, const RankSet u);

	inline sum Insides(void) {
		return(sumsofterms);
	}

	inline list<chain> Support(void) {
		list<chain> Answer;
		for(sum::const_iterator iter = sumsofterms.begin(); iter != sumsofterms.end(); ++iter) {
			Answer.push_back( (*iter).element );
		}

		return(Answer);
	}

	friend bool Zeroterm(term T) {
		return(T.coefficient == 0.0);
	}

	// testing: done
	friend void Integrity(basis& b) {
		sum::iterator iter, last;
		last = remove_if(b.sumsofterms.begin(), b.sumsofterms.end(), Zeroterm);
		sum temp;
		for (iter = b.sumsofterms.begin(); iter != last; ++iter) {
			temp.push_back(*iter);
		}
		b.sumsofterms = temp;
	} 

// testing: done.
	inline basis operator = (const basis& element) {
		(*this).sumsofterms = element.sumsofterms;
		return(*this);
	}
// Testing: Done
	inline friend void operator += (basis& element1, basis element) {
		for(sum::iterator x = (element.sumsofterms).begin(); x != (element.sumsofterms).end(); ++x) {
			bool found = false;
			for(sum::iterator y = element1.sumsofterms.begin(); y != element1.sumsofterms.end(); ++y) {	
			// we need to loop through each term
				if ( (*x).element == (*y).element ) {
					(*y).coefficient += (*x).coefficient;
					found = true;
					break;
				}
			}
			// if we never found it we need to add it.
			if (!found) {
				element1.sumsofterms.push_back(*x);
			}
		}
		Integrity(element1);
	}

// Testing:done.
	inline void operator *= (const int k) {
		if (k == 0) {
			basis nullbasis;
			*this = nullbasis;
		}
		else {
			for(list<term>::iterator x = sumsofterms.begin(); x != sumsofterms.end(); ++x) {
				(*x).coefficient *= k;
			}
		}
	}

	inline void operator *= (const double k) {
		if (k == 0) {
			basis nullbasis;
			*this = nullbasis;
		}
		else {
			for(list<term>::iterator x = sumsofterms.begin(); x != sumsofterms.end(); ++x) {
				(*x).coefficient *= k;
			}
		}
	}

// Testing: Done.
	friend ostream &operator<< (ostream &out_file, basis &b) {
		out_file << "\n";
		for(sum::iterator iter = b.sumsofterms.begin(); iter != b.sumsofterms.end(); ++iter) {
			out_file << (*iter).coefficient;
			out_file << "*";
			out_file << (*iter).element;
			sum::iterator tempit = iter;
			++tempit;
			if (tempit != b.sumsofterms.end()) {
				out_file << "+";
			}
		}
      return(out_file);
    }

// Testing: done.
	inline basis operator * (const int k) {
		basis temp;
		if (k == 0) {
			basis nullbasis;
			return(nullbasis);
		}
		else {
		
			temp = *this;
			for(list<term>::iterator x = temp.sumsofterms.begin(); x != temp.sumsofterms.end(); ++x) {
				(*x).coefficient *= k;
			}
		
		}

		return(temp);
	}

// Testing: done
	inline basis operator * (const double k) {
		basis temp;
		if (k == 0.0) {
			basis nullbasis;
			return(nullbasis);
		}
		else {
		
			temp = *this;
			for(list<term>::iterator x = temp.sumsofterms.begin(); x != temp.sumsofterms.end(); ++x) {
				(*x).coefficient *= k;
			}
		
		}

		return(temp);
	}
	
/*
	void Add(term T) {
		basis temp;
		(temp.sumsofterms).push_back(T);
		(*this) += temp;
		Integrity(*this);
	}
*/	

// testing:done.
	// convert chain into a single basis element
	basis operator = (const chain& A) {
		basis temp1;
		term temp;
		temp.coefficient = 1;
		temp.element = A;
		sum nullist;
		nullist.push_back(temp);
		sumsofterms = nullist;
		return(*this);
	}

// testing: Done.
	basis(const chain c) {
		term temp;
		temp.coefficient = 1;
		temp.element = c;
		sum nullist;
		nullist.push_back(temp);
		sumsofterms = nullist;
	}

inline friend bool operator == (basis& element1, basis element) {
		bool flag = true;
		for(sum::iterator x = (element.sumsofterms).begin(); x != (element.sumsofterms).end(); ++x) {
			bool found = false;
			for(sum::iterator y = element1.sumsofterms.begin(); y != element1.sumsofterms.end(); ++y) {	
			// we need to loop through each term
				if ( (*x).element == (*y).element ) {
					if ( (*y).coefficient == (*x).coefficient) {
						flag = false;
						break;
					}
					else {
						found = true;
					}
				}
			}
			if (!found) {
				flag = false;
				break;
			}
		}
		return(flag);
	}
};

#endif // !defined(AFX_BASIS_H__1E9CDCC2_C3F8_11D5_8A63_0050BA79228E__INCLUDED_)
