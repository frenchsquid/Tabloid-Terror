#ifndef _PARTITION_H_INCLUDED_
#define _PARTITION_H_INCLUDED_
#include <vector>
#include <list>

#include <string.h>
#include <iostream>

/****************************************************************
 * Partition class Ver 1.0		  			*
 *					  			*
 * Member functions:			  			*
 * 	Partition 	- Create an empty partition		*
 *	l[i]		- Get the ith part of l			*
 *	=		- Assignment				*
 *      Size 	  	- Return the size of l			*
 *	l(lambda)	- Return length				*
 *	M(i) 		- Return the multiplicity of i in l   	*
 *	~	 	- Return the conjugate partition  	*
 *	==	  	- Equality				*
 *	Add(n)		- Add n to l				*
 *	Remove(n)	- Remove n from l			*
 *			  Do nothing if no n in l		*
 *	!=		- inequality				*
 *	>, <		- Young ordering			*
 *	<=, >=		- Dominance ordering			*
 *	<<, >>		- iostream library stuff		*
 *	Par(n)		- Generate partitions of n		*
 *	lprime(lambda)  - Return conjugate length		*
 ****************************************************************/

using namespace std;

typedef vector<int> IntVector; 


class Partition {
  private:
    // a partition will be stored by its multiplicity table. 
    // so the number of 2s is data[2]

	IntVector data;
    int length;
    int value;
    int max;

  public:
    // Default constructor. 
    Partition(void) {
      length = 0;
      value  = 0;
      max    = 0;
      for(int i=1; i<=12; i++) {
        data.push_back(0);
      }
    }

	void Zero(void) {
		Partition Null;
		*this = Null;
	}

    // Copy constructor. This allows calls by value.
    Partition(const Partition& other_partition) {
      data   = other_partition.data;
      length = other_partition.length;
      value  = other_partition.value;
      max    = other_partition.max;
    }

    // Nothing for the destructor to do
    ~Partition() {}

    // Get the ith part of l
    int operator[] (const int index) {
		int count = 0;
		int loop;
		int Answer;
		for (loop=max; loop >0; loop--) {
			for (int loop2 = 1; loop2 <= M(loop); loop2++) {
				count++;
				if (count == index) {
					Answer = loop;
				}
			}
		}

		return(Answer);
	}

    // Return what the partition partitions
    int Size(void) {
      return(value);
    }

	int maxpart(void) {
		return(max);
	}

    // Return the length
    int l(void) {
      return(length);
    }

    // return the multiplicity of i
    int M(const int i) {
      if (i <= max) {
        return(data[i]);
      }
      else {
	return(0);
      }
    }



    // conjugate partition 
    Partition operator ~(void); 

    // Assignment
    Partition operator = (const Partition& l) {
      data   = l.data;
      length = l.length;
      value  = l.value;
      max    = l.max;
	  return(*this);
    }

    bool operator == (const Partition& l) {
      return(l.data == data);
    }

    void Add(const int n);

    void Remove(const int n);

    bool operator != (const Partition& l) {
      return(data != l.data);
    }

    bool operator < (const Partition& l );

    bool operator > (const Partition& l);

    bool operator <= (const Partition& l);

    bool operator >= (const Partition& l);

    istream &operator >> (Partition &lambda);

    friend ostream &operator<< (ostream &out_file, Partition &lambda) {
      int loop, loop2;
	  bool flag;
	  
	  flag = false;

      out_file << "(";
      for (loop=lambda.max; loop >0; loop--) {
		for (loop2 = 1; loop2 <= lambda.M(loop); loop2++) {
			if (flag) {
				out_file << ", " << loop;
			}
			else {
				out_file << loop;
				flag = true;
			}
		}
      }

      out_file << ")";
      return(out_file);
    }

    friend Partition lprime(const Partition l);
};    

typedef list<Partition> ParList;

ParList ParMaxPart(const int n, const int maxpart);
ParList Par(const int n);

#endif // _PARTITION_H_INCLUDED_
