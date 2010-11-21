// Tabloid2.h: interface for the Tabloid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLOID2_H__A49DD944_C16A_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_TABLOID2_H__A49DD944_C16A_11D5_8A63_0050BA79228E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Partition.h"

class Tabloid  
{
private:
	Partition Shape;
	vector <vector<int> > data; 
public:
	Tabloid(const Partition lambda);
	virtual ~Tabloid();
	void SetRow(const int row, const vector<int> stuff);	
    

	friend ostream &operator<< (ostream &out_file, Tabloid &T) {
  
      out_file << "\nTabloid: \n";
	  for (int i = (T.Shape).maxpart(); i>0; i++) {
		  for(int j = 1; j <= T.Shape.M(i); j++) {
			  cout << i << " ";
		  }
	  }

      out_file << "\n";
      return(out_file);
    }

};

#endif // !defined(AFX_TABLOID2_H__A49DD944_C16A_11D5_8A63_0050BA79228E__INCLUDED_)
