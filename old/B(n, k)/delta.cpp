set<point> properpowerset(int n)

Coord_Mat_double delta(int n, int k, int l) {
  
  vector<chain> basisl, basislminus1;
  chain nullchain;
  point fullset;
  int loop, i, j, rows, cols, index;
  vector<chain>::const_iterator iter;
  chain element;
  chain::const_iterator iter2, iter3;
  bool flag;

  for(loop=1; loop<n+1; loop++) {
    fullset.push_back(loop);
  }  

  basisl = chain(l+2, nullchain, properpowerset(n), k, fullset);
  basislminus1 = chain(l+1, nullchain, properpowerset(n), k, fullset);

  rows = basislminus1.size();
  cols = basisl.size();  
  double Answer(rows, cols);
  for(i=1; i<=rows; i++) {
    for(j=1; j<=cols; j++) {
      Answer = 0.0;
    }
  }

  index = 0;
  for(iter=basisl.begin(); iter != basisl.end(); ++iter) {
    index++;
    for(iter2=*iter.begin()+1; iter2 != *iter2.end()-1; ++iter2) {
      element = *iter;
      element.remove(*iter2);
    
      flag = true;
      for(iter3 = element.begin(); iter3 != element.end()-1; ++iter3) {
         if( !( 
  