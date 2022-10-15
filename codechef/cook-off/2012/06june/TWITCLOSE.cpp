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


bool used[1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,k;
    scanf("%d %d",&n,&k);

    int cnt = 0;

    for (int i = 0; i < k; i++){
        int a;
        if (scanf(" CLICK %d ",&a) == 1){
            cnt += 1 - 2*used[a];
            used[a] ^= 1;
        }
        else {
            scanf("OSEALL");
            cnt = 0;
            memset(used,0,sizeof(used));
        }
        printf("%d\n",cnt);
    }

  return 0;
}