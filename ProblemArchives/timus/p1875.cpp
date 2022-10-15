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

ll x[5];
ll y[5];

int ans;

void go(int mask,int cnt){
   if (mask == 31){
     ans = min(ans,cnt);
     return;
   }
   for (int i = 0; i < 5; i++)
    if (!(mask & (1<<i))){
       go(mask | (1<<i), cnt+1);
       for (int j = 0; j < 5; j++)
         if ((!(mask & (1<<j)) && i != j)){
            if (((x[i] - x[j]) * (y[j]*x[i] - y[i]*x[j]) ) < 0)
                continue;            
            if (x[i] == x[j] || y[j]*x[i] == y[i]*x[j])
                continue;
            int mask1 = mask;
            mask1 |= (1<<j)|(1<<i);
           // cerr << i <<" "<<j<<endl;
            for (int k = 0; k < 5; k++)
                if (k != i && k!= j){                
                    if (((x[i] - x[k]) * (y[k]*x[i] - y[i]*x[k]) ) < 0)
                        continue;    
                    if (x[i] == x[k] || y[k]*x[i] == y[i]*x[k])
                        continue;
                    if (x[k]*(x[k] - x[i])*(y[i]*x[j] -x[i]*y[j]) != x[j]*(x[j] - x[i])*(y[i]*x[k] - y[k]*x[i]))
                        continue;
             //       cerr << i <<" "<<j<<" "<<k<<endl;
                    mask1 |= (1<<k);
                }
            go(mask1,cnt+1);
         }
        return;  
    }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    while (true){

    for (int i = 0; i < 5; i++){
        if (!(cin>>x[i]>>y[i]))
            return 0;
    }

    ans = 1<<30;
    go(0,0);
    cout << ans << endl;
    }
    return 0;
}