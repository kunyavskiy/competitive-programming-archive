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

typedef unsigned long long ll;
typedef long double ld;


const int MAXN = 110000;
const int P = 239017;
const int MOD1 = 1000000009;
const int MOD2 = 1000000007;
string a,b;

ll h[2][MAXN];
ll stP1[MAXN];
ll stP2[MAXN];

int n;

void inithash(string s,ll* h){
    ll a,b;
    a = b = 0;

    h[0] = 0;

    for (int i = 0; i < n; i++){
        a = (a + s[i] * stP1[i])%MOD1;
        b = (b + s[i] * stP2[i])%MOD2;
        h[i+1] = a | (b << 32);
    }
}

ll get(ll* h,int l,int r){
   ll a = ((h[r]&((1LL<<32)-1)) - (h[l]&((1LL<<32)-1))+MOD1)*stP1[MAXN-r-1];
   ll b = ((h[r]>>32) - (h[l]>>32)+MOD2)*stP2[MAXN-r-1];
   a %= MOD1;
   b %= MOD2;
   return (a | (b<<32));
}

string get(int len){
    if (len == 0)
        return "";
    vector<ll> h;

    for (int i = 0; i+len <= n; i++){
        h.pb(get( ::h[0],i,i+len));
//        cerr << h.back() <<" \n"[i+len==n];
    }
    sort(h.begin(),h.end());

    ll res = 0;
    
    for (int i = 0; i+len <= n; i++){
        if (binary_search(h.begin(),h.end(),get( ::h[1],i,i+len))){
            res = get( ::h[1],i,i+len);
            break;
        }
        if (i+len == n)
            return "";
    }


    for (int i = 0; i+len <= n; i++)
        if (get( ::h[0],i,i+len) == res)
            return string(a.begin()+i,a.begin()+i+len);        
    assert(false);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    getline(cin,a);
    getline(cin,a);
    getline(cin,b);
    n = a.size();

    stP1[0] = 1;
    stP2[0] = 1;

    for (int i = 1; i < MAXN; i++)
        stP1[i] = (stP1[i-1]*P)%MOD1;
    for (int i = 1; i < MAXN; i++)
        stP2[i] = (stP2[i-1]*P)%MOD2;
    
    inithash(a,h[0]);
    inithash(b,h[1]);

    int l = 0;
    int r = n+1;

    for (;r-l > 1;){
        int m = (l+r)/2;
        if (get(m) != "")
            l = m;
        else
            r = m;
    }

    cout << get(l) << endl;
    return 0;
}