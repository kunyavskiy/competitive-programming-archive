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

int g[110][110];
int val[110];

int d[110][420];         

int n;
int ans;

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int lcm(int a,int b){
    return a*b/gcd(a,b);
}

int lcm(int msk){
    int x = 1;
    for (int i = 0; i < 7; i++)
        if (msk & (1<<i))
            x = lcm(x,i+1);
    return x;
}

int solve(int msk){
    memset(d,63,sizeof(d));
    int md = lcm(msk);
    if (!(msk & (1<<(val[0]-1))))
        return 1<<30;            
    d[0][val[0]%md] = val[0];


    queue<pair<int,int> > q[8];

    int inq = 1;

    q[0].push(mp(0,(val[0]%md)));



    for (int ptr = 0; inq > 0; ptr++){
        if (ptr == 8)
            ptr = 0;

        for (;q[ptr].size();){
            int v = q[ptr].front().first;
            int r = q[ptr].front().second;
            inq--;
                                                    
            if (d[v][r] > ans)
                return 1<<30;
        
            if (v == n-1 && r == 0){    
                return d[v][r];
            }
            q[ptr].pop();

            for (int i = 0; i < n; i++)
                if (g[v][i] && (msk & (1<<(val[i]-1))) ){
                    int tor = (10*r+val[i])%md;
                    if (d[i][tor] > d[v][r] + val[i]){
                        d[i][tor] = d[v][r] + val[i];
                        q[(ptr+val[i])%8].push(mp(i,tor));
                        inq++;
                    }
                }
        }
    }
    return 1<<30;

}

bool read(){
  scanf("%d",&n);
  if (!n) return false;
  for (int i = 0; i < n; i++)
    scanf("%d",&val[i]);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        scanf("%d",&g[i][j]);


  ans = 1<<30;


  for (int i = 0; i < (1<<7); i++)
    ans = min(ans,solve(i));

  if (ans == (1<<30))
    printf("-1\n");
  else
    printf("%d\n",ans);

  return true;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  while (read());
  return 0;
}

