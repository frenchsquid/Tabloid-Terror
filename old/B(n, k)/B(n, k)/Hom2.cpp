#include "RankSet.h"
#include "Partition.h"
#include "tableau.h"
#include "basis.h"
#include "Perm Test\Matrix.h"
#include <math.h>

using namespace std;

int parity(const int i) {
	if(i % 2 == 0) {
		return(1);
	}
	else {
		return(-1);
	}
}

//Testing: done.
basis ChainDelta(chain A, const int k) {
	// we apply the boundary map to a chain
	// so we sum over all sets in the chain

	basis Answer;
	int index = 0;
	list<set<int> > chainlist = A.listofsets();
	//get the size of the first set.
	int n = ( *(chainlist.begin()) ).size();
	if (chainlist.size() == 3) {
		return(Answer);
	}
	else {

		for(list<set<int> >::iterator X = chainlist.begin(); X != chainlist.end(); ++X) {
			index++;
			list< set<int> > newchain = chainlist;
			list< set<int> >::iterator temp = X;
			++temp;
			if ( X != chainlist.begin() && temp != chainlist.end() ) {
				//we need to get an iterator pointing to *X in newchain
				list< set<int> >::iterator pointy;
				for(list< set<int> >::iterator iter = newchain.begin(); iter != newchain.end(); ++iter) {
					if( (*X) == (*iter) ) {
						pointy = iter;
						break;
					}
				}
	
				newchain.erase(pointy);
				chain temp2(newchain);
				if(IsChain(temp2, k)) {
					basis temp;
					temp = temp2;
					temp *= parity(n-index);
					Answer += temp;
				}
			}
		}
	}
	return(Answer);
}


// Tested
basis Delta(const int k, basis element) {

	// element is a sum of chains
	// we need to loop over each chain.
	// we store the new basis-type element in Answer
	basis Answer;
	sum stuff = element.Insides();
	sum::const_iterator A;
	for(A = stuff.begin(); A != stuff.end(); ++A) {
		// call the real delta that acts on chains.
		chain c = (*A).element;
		basis image = ChainDelta(c, k);
		image *= (*A).coefficient;
		Answer += image;
	}

	return(Answer);
}

//Testing: Done.
vector<RankSet> imageranks(RankSet u, const int l) {
	
	// convert to a vector for easier scrolling
	vector<int> stuff;
	for(RankSet::const_iterator iter = u.begin(); iter != u.end(); ++iter) {
		stuff.push_back(*iter);
	}

	// scroll through each spot but not the last
	// and combine that spot with the next one.
	vector<RankSet> Answer;

	if(stuff.size() == 1) {
		return(Answer);
	}

	for (int i = 1; i < stuff.size(); i++) {
		RankSet temp;
		for (int j = 1; j < i; j++) {
			temp.push_back(stuff[j-1]);
		}
		int join = stuff[i-1] + stuff[i];
		temp.push_back(join);
		for (int k = i+2; k <= stuff.size(); k++) {
			temp.push_back(stuff[k-1]);
		}
		// Now make sure no part is bigger than k
		bool kcond = true;
		for (RankSet::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
			if ( (*iter) > l) {
				kcond = false;
				break;
			}
		}
		if(kcond) {
			Answer.push_back(temp);
		}
	}

	return(Answer);
}

//Testing: Done.
basis e(tableau t, chain c) {
	list<Perm> colgroup = C(t);
	list<Perm> rowgroup = R(t);
	basis Answer;
	// we scroll through col * sign and the row
	for(list<Perm>::iterator sigma = colgroup.begin(); sigma != colgroup.end(); ++sigma) {
		for (list<Perm>::iterator tau = rowgroup.begin(); tau != rowgroup.end(); ++tau) {
			const chain temp = c * ((*sigma) * (*tau));
			basis tempbas;
			tempbas = temp;
			tempbas *= sign(*sigma);
			Answer += tempbas;
		}
	}

	return(Answer);
}

//Tested
basis e(const tableau t, basis b) {
	basis Answer;
	sum stuff = b.Insides();
	sum::const_iterator A;
	for(A = stuff.begin(); A != stuff.end(); ++A) {
		// call the real e that acts on chains.
		chain c = (*A).element;
		basis image = e(t, c);
		image *= (*A).coefficient;
		Answer += image;
	}

	return(Answer);
}	

//Testing: Done
// computes the innerproduct
double Prod(basis a, basis b) {
	double Answer = 0.0;
	sum A, B;
	sum::iterator iter1, iter2;
	A = a.Insides();
	B = b.Insides();

	for(iter1 = A.begin(); iter1 != A.end(); ++iter1) {
		for(iter2 = B.begin(); iter2 != B.end(); ++iter2) {
			if ( (*iter1).element == (*iter2).element ) {
				Answer += ((*iter1).coefficient)*((*iter2).coefficient);
			}
		}
	}

	return(Answer);
}

//Testing: Done
double Norm(const basis b) {
	return(sqrt(Prod(b,b)));
}

/*
//Testing:
void GramSchmidt(const vector<basis> B, vector<basis>& O, vector< vector<double> >& M) {
	// We gramschmidt B. 
	// O contains the ons.
	//O_i = M_i1 B_1 + ... + M_in B_n
	int n = B.size();
	vector<basis> Otemp(n);
	// We normalize the first vector
	basis first = B[0];
	first *= 1/(Norm(first));
	Otemp[0]=first;
	vector<double> firstrow(n);
	firstrow[0] = 1.0/Norm(B[0]);
	for (int i = 1; i < n; i++) {
		firstrow.push_back(0.0);
	}
	M.push_back(firstrow);

	// now we loop through the others;
	for(i = 1; i < n; i++) {
		// Get the projection onto our current subspace
		// We use the formula O[i] = Normalization of (B[i] - Proj_O(B[i]))
		// and B[i] - Proj_O(B[i]) = B[i] - Prod(O[0], B[i])O[0] - ... - Prod(O[i-1],B[i])O[i-1]
		// so first we get the coefficients
		vector<double> newrow(n);
		for(int l = 0; l < n; l++) {
			newrow[l]=0.0;
		}
		newrow[i] = 1.0; // This takes care of the first term.
		basis temp;
		temp = B[i];
		for(int j = 0; j < i; j++) {
			double prodtemp = Prod(Otemp[j], B[i]) * (-1.0);
			// so we need to add prodtemp times M[j] to newrow;
			for(int k = 0; k < n; k++) {
				newrow[k] += prodtemp * ((M[j])[k]);
			}
			temp += Otemp[j] * prodtemp;
		}

		double normtemp = 1.0/Norm(temp);
		temp *= normtemp;
		for(j = 0; j < n; j++) {
			newrow[j] *= normtemp;
		}

		M.push_back(newrow);
		Otemp[i]=temp;
	}
	for(i = 0; i < n; i++) {
		O.push_back(Otemp[i]);
	}
}




// If A = project(b, O) then b = sum A_i O_i
vector<double> project(basis b, vector<basis> B) {
	// Note we need that B is LI.
//	cout << "\n" << b;
//	for(vector<basis>::iterator iter = B.begin(); iter != B.end(); ++iter) {
//		cout << "\n" << *iter;
//	}
	// We use Gram-Schmidt
	vector<basis> O;			// Will contain ons
	vector< vector<double> > M;	// O_i = M_i1 B_1 + ... + M_in B_n
	GramSchmidt(B, O, M);
	int n = B.size();
	
	vector<double> Answer(n);
	// we loop through O and compute the interproduct of b with each element of the ons
	// the we reexpress O in terms of B
	for(int i = 0; i < n; i++) {
		int coef = Prod(O[i], b);
		for (int j = 0; j < n; j++) {
			Answer[j] += coef*((M[i])[j]);
		}
	}

	return(Answer);
}
*/

vector<double> project(basis b, vector<basis> B) {
	// first we need to create the matrix
	// Getting the support
	vector<chain> SupportVec;
	for(vector<basis>::const_iterator iter = B.begin(); iter != B.end(); ++iter) {
		list<chain> TempSup = (*iter).Support()
		for(list<chain>::const_iterator iter2 = TempSup.begin(); iter2 != TempSup.end(); ++iter2) {
			bool found = false;
			for(vector<chain>::const_iterator iter3 = SupportVec.begin(); iter3 != SupportVec.end(); ++iter3) {
				if (*iter3 == *iter2) {
					found = true;
					break;
				}
			}
			if (!found) {
				SupportVec.push_back(*iter2);
			}
		}
	}

	// Now that we have the basis we can begin to make the matrix
	Matrix M;
	int n = SupportVec.size();
	int m = B.size();
	// we use column insert
	for(int i = 0; i < m; i++) {
		// we need to make the column
		vector<double> TempCol(n);
		for (int j = 0; j < n; j++) {
			basis TempBasis(SupportVec[j]); 
			TempCol[j] = Prod(B[i], TempBasis);
		}

		// Now we insert the column
		M.ColumnSet(i+1, TempCol);
	}

	// Now we add the last column
	vector<double> TempCol(n);
	for (int j = 0; j < n; j++) {
		basis TempBasis(SupportVec[j]); 
		TempCol[j] = Prod(b, TempBasis);
	}
	M.ColumnSet(m+1, TempCol);

	// Now we rowreduce
	Matrix R = RowReduce(M);
	
	//Now we have b in terms of elements of B
	//Now we read off the last column for coefficients
	vector<double> Answer(m);
	for (i = 0; i < m; i++) {
		Answer[i] = R.Get(i, m);
	}

	return(Answer);
}


void main(void) {
	
	int n, k, r;

	cout << "Please enter n ";
	cin >> n;
	cout << "Please enter k ";
	cin >> k;

	// We first loop through all partitions of n
	list<Partition> pars;
	pars = Par(n);

	// for latter use
	list<RankSet> ranks;
	ranks = ComputeRanks(n, k);
	for(list<Partition>::iterator lambda = pars.begin(); lambda != pars.end(); ++lambda) {
		vector<Matrix> MatList(n-1);
		vector<bool> exists(n-1);
		for(int o = 0; o < n-1; o++) {
			exists[o] = false;
		}
		// Now we loop through all possible ranks-sets
		// Answers store our multiplicity calculations
		vector<int> Answers(n-1);
		// Before we begin we need to get all possible SSYT to create an ordered basis
		vector< vector<basis> > Support(n-1);
		for(list<RankSet>::const_iterator iter = ranks.begin(); iter != ranks.end(); ++iter) {
			list<tableau> temptablist = SSYT(*lambda, *iter);
				
			if(temptablist.size() != 0) {

				// convert each tableau to a chain
				list<chain> tempchainlist;
				for(list<tableau>::const_iterator tabby = temptablist.begin(); tabby != temptablist.end(); ++tabby) {
					Partition gamma2;
					for (RankSet::const_iterator iter7 = (*iter).begin(); iter7 != (*iter).end(); ++iter7) {
						gamma2.Add(*iter7);
					}
					tabloid tempoid;
					tempoid = TableauToTabloid(*tabby, gamma2);
					chain c = ConvertFromTabloid(tempoid);
					basis b(c);
					(Support[(*iter).size()-2]).push_back(b);
				}
			}
		}
		for(list<RankSet>::iterator u = ranks.begin(); u != ranks.end(); ++u) {
			// We need to get possible ranges of u

			list<tableau> tableaulist = SSYT(*lambda, *u);
			// convert to chains
			list<chain> domain;
			
			Partition gamma;
			for (RankSet::const_iterator iter = (*u).begin(); iter != (*u).end(); ++iter) {
				gamma.Add(*iter);
			}

			for(list<tableau>::const_iterator tabby = tableaulist.begin(); tabby != tableaulist.end(); ++tabby) {				
				domain.push_back(ConvertFromTabloid(TableauToTabloid(*tabby, gamma)));
			}
			
			// So now domain contains all chains which we need to compute the image of
			// Now get all images of *u
			//Test code:
		

			vector<RankSet> images = imageranks(*u, k);

			// get a list  of SSYT
			// where each element of the list is a SSYT 
			// of each possible image
			
			vector<chain> posschains;
			for(vector<RankSet>::iterator image = images.begin(); image != images.end(); ++image) {
				list<tableau> temptablist = SSYT(*lambda, *image);
				
				if(temptablist.size() != 0) {

					// convert each tableau to a chain
					list<chain> tempchainlist;
					for(tabby = temptablist.begin(); tabby != temptablist.end(); ++tabby) {
						Partition gamma2;
						for (RankSet::const_iterator iter = (*image).begin(); iter != (*image).end(); ++iter) {
							gamma2.Add(*iter);
						}
						tabloid tempoid;
						tempoid = TableauToTabloid(*tabby, gamma2);
						chain c = ConvertFromTabloid(tempoid);
						posschains.push_back(c);
					}
				}
			}
			// So now posschains contains all possible image chains

			// this stores the dimension of the range
			int rangedim = posschains.size();

			// for each possible image chain, apply the 
			// Young symmetrizer. We will get a result of type basis.
			Partition theta;
			for(int junk = 1; junk <= (*lambda).Size(); junk++) {
				theta.Add(1);
			}
			tableau t = standard(*lambda, theta);
			vector<basis> vecofimages;
			for(vector<chain>::const_iterator c = posschains.begin(); c != posschains.end(); ++c) {
				vecofimages.push_back(e(t, *c));
			}
			//vecofimages now contains all the symmetrized images.

			// for each chain in the domain apply delta
			vector<basis> domainchains;
			list<chain>::iterator c1;
			for(c1 = domain.begin(); c1 != domain.end(); ++c1) {
				domainchains.push_back(Delta(k, *c1));
			}

			// then apply the Young symmetrizer of shape lambda
			// and standard to the images of delta
			vector<basis> Answer;
			vector<basis>::const_iterator X;
			for(X = domainchains.begin(); X != domainchains.end(); ++X) {
				Answer.push_back(e(t, *X));
			}
			
			// then get the projection of our result onto each 
			// possible image
			if(rangedim == 0) {
				Answers[(*u).size()-2] = Answers[(*u).size()-2] + domainchains.size();
	//			cout << "\nWith lambda = " << *lambda;
	//			cout << "\nAnd u = " << *u;
	//			cout << "We add nullity " << domainchains.size();
	//			cout << "\nPress any key to continue";
	//			char ch = getchar(); 
				
			}
			else {
				Matrix Mat = MatList[(*u).size()-2];
				int newrow = Mat.col() + 1;
				for(int count = newrow; count < newrow + Answer.size(); count++) {
					// store this as a column in our matrix.
					vector<double> tempvec = project(Answer[count-newrow], vecofimages);
					Mat.ColumnSet(count, tempvec);
				}
				
				MatList[(*u).size() - 2] = Mat;
				exists[(*u).size()-2] = true;
			}
		}
		for(r = 0; r <= n-2; r++) {
			cout << "\nWith lambda = " << *lambda;
			cout << "\nand r = " << r;
			cout << "\nWe get the matrix" << MatList[r];
			cout << "With nullity = " << MatList[r].Nullity();
			cout << " and rank = " << MatList[r].Rank();
			cout << "\nOther contributions give " << Answers[r];
			// we adjust the multiplicity vector
			if (exists[r]) {
				Answers[r] += MatList[r].Nullity();
				Answers[r-1] -= MatList[r].Rank();
			}
			cout << "\nPress any key to continue";
			char ch = getchar();
		
		}
		for(r = 0; r <= n-2; r++) {
			cout << "\nThe multiplicity of ";
			cout << (*lambda);
			cout << " in H" << r << " is: " << Answers[r];
		}
		cout << "\nPress any key to continue";
		char ch = getchar();
	}
	
}

		

