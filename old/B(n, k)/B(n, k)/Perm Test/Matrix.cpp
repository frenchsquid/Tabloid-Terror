// Matrix.cpp: implementation of the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#include "Matrix.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix::Matrix()
{
	rownum = 0;
	colnum = 0;

}

Matrix::~Matrix()
{

}

// this inserts x into row i col j where i, j >= 1
void Matrix::Set(const int i, const int j, const double x) {
	// Make sure (i, j) exists
	if ( (rownum < i) || (colnum < j) ) {
		cerr << "\nError in Set. Tried to set spot (" << i << "," << j <<").";
		cerr << "When rownum=" << rownum << " and colnum=" << colnum;
		char ch = getchar();
		exit(-1);
	}
	(data[i-1])[j-1] = x;
}

// this inserts col into the nth column note then n >= 1. so n != 0
void Matrix::ColumnSet(const int n, vector<double> col) {
	// Are there n cols yet?
	if(colnum >= n) {
		// make sure the number of rows is right
		if ( rownum != col.size()) {
			cerr << "\n Error in ColumnSet";
			cerr << "\n tried to insert a column of size " << col.size();
			cerr << "When the rownum = " << rownum;
			char ch = getchar();
			exit(-1);
		}

		// set the col
		for(int j = 1; j <= rownum; j++) {
			Set(n, j, col[j-1]);
		}
	}
	else {
		// make sure there are at least n-1 columns
		if(colnum < n-1) {
			cerr << "\n Error in ColumnSet. Tried to insert column " << n;
			cerr << " when column " << n-1 << "doesn't exist";
			char ch = getchar();
			exit(-1);
		}
		//set the colnum 
		colnum++;
		// we need to insert a number at the end of each row
		// if this is the first column we need to do something special
		int count = 0;
		if (n == 1) {
			rownum = col.size();
			for( count = 0; count < col.size(); count++) {
				vector<double> temp;
				temp.push_back(col[count]);
				data.push_back(temp);
			}
		}
		else {
			for(vector< vector<double> >::iterator iter = data.begin(); iter != data.end(); ++iter) {
				(*iter).push_back(col[count]);
				count++;
			}
		}
	}
}

bool IsZero( vector<double> v) {
	bool flag = true;
	for(int i = 0; i < v.size(); i++) {
		if (v[i] != 0) {
			flag = false;
			break;
		}
	}

	return(flag);
}


void Matrix::RowSwap(const int i, const int j) {
	vector<double> temp;
	temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

void Matrix::RowMult(const int i, const double d) {
	for(int j = 0; j < colnum; j++) {
		(data[i])[j] *= d;
	}
}


// add d * Row i to row j
void Matrix::RowAddMult(const int i, const int j, const double d) {
	for (int k = 0; k < colnum; k++) {
		(data[j])[k] += d*((data[i])[k]);
	}
}

Matrix RowReduce(Matrix N) {
	Matrix M = N;
	// we go down the rows
	int currentrow = 0;

	for (int currentcol = 0; currentcol < M.col(); currentcol++) {
		// look for a nonzero entry in the current column and below or at the current row
		int nonzero;
		bool found = false;
		for(nonzero = currentrow; nonzero < M.row(); nonzero++) {
			if ( M.Get(nonzero, currentcol) != 0) {
				found = true;
				break;
			}
		}

		if (!found) {
			// column is all zeroed out moveon
		}
		else {
			// is the nonzero entry in the current row?
			if(nonzero != currentrow) {
				// ok swap rows
				M.RowSwap(nonzero, currentrow);
			}

			// so now the current row has a nonzero entry in column currentcol
			// normalize
			double factor = 1.0/M.Get(currentrow,currentcol);
			M.RowMult(currentrow, factor);

			//now zero out beneath it
			for(int j = currentrow+1; j < M.row(); j++) {
				M.RowAddMult(currentrow, j, -1.0*M.Get(j,currentcol));
		
			}

		}
		currentrow++;
	}

	return(M);
}

int Matrix::Rank(void) {
	Matrix M = RowReduce(*this);
	int Answer = 0;;
	for( int i = 0; i < rownum; i++) {
		if (!IsZero( (M.data)[i] )) {
			Answer++;
		}
	}
	return(Answer);
}
