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

int d[110][110];
int p[110][110];
int p2[110][110];
bool inq[110][110];

char s[110][110];
int len[110];
int n;

queue< pair<int,int> > q;


string res1,res2;

void gen(int x,int y){
    if (p[x][y] == -1){
        res1 = s[x];
        return;
    }

    if (len[p[x][y]] <= y)
        gen(p2[x][y], y - len[p[x][y]]);
    else 
        gen(p2[x][y], len[p2[x][y]] - y);    

    if (res1.size() <= res2.size())
        res1 += s[p[x][y]];
    else
        res2 += s[p[x][y]];
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf(" %s",s[i]);
        len[i] = strlen(s[i]);
    }

    memset(d,63,sizeof(d));

    for (int i = 0; i < n; i++){
        d[i][0] = 0;
        p[i][0] = p2[i][0] = -1;
        inq[i][0] = 1;
        q.push(mp(i,0));
    }

    while (!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();


        inq[x][y] = 0;


        for (int j = 0; j < n; j++){
            if (y == 0 && x == j) continue;

            bool Q = true;

            for (int k = 0; y + k < len[x] && k < len[j] && Q; k++)
                Q &= s[x][y+k] == s[j][k];

            if (!Q) continue;

            int nx,ny,nd = d[x][y];
            if (len[j] + y > len[x]) {
                nx = j;
                ny = len[x] - y;
                nd += ny;
            } else {
                ny = y + len[j];
                nx = x;
            }


            if (d[nx][ny] > nd){
                d[nx][ny] = nd;
                p[nx][ny] = j;
                p2[nx][ny] = x;
                if (!inq[nx][ny])
                    q.push(mp(nx,ny)),inq[nx][ny] = 1;
                
                if (ny == len[nx]){
                    res1 = res2 = "";
                    gen(nx,ny);
                    assert(res1 == res2);
                    puts("YES");
                    puts(res1.data());
                    return 0;
                }
            }
        }
    }

    printf("NO\n");
    return 0;
}