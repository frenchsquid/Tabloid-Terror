// tabloid.cpp: implementation of the tabloid class.
//
//////////////////////////////////////////////////////////////////////

#include "tabloid.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tabloid::tabloid()
{

}

tabloid::tabloid(Partition lambda) {
	rownum = lambda.l();


	// we intialize the table
	rows nullrow;
	for (int i = 1; i <= rownum; i++) {
		table.push_back(nullrow);
	}

	
}

tabloid::~tabloid()
{

}

// return the standard tabloid on lambda
tabloid standardoid(Partition lambda) {
	tabloid t(lambda);
	int count = 1;
	int foo;
	for (int i = 1; i <= lambda.l(); i++) {
		rows temp;
		foo = lambda[i];
		for (int j = 1; j <= foo; j++) {
			temp.insert(count);
			count++;
		
		}
		t.table[i-1] = temp;
	}
	return(t);
}


// define Perm * tabloid
tabloid operator * (const Perm sigma,tabloid t) {
	// we loop through all elements of t
	// remember there is a first blank row
	tabloid Answer;
	rows null;
	for (int j = 1; j <= t.rownum; j++) {
		Answer.table.push_back(null);
	}
	Answer.rownum = t.rownum;
	for (int row = 1; row <= t.rownum; row++) {
		rows temp;
		for (rows::const_iterator iter = (t.table[row-1]).begin(); iter != (t.table[row-1]).end(); ++iter) {
			(temp).insert(sigma[*iter]);
		}
		Answer.table[row-1] = temp;
	}

	return(Answer);
}


// number of rows;
int tabloid::RowNumber(void) {
	return(rownum);
}

// return contents of row n
rows tabloid::Row(const int n) {
	return(table[n-1]);
}

// reorder the rows of a tabloid Note it no longer have the shape of a paritition
tabloid reorderrows(const Perm sigma, const tabloid t) {
	tabloid s;


	// we intialize the table
	rows nullrow;
	for (int j = 1; j <= t.rownum; j++) {
		s.table.push_back(nullrow);
	}


	s.rownum = t.rownum;

	for (int i = 1; i <= t.rownum; i++) {
		s.table[i-1] = t.table[sigma[i]-1];
	}

	return(s);
}

	
void tabloid::insert(const vector<int> A) {
	// first we need to conver row to type rows
	rows converted;
	for (vector<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter) {
		converted.insert(*iter);
	}

	// now we update rownum
	rownum++;

	// now we add the row
	table.push_back(converted);
}


// a set operation
void tabloid::Add(const int row, const int value) {
	(table[row-1]).insert(value);
}