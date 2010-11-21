// RankSet.h: interface for the RankSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANKSET_H__1E9CDCC3_C3F8_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_RANKSET_H__1E9CDCC3_C3F8_11D5_8A63_0050BA79228E__INCLUDED_

#include "tabloid.h"
#include "chain.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
class RankSet:public list<int>  
{

public:
	RankSet();
	virtual ~RankSet();

	Partition Shape(void);
	friend list<RankSet> ComputeRanks(const int n, const int k);
	list<tabloid> ComputeTabloids(void);
	friend chain ConvertFromTabloid(const tabloid t);
	Perm ReShape(void);
	list<int> Convert(void);

	friend ostream &operator<< (ostream &out_file, RankSet &u) {
      out_file << "\nRankSet: {";
	  
	  bool flag = false;
      for (RankSet::const_iterator iter = u.begin(); iter != u.end(); ++iter) {
		  out_file << " " << *iter;
      }

	  out_file <<"}\n";
      
      return(out_file);
    }


};

list< RankSet > composition(const int n);
#endif // !defined(AFX_RANKSET_H__1E9CDCC3_C3F8_11D5_8A63_0050BA79228E__INCLUDED_)
