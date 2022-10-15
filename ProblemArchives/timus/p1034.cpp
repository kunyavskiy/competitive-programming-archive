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

int usex[110];
int usey[110];
int uses[110];
int used[110];


int have[110][110];
int rem[110][110];

int n;
int ans;


int x[110];
int y[110];

void go(int x,int y,int cnt1,int cnt2){
    if (x == n){
        ans += cnt1 == 3 && cnt2 == 3;
        return;
    }
    if (y == n){
        go(x+1,0,cnt1,cnt2);
        return;
    }
    if (cnt1 > 3 || cnt2 > 3)
        return;
    if (cnt1 + (n-x) < 3)
        return;

    if (!usex[x] && !usey[y] && !uses[x+y] && !used[x-y+50] && (cnt1 < 3 || have[x][y])){
        usex[x] = usey[y] = uses[x+y] = used[x-y+50] = true;

        int _cnt = cnt2;  

        /*for (int i = x; i < n && _cnt <= 3; i++)
            for (int j = ((i==x)?(y+1):0); j < n && _cnt <= 3; j++)
                if (have[i][j] && (usex[i] || usey[j] || uses[i+j] || used[i-j+50]))
                    _cnt++; */

        for (int k = 0; k < n && _cnt <= 3; k++)
            if (mp( ::x[k], ::y[k]) > mp(x,y) && (usex[ ::x[k]] || usey[ ::y[k]] || uses[ ::x[k] + ::y[k]] || used[ ::x[k] - ::y[k] + 50]))
                _cnt++;

        if (_cnt <= 3) {
            go(x,y+1,cnt1 + !have[x][y],cnt2);
        }
        usex[x] = usey[y] = uses[x+y] = used[x-y+50] = false;
                           
    }
    go(x,y+1,cnt1,cnt2 + have[x][y]);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d",&n);

  for (int i = 0; i < n; i++){
    int x,y;
    scanf("%d %d",&x,&y);
    --x,--y;
    ::x[i] = x;
    ::y[i] = y;
    have[x][y] = true;
  }

  go(0,0,0,0);  

  cout << ans << endl;
  return 0;
}