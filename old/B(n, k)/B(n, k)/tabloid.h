// tabloid.h: interface for the tabloid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLOID_H__3E476C41_C563_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_TABLOID_H__3E476C41_C563_11D5_8A63_0050BA79228E__INCLUDED_

#include <set>
#include <vector>
#include "Partition.h"
#include "Perm.h"
// #include <algorithm>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
typedef set<int> rows;

class tabloid  
{
private:
	
	vector<rows> table;

	int rownum;


public:
	tabloid();
	tabloid(const Partition lambda);
	virtual ~tabloid();

	


	// number of rows;
	int RowNumber(void);

	// return contents of row n
	set<int> Row(const int n);

	// reorder the rows of a tabloid Note it no longer have the shape of a paritition
	friend tabloid reorderrows(const Perm sigma, const tabloid t);

	void insert(const vector<int> row);

	// a set operation
	void Add(const int row, const int value);
	
	// A std tabloid
	friend tabloid standardoid(Partition lambda);

	friend ostream &operator<< (ostream &out_file, tabloid &t) {
      out_file << "\nTabloid: ";
	  
	  bool flag = true;
	  for (vector<rows>::const_iterator iter = t.table.begin(); iter != t.table.end(); ++iter) {
		  if (!flag) {
			  out_file << "         ";
		  }
	//	  sort((*iter).begin(), (*iter).end());
		  for (rows::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); ++iter2) {
			  out_file << *iter2 << " ";
	      }

		  out_file <<"\n";
		  flag = false;
	  }
	  out_file << "\n";
      
      return(out_file);
    }

	// define Perm * tabloid
	friend tabloid operator * (const Perm sigma, const tabloid t);

	inline bool operator == (const tabloid t) {
		return(table == t.table);
	}

	// this is to allow sets of tabloids
	// < is is needed for the insert generic algorithm
	friend bool operator < (const tabloid& t, const tabloid& s) {
		return(true);
	}

};

#endif // !defined(AFX_TABLOID_H__3E476C41_C563_11D5_8A63_0050BA79228E__INCLUDED_)
