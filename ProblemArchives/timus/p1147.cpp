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

struct event{
    int lx,rx;
    int y;
    int tp;
    int color;
    int t;
    bool operator<(const event& a) const{
        return y < a.y;
    }
    event(int lx,int rx,int y,int tp,int color,int t):lx(lx),rx(rx),y(y),tp(tp),color(color),t(t) {
    }
    event(){
    }
};

event evs[2100];
int xs[2100];
int ptr,xptr;

int n;

int ans[3000];

int RY[3000];
int CL[3000];


void solve(int l,int r){
    vector<pair<int,int > > ev;


    for (int i = 0; i < ptr; i++)
        if (evs[i].lx <= l && r <= evs[i].rx)
            ev.pb(mp(evs[i].y,evs[i].t));

    priority_queue<int> q;

    for (int i = 0; i < (int)ev.size(); i++){
        if (i){
            while (!q.empty() && RY[q.top()] < ev[i].first)
                q.pop();
            assert(!q.empty());
            ans[CL[q.top()]] += (ev[i].first - ev[i-1].first) * (r-l);               
        }
        q.push(ev[i].second);
    }
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    {
       int a,b;
       scanf("%d %d",&a,&b);
       evs[ptr++] = event(0,a,0,1,1,0);
       evs[ptr++] = event(0,a,b,-1,1,0);
       RY[0] = b;
       CL[0] = 1;
       xs[xptr++] = 0;
       xs[xptr++] = a;
    }



    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        int lx,ly,rx,ry,c;
        scanf("%d %d %d %d %d",&lx,&ly,&rx,&ry,&c);
        RY[i+1] = ry;
        CL[i+1] = c;
        xs[xptr++] = lx;
        evs[ptr++] = event(lx,rx,ly,1,c,i+1);
        xs[xptr++] = rx;
        evs[ptr++] = event(lx,rx,ry,-1,c,i+1);
    }

    sort(evs,evs+ptr);
    sort(xs,xs+xptr);
    xptr = unique(xs,xs+xptr) - xs;

    for (int i = 1; i < xptr; i++)
        solve(xs[i-1],xs[i]);

    for (int i = 0; i <= 2500; i++)
        if (ans[i])
            printf("%d %d\n",i,ans[i]);

    return 0;
}