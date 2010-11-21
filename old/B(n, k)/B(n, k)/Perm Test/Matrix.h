// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__D45D2700_DC1B_11D5_8A63_0050BA79228E__INCLUDED_)
#define AFX_MATRIX_H__D45D2700_DC1B_11D5_8A63_0050BA79228E__INCLUDED_

#include <vector>
#include <iostream>
#include <stdio.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

class Matrix
{
	// this is a vector of the rows of the matrix.
	vector< vector<double> > data;
	
	int rownum, colnum;

public:
	Matrix();
	virtual ~Matrix();

	//copy constructor
	Matrix(const Matrix& other_matrix) {
		rownum = other_matrix.rownum;
		colnum = other_matrix.colnum;
		data   = other_matrix.data;
	}

	Matrix operator= (const Matrix& other_matrix) {
		(*this).rownum = other_matrix.rownum;
		(*this).colnum = other_matrix.colnum;
		(*this).data   = other_matrix.data;
		return(*this);
	}

	// this inserts col into the nth row. note then n >= 1. so n != 0
	void ColumnSet(const int n, vector<double> col);

	// this inserts x into row i col j where i, j >= 1
	void Set(const int i, const int j, const double x);

	int Rank(void);

	inline int Nullity(void) {
		return(colnum - Rank());
	}
	
	inline int col(void) {
		return(colnum);
	}

	inline int row(void) {
		return(rownum);
	}

	double Get(const int i, const int j) {
		return( (data[i])[j] );
	}

	void RowSwap(const int i, const int j);

	void RowMult(const int i, const double d);

	// add d * Row i to row j
	void RowAddMult(const int i, const int j, const double d);

	friend Matrix RowReduce(Matrix N);

	friend ostream &operator<< (ostream &out_file, Matrix M) {
      out_file << "\nMatrix: ";

	  bool first = true;

	  for(int row = 0; row < M.rownum; row++) {
		  if (!first) {
			out_file << "        ";
		  }
		  first = false;
		  for(int col = 0; col < M.colnum; col++) {
			  out_file << M.Get(row,col) << " ";
	      }
		  out_file <<"\n";
	  }
	  out_file << "\n";
      
      return(out_file);
    }

};


#endif // !defined(AFX_MATRIX_H__D45D2700_DC1B_11D5_8A63_0050BA79228E__INCLUDED_)
