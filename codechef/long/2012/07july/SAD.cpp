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
typedef long double ld;


int a[110][110];
int b[110];
int c[110];
int n,m;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&m);
    memset(b,63,sizeof(b));
    memset(c,0,sizeof(c));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            scanf("%d",&a[i][j]);
            b[i] = min(b[i],a[i][j]);
            c[j] = max(c[j],a[i][j]);
        }
    //cerr << b[0] <<" "<<b[1] << endl;
    //cerr << c[0] <<" "<<c[1] <<" "<<c[2] << endl;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == b[i] && a[i][j] == c[j]){
                printf("%d\n",a[i][j]);
                return 0;
            }
    printf("GUESS\n"); 
    return 0;
}