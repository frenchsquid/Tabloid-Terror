#include "Partition.h"
#include <algorithm>


void Partition::Add(const int n) {
  ++data[n];
  ++length;
  value += n;
  if (n > max) {
	  max = n;
  }
}

inline int min(const int a, const int b) {
	if (a < b) {
		return(a);
	}
	else 
		return(b);
}

ParList ParMaxPart(const int n, const int maxpart) {
	
	ParList temp, RetList;
    Partition lambda;
	Partition NullPartition;

	int BiggestPart;

	if (n <= 0) {
		cout << "\nSomething is wrong. Someone tried to create a partition of " << n;
		cout << " This makes no sense";
		exit(-1);
	}

	if (n == 1) {
		lambda.Add(1);
		temp.push_back(lambda);
		return(temp);
	}
	else {
		 
		for (int i = 1; i <= min(n, maxpart); i++) {
			BiggestPart = min(i,n);

			if (i != n) {
				temp = ParMaxPart(n-i, BiggestPart);
				for (ParList::const_iterator iter = temp.begin(); iter != temp.end(); ++iter) {
					lambda = *iter;
					lambda.Add(i);
					RetList.push_back(lambda);
				}
			}
			else {
				lambda = NullPartition;
				lambda.Add(n);
				RetList.push_back(lambda);
			}
		}
	}

	return(RetList);
}

ParList Par(const int n) {
	return(ParMaxPart(n,n));
}

Partition lprime(Partition l) {
	Partition Answer;

	// we calculate l'_i
	// recall that the length of l' will be l_1
	for (int i = 1; i <= l[1]; i++) {
		int lambdaprimei = 0;
		int count = 0;
		for (int j = 1; j <= l.l(); j++) {
			if (l[j] >=i) {
				count++;
			}
		}
		Answer.Add(count);
	}
	return(Answer);
}




	
