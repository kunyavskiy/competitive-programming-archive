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

int g[45][45][45][45];
int used[20*20*20],usedit;
int n,m;
char s[45][45];

void calc(int lx,int rx,int ly,int ry){
    ++usedit;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (lx < i-j+21 && i-j+21< rx && ly < i+j+1 && i+j+1 < ry){
                if (s[i][j] == 'L')
                    used[g[lx][rx][ly][i+j+1] ^ g[lx][rx][i+j+1][ry]] = usedit;
                else if (s[i][j] == 'R')
                    used[g[lx][i-j+21][ly][ry] ^ g[i-j+21][rx][ly][ry]] = usedit;
                else if (s[i][j] == 'X')
                    used[
                           g[lx][i-j+21][ly][i+j+1] ^
                           g[lx][i-j+21][i+j+1][ry] ^
                           g[i-j+21][rx][ly][i+j+1] ^
                           g[i-j+21][rx][i+j+1][ry]   
                        ] = usedit;
            }
                                                                
    int& ans = g[lx][rx][ly][ry];
    for (;used[ans] == usedit; ans++);             
   // if (19 <= lx && rx <= 23 && 0 <= ly && ry <= 4)
     //   cerr << lx <<" "<<rx <<" "<<ly <<" "<<ry <<" "<<ans << endl;
}


int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c ",&s[i][j]);
    for (int i = 0; i < 44; i++)
        for (int j = 0; j < 44; j++)
            for (int di = 0; i+di < 44; di++)
                for (int dj = 0; i+dj < 44; dj++)
                    calc(i,i+di,j,j+dj);
    int temp = g[0][43][0][43];
    if (temp == 0)
      cout << "LOSE" << endl;
    else
      cout << "WIN" << endl;    
  return 0;
}