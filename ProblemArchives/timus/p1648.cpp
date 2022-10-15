#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int a[21000];

ll ans1,ans2;
int n,d;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> n >> d;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<pair<int,int> > v;

    for (int i = 0; i < n; i++){
        v.pb(mp(d,i));
        while (v.size() && a[i]){
            int t = min(a[i],v.back().first);
            ans1 += t;
            ans2 += (i-v.back().second)*1LL*t;
            v.back().first -= t;
            a[i] -= t;
            if (v.back().first == 0)
                v.pop_back();
        }
    }

    cout << ans1 << " "<<ans2 << endl;
    return 0;
}