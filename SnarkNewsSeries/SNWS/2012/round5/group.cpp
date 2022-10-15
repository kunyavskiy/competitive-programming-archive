#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "group"

using namespace std;

typedef long long ll;
typedef long double ld;

int a[110][110];
int n;

void err(bool q){
    if (!q){
        printf("No\n");
        exit(0);
    }
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
      scanf("%d",&n);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            scanf("%d",&a[i][j]),--a[i][j];
            err(0 <= a[i][j] && a[i][j] < n);
        }

      for (int i = 0; i < n; i++)
         for (int j = 0; j < n; j++)
           for (int k = 0; k < n; k++)
             err(a[a[i][j]][k] == a[i][a[j][k]]);

      int e = -1;

      for (int i = 0; i < n; i++){
         bool ok = true;
         for (int j = 0; j < n; j++)
            if (a[i][j] != j || a[j][i] != j)
                ok = false;

         if (ok)
            e = i;
      }

      err(e != -1);

      for (int i = 0; i < n; i++){
         bool ok = false;
         for (int j = 0; j < n; j++)
            if (a[i][j] == e && a[j][i] == e)
                ok = true;
         err(ok);
      }

      printf("Yes\n");
  	  return 0;
} 