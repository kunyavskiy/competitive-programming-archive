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
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;

    ld dans = log(3.0)/log(10.0) + (n-1)*log(2.0)/log(10.0);
    int ans = (int)dans;

    /*cerr << ans <<" "<<dans-ans<<endl;
    cerr << (log(3.0)-log(2.0))/log(10.0) << endl;
    cerr << (log(3.0))/log(10.0) << endl;
    */
    if (n % 2 == 0){
        if ((log(3.0) - log(2.0))/log(10.0) > dans-ans)
            ans--;
    }
    else {
        if ((log(3.0))/log(10.0) > dans-ans)
            ans--;
    }

    cout << ans << endl;
    

    return 0;
}