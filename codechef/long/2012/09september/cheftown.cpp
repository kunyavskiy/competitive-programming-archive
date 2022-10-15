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


int a[410000];
int cnt = 0;
bool used[410000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,w;
  set<int> s;

  scanf("%d %d",&n,&w);

  int ans = 0;

  for (int i = 0; i < n; i++){
    scanf("%d",&a[i]);
    used[a[i]] = true;
    cnt += used[a[i]-1];
    cnt += used[a[i]+1];
    if (i >= w){
        used[a[i-w]] = false;
        cnt -= used[a[i-w]-1];
        cnt -= used[a[i-w]+1];
    }
    ans += cnt == w-1;
  }

  cout << ans << endl;
 
  return 0;
}