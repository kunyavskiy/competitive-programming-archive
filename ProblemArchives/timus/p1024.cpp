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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int p[1100];
bool used[1100];

int gcd(int a,int b){
    if (!a || !b)
        return a+b;
    return gcd(b,a%b);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> p[i];
        --p[i];
    }

    ll ans = 1;
    for (int i = 0; i < n; i++)
        if (!used[i]){
            int cnt = 0;

            for (int j = i;!used[j]; j=p[j]){
                cnt++;
                used[j] = true;
            }

            
            ans = ans * cnt / gcd(ans,cnt);
        }
    cout << ans << endl;    
  return 0;
}