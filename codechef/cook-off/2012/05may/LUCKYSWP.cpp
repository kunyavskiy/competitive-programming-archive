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


char s[110000];
int fs[110000];
int ss[110000];
int n;


int calc(){

    for (int i = 0; i < n; i++)
       fs[i] = (i?fs[i-1]:0) + (s[i] == '4');
    for (int i = n-1; i >= 0; i--)
        ss[i] = ((i==(n-1))?0:ss[i+1]) + (s[i] == '7'); 

    ss[n] = 0;

    int best = 0;
    int bbal = 0;
    int cbal = 0;

    int ans = ss[0];

    for (int i = 0; i < n; i++){                                                                   
        cbal += (s[i] == '4') - (s[i] == '7');
        bbal = max(bbal,cbal);
        best = min(best,cbal-bbal);
        ans = max(ans,fs[i] + ss[i+1] - best);
        //cerr << i <<" cbal="<<cbal <<" bbal="<<bbal <<" best="<<best <<" fs="<<fs[i] <<" ss="<<ss[i+1] <<" ans="<<ans<<endl;
    }
    //cerr << endl;

    return ans;

}

void solve(){
    gets(s);
    n = strlen(s);
    int ans1 = calc();

    for (int i = 0; i < n; i++)
        s[i] = '4' + '7' - s[i];

    reverse(s,s+n);
    int ans2 = calc();

    printf("%d\n",max(ans1,ans2));

}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int t;
    gets(s);
    sscanf(s,"%d",&t);
    while (t-->0)
        solve();
  return 0;
}