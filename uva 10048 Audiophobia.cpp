#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

int main(){
  int C, S, Q;
  int testcase = 1;
  while( scanf("%d%d%d", &C, &S, &Q) != EOF &&
       C != 0 && S != 0 && Q != 0 ){

    int path[105][105] = {0};
    for( int i = 1 ; i <= C ; ++i ){
      for( int j = 1 ; j <= C ; ++j ){
        path[i][j] = INT_MAX;
      }
    }

    int c1, c2, d;
    for( int i = 0 ; i < S ; ++i ){
      scanf("%d%d%d", &c1, &c2, &d);
      path[c1][c2] = d;
      path[c2][c1] = d;
    }

    for( int k = 1 ; k <= C ; ++k ){
      for( int i = 1 ; i <= C ; ++i ){
        for( int j = 1 ; j <= C ; ++j ){
          path[i][j] = min(path[i][j], max(path[i][k], path[j][k]));
        }
      }
    }

    if( testcase > 1 ) printf("\n");
    printf("Case #%d\n", testcase++);
    for( int i = 0 ; i < Q ; ++i ){
      scanf("%d%d", &c1, &c2);

      /* c1 != c2, based on problem statements */ 
      if( path[c1][c2] != INT_MAX ) printf("%d\n", path[c1][c2]);
      else printf("no path\n");
    }
  }
  return 0;
}
