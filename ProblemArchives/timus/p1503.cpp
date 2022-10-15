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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const ld eps = 1e-12;
const ld inf = 1e10;

typedef vector<ld> poly;


bool cmpeql(ld a,ld b){
    return fabsl(a-b) < eps;
}


poly diff(poly p){
    poly res;
    res.resize(p.size()-1);
    for (int i = 0; i+1 < (int)p.size(); i++)
        res[i] = p[i]*(p.size()-i-1);
    return res;
}

ld calc(poly p,ld val){
    ld res = 0;
    for (int i = 0; i < (int)p.size(); i++)
        res = res * val + p[i];
    return res;
}

int sign(ld v){
    if (v > eps)
        return 1;
    else if ( v > -eps)
        return 0;
    else
        return -1;
}


bool solverange(ld l,ld r,poly p,ld& res){
    ld v1 = calc(p,l);
    ld v2 = calc(p,r);
    if (sign(v1) == 0){
        res = l;
        return 1;
    }
    if (sign(v2) == 0){
        res = r;
        return 1;
    }        
    if (sign(v1) == sign(v2))
        return 0;
    if (sign(v1) == -1){
        for (int i = 0; i < 1000; i++){
            ld mid = (l+r)/2;
            if (calc(p,mid) > 0)
                r = mid;
            else
                l = mid;
        }
        res = (l+r)/2;
        return true;
    }
    for (int i = 0; i < 1000; i++){
        ld mid = (l+r)/2;
        if (calc(p,mid) < 0)
            r = mid;
        else
            l = mid;
    }
    res = (l+r)/2;
    return true;
}


vector<ld> solve(poly p){
    if (p.size() == 2){
        vector<ld> res;
        res.pb(-p[1] / p[0]);
        return res;
    }

    vector<ld> roots = solve(diff(p));
    vector<ld> res;

    roots.pb(-inf);
    roots.pb(inf);
    sort(roots.begin(),roots.end());

    for (int i = 0; i < (int)roots.size()-1; i++){
        ld temp = 0;
        if (solverange(roots[i],roots[i+1],p,temp))
            res.pb(temp);
    }

    sort(res.begin(),res.end());
    return res;        
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    poly p;
    int n;
    scanf("%d",&n);
    p.resize(n+1);

    for (int i = 0; i <= n; i++)
        cin >> p[i];

    vector<ld> res = solve(p);

//    cout << res.size() << endl;

    cout.precision(15);
    for (int i = 0; i < res.size(); i++)
        cout << fixed << res[i]+(1e-16) << endl;

    return 0;
}