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

typedef long long int64;
typedef long double ld;


int bef[20];
int64 cnt[1<<20];
int n = 0;


int64 calc(int mask){
    if (mask == 0)
        return 1;
    if (cnt[mask] != -1)
        return cnt[mask];
    int64& ans = cnt[mask];
    ans = 0;
    for (int i = 0; i < n; i++)
        if ((mask & (1<<i)) && (!(mask & bef[i])))
            ans += calc(mask ^ (1<<i));
    return ans;
}

void build(int mask,int64 x){
}

int main(){
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  return 0;
}