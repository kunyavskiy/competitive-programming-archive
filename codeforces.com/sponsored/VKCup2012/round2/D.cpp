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

const int MAXN = 200000; //103680

ll d[210000];
int ptr;

ll p[100];
ll a[100];
int k;

ll V;

void read(){
   scanf("%d",&k);
   V = 1;
   ptr = 0;
   for (int i = 0; i < k; i++){
      scanf(LLD" "LLD,&p[i],&a[i]);
      for (int j = 0; j < a[i]; j++)
        V *= p[i];
   }

   d[ptr++] = 1;
   for (int i = 0; i < k; i++){ 
       int temp = ptr;
       ll temp2 = p[i];
       for (int j = 1; j <= a[i]; j++){
          for (int t = 0; t < temp; t++)
             d[ptr++] = d[t] * temp2;
          temp2 *= p[i];
       }
   }
   sort(d,d+ptr);
}

ll msqrt(ll x){
    ll y = sqrt(ld(x));
    while (y*y < x) 
        y++;
    while (y*y > x)
        y--;
   return y;
}



void solve(){
    read();    

    ll S,aa,ab,ac;
    ll a,b,c;
    int id,temp;

    S = 1LL<<62;
    aa = ab = ac = -1;

    int ID = ptr-1;

    for (int i = 0; i < ptr; i++){
        a = d[i];
        if (a * a > V/a)
            break;

/*        val = msqrt(V/a);

        id = lower_bound(d,d+ptr,val) - d;*/

        while (a * d[ID] > V/d[ID])
            ID--;
        
        id = ID;
        temp = id;

        id = temp;
        while (id >= 0 && (V/a) % d[id])
            id--;
        b = d[id];
        c = V/(a*b);


        if (S > 2*(a*b+a*c+b*c)){
            S = 2*(a*b+a*c+b*c);
            aa = a;
            ab = b;
            ac = c;
        }
    }

    printf(LLD" "LLD" "LLD" "LLD"\n",S,aa,ab,ac);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);
  for (int i = 0; i < t; i++)
    solve();
  return 0;
}

