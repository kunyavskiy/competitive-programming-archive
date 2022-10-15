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

struct segment{
    ll x1,y1,x2,y2;
    segment(){
        x1 = y1 = x2 = y2 = 0;
    }
};

vector<segment> ss;

int solve(segment s){
  vector<pair<ll,int> > v;
  ll l,r;
  l = r = -1;
  if (s.x1 > s.x2)
    swap(s.x1,s.x2);
  if (s.y1 > s.y2)
    swap(s.y1,s.y2);

  if (s.x1 == s.x2){
    l = s.y1;
    r = s.y2;

    for (int i = 0; i < (int)ss.size(); i++){
        if (ss[i].x1 == ss[i].x2 && ss[i].x1 == s.x1){
            v.pb(mp(ss[i].y1,1));            
            v.pb(mp(ss[i].y2+1,-1));
        }
        if (ss[i].x1 != ss[i].x2 && (ss[i].x1 <= s.x1 && s.x1 <= ss[i].x2)){
            v.pb(mp(ss[i].y1,1));
            v.pb(mp(ss[i].y1+1,-1));
        }
    }    
  }  

  if (s.y1 == s.y2){
    l = s.x1;
    r = s.x2;

    for (int i = 0; i < (int)ss.size(); i++){
        if (ss[i].y1 == ss[i].y2 && ss[i].y1 == s.y1){
            v.pb(mp(ss[i].x1,1));            
            v.pb(mp(ss[i].x2+1,-1));
        }
        if (ss[i].y1 != ss[i].y2 && (ss[i].y1 <= s.y1 && s.y1 <= ss[i].y2)){
            v.pb(mp(ss[i].x1,1));
            v.pb(mp(ss[i].x1+1,-1));
        }
    }    
  }  

  ss.pb(s);

  v.pb(mp(-(1LL<<60),0));
  v.pb(mp((1LL<<60),0));

  sort(v.begin(),v.end());

  ll ans = 0;

  int cur = 0;

 // for (int i = 0; i < (int)v.size(); i++)
 //   cerr << v[i].first <<" "<<v[i].second << endl;
  //cerr<<endl;

  for (int i = 0; i < (int)v.size(); ){
    if (cur == 0 && i){
   //     cerr << min(v[i].first,r+1) <<" "<<max(v[i-1].first,l) << endl;
        ans += max(0LL,min(v[i].first,r+1) - max(v[i-1].first,l));
    }
    int j = i;
    for (; j < (int)v.size() && v[j].first == v[i].first; j++)
        cur += v[j].second;
    i = j;
  }

  return ans;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  int t;

  scanf("%d",&t);

  ll curx,cury;
  curx = cury = 0;

  ss.pb(segment());

  for (int i = 0; i < t; i++){
    char c;int len;
    scanf(" %c %d",&c,&len);
    segment seg;
    seg.x1 = curx, seg.y1 = cury;

    if (c == 'U')
        curx += len;
    else if (c == 'D')
        curx -= len;
    else if (c == 'L')
        cury -= len;
    else if (c == 'R')
        cury += len;

    seg.x2 = curx, seg.y2 = cury;
    printf("%d\n",solve(seg));
  }




  return 0;
}

