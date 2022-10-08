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

int n,m;

char c[1100][1110];

int d[1100][1100][2];

bool good(int x,int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d",&n,&m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf(" %c",&c[i][j]);

  memset(d,63,sizeof(d));

  d[0][0][0] = 0;

  deque<int> qx,qy,qn;

  qx.pb(0),qy.pb(0),qn.pb(0);

  for (;!qx.empty();){
     int x = qx.front(), y = qy.front(), nap = qn.front();
     cerr << x <<" "<<y <<" "<<nap << endl;
     qx.pop_front();
     qy.pop_front();
     qn.pop_front();
     if (nap == 1){
        if (good(x+1,y) && d[x+1][y][nap] > d[x][y][nap]){
            d[x+1][y][nap] = d[x][y][nap];
            qx.push_front(x+1);
            qy.push_front(y);
            qn.push_front(nap);
        }
        if (good(x-1,y) && d[x-1][y][nap] > d[x][y][nap]){
            d[x-1][y][nap] = d[x][y][nap];
            qx.push_front(x-1);
            qy.push_front(y);
            qn.push_front(nap);
        }    
     }
     if (nap == 0){
        if (good(x,y+1) && d[x][y+1][nap]> d[x][y][nap]){
            d[x][y+1][nap] = d[x][y][nap];
            qx.push_front(x);
            qy.push_front(y+1);
            qn.push_front(nap);
        }
        if (good(x,y-1) && d[x][y-1][nap] > d[x][y][nap]){
            d[x][y-1][nap] = d[x][y][nap];
            qx.push_front(x);
            qy.push_front(y-1);
            qn.push_front(nap);
        }
     }

     if (c[x][y] == '#'){
        if (d[x][y][1-nap] > d[x][y][nap]+1){
            d[x][y][1-nap] = d[x][y][nap]+1;
            qx.pb(x);
            qy.pb(y);
            qn.pb(1-nap);
        }
     }
  }

  if (d[n-1][m-1][0] > n*m)
    printf("-1\n");
  else
    printf("%d\n",d[n-1][m-1][0]);        

  return 0;
}

