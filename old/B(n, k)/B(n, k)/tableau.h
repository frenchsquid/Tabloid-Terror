// tableau.h: interface for the tableau class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEAU_H__3E476C42_C563_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_TABLEAU_H__3E476C42_C563_11D5_8A63_0050BA79228E__INCLUDED_

#include "Perm.h"
#include "tabloid.h"
#include "RankSet.h"



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tableau  
{
private:
	typedef vector<int> tabrows;
	vector<tabrows> table;

	Partition shape;

public:
	tableau();
	tableau(Partition lambda);
	virtual ~tableau();

	friend list<tableau> SSYT(const Partition lambda, const Partition mu);
	friend list<tableau> SSYT(Partition lambda, RankSet mu);
	friend list<tableau> SYT(const Partition lamdba);

	int Get(const int row, const int col);

	// return all tableau row equiv to T:
	friend list<tableau> Braceof(const tableau T);

	// return the column and row groups of T
	friend list<Perm> C(const tableau T);
	friend list<Perm> R(const tableau T);

	// act on T by sigma
	friend tableau operator * (const Perm sigma, const tableau T);
	friend tableau Apply (const Perm sigma, const tableau T);
	friend bool RowEqual(const tableau t, const tableau s);
	friend int maxentry(const tableau T);
	friend bool operator < (const tableau& t, const tableau& s) {
		return(true);
	}

	friend bool operator == (const tableau& t, const tableau& s) {
		return( t.table == s.table);
	}

	friend tabloid TableauToTabloid(const tableau T, const Partition lambda);

	// std tableau of shape lambda type mu
	friend tableau standard(Partition lambda, Partition mu);
	friend tableau standard(Partition lambda, RankSet mu);
	friend bool IsSSYT(tableau T); 
	friend bool IsSYT(tableau T);
	friend tableau conjugate(const tableau T);

	void Set(const int row, const int col, const int value);

	friend ostream &operator<< (ostream &out_file, tableau &t) {
      out_file << "\nTableau: ";
	  
	  bool flag = true;
	  for (vector<tabrows>::const_iterator iter = t.table.begin(); iter != t.table.end(); ++iter) {
		  if (!flag) {
			  out_file << "         ";
		  }
		  for (tabrows::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); ++iter2) {
			  out_file << *iter2 << " ";
	      }

		  out_file <<"\n";
		  flag = false;
	  }
	  out_file << "\n";
      
      return(out_file);
    }




};

#endif // !defined(AFX_TABLEAU_H__3E476C42_C563_11D5_8A63_0050BA79228E__INCLUDED_)

