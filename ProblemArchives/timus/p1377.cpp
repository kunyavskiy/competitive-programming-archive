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

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

int id[110][110];
int n,m;


bool good(int x,int y){
    return 0 <= x && x< n && 0 <= y && y < m && id[x][y] == -1;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(id,-1,sizeof(id));

    scanf("%d %d",&n,&m);

    int ptr = 0;

    int nap = 0;
    int x,y;
    x = y = 0;

    id[x][y] = ptr++;

    while (ptr < n*m){

        for (;good(x+dx[nap],y+dy[nap]);){
            x += dx[nap];
            y += dy[nap];
            id[x][y] = ptr++;
        }

        nap = (nap+1)%4;
    }

    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;

    --x1,--y1,--x2,--y2;

    cout << abs(id[x1][y1] - id[x2][y2]) << endl;

    return 0;
}