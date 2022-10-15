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

char s[100][100];
int n,m;

void recolor(int x,int y,char f,char t){
    if (x < 0 || y < 0 || x >= n || y >= m ||s[x][y] != f)
        return;
    s[x][y] = t;
    recolor(x+1,y,f,t);
    recolor(x-1,y,f,t);
    recolor(x,y-1,f,t);
    recolor(x,y+1,f,t);
    return;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c",&s[i][j]);

    int k;
    scanf("%d",&k);

    for (int i = 0; i < k; i++){
        int x;
        scanf("%d",&x);
        if (i&1)
            recolor(0,m-1,s[0][m-1],x+'0');
        else
            recolor(n-1,0,s[n-1][0],x+'0');

        //for (int i = 0; i < n; i++)
        //    cerr << s[i] << endl;
        //cerr<<endl<<endl;
    }

    recolor(0,m-1,s[0][m-1],'!');
    recolor(n-1,0,s[n-1][0],'?');

    int cnt1,cnt2;

    cnt1 = cnt2 = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (s[i][j] == '!')
                cnt2++;
            else if (s[i][j] == '?')
                cnt1++;

    cout << cnt1 << endl << cnt2 << endl;

    return 0;
}