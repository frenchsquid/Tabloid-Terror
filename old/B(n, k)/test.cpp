#include "Partition.h"


void main(void) {
  
  cout << "\nTesting constructor";
  Partition lambda, mu, nu;

  cout << "\nTesting print";
  cout << lambda;

  cout << "\nTesting Add";
  lambda.Add(3);
  lambda.Add(1);
  lambda.Add(3);
  cout << lambda;

  cout << "\nTesting =";

  mu = lambda;
  cout << mu;

  cout << "\nTesting Par";

  ParList TestList;
  TestList = Par(6);

  for (ParList::iterator iter = TestList.begin(); iter != TestList.end(); ++iter) {
	cout << *iter;
	cout << "\nPartition: ";
	for (int q = 1; q <= (*iter).l(); q++) {
		cout <<" " << (*iter)[q];
	}
  }

  cout <<"\n Now testing conjugation: ";
  for (ParList::iterator iter2 = TestList.begin(); iter2 != TestList.end(); ++iter2) {
	  cout << lprime(*iter2);
  }


  

  cout << "\n Press a number and return to continue";
  int qpw;
  cin >> qpw;
}
