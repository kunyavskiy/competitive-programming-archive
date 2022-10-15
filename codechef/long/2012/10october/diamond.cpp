// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef double ld;


ld p[2010][2010];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    p[1][0] = 1;
    p[2][0] = p[2][1] = 0.5;

    for (int i = 3; i <= 2000; i++){
        p[i][0] = 0.5 * (2.0 - p[i-1][0]);
        p[i][i-1] = 0.5 * (2.0 - p[i-1][i-2]);
        for (int j = 1; j < i-1; j++)
            p[i][j] = 0.5 * (2.0 - p[i-1][j] - p[i-1][j-1]);
    } 

    int t;
    scanf("%d",&t);

    while (t-->0){
        int n;
        scanf("%d",&n);
        ld res = 0;

        for (int i = 0; i < n; i++){
            int a;
            scanf("%d",&a);
            res += p[n][i] * a;
        }

        printf("%.10lf\n",res);
    }


  return 0;
}