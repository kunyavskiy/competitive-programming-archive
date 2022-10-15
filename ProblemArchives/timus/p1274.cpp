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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<ll,ll> frac;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

int sign(ll a){
    return (a > 0) - (a < 0);
}

frac get(){
   string s;
   getline(cin,s);
   ll a,b,c;
   if (sscanf(s.data(),LLD" "LLD"/"LLD,&a,&b,&c) == 3)
      return frac(sign(a)*(abs(a)*c+b),c);   
   if (sscanf(s.data(),LLD"/"LLD,&b,&c) == 2)
      return frac(b,c);
   sscanf(s.data(),LLD,&a);
   return frac(a,1LL);   
}

void print(frac a){
    if (a.first < 0)
        printf("-"),a.first *= -1;
    if (a.first == 0 || a.first >= a.second)
        printf(LLD" ",a.first / a.second);
    a.first %= a.second;
    if (a.first)
        printf(LLD"/"LLD,a.first,a.second);
    printf("\n");
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    frac a = get();
    string s;
    getline(cin,s);
    frac b = get();

    frac res;

    if (s == "*")
       res = frac(a.first*b.first,a.second*b.second);
    else if (s == "/")
       res = frac(a.first*b.second,a.second*b.first);
    else if (s == "+")
       res = frac(a.first*b.second + b.first*a.second,a.second*b.second);
    else 
       res = frac(a.first*b.second - b.first*a.second,a.second*b.second);

    if (res.second < 0)
        res.first *= -1,res.second *= -1;

    ll g = gcd(abs(res.first),abs(res.second));

    res.first /= g, res.second /= g;

    print(res);     
    return 0;
}