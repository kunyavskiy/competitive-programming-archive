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


const int MAXN = 1100;

vector<pair<int,int> > v;
bool used[MAXN];

map<int,vector<int> > poss;
ll cur;

bool luck(int x){
    while (x){
        if (x % 10 != 4 && x % 10 != 7)
            return false;
        x /= 10;
    }
    return true;
}

int n;

set<pair<int,int> > s;


ll get(ll len){
    return len*(len+1)/2;
}

void reset(){
    s.clear();
    s.insert(mp(0,v.back().first - 1));
    cur = get(v.back().first);
    memset(used,0,sizeof(used));     
}


void addpos(int pos){
    set<pair<int,int> > ::iterator iter = s.upper_bound(mp(pos,-1));
    if (iter == s.begin())
        return;
    --iter;
    assert(iter->first <= pos);
    if (iter->second < pos)
        return;
    int l = iter->first;
    int r = iter->second;
    s.erase(iter);
    cur -= get(r - l+1);
    cur += get(pos-l);
    cur += get(r-pos);
    if (pos > l)
        s.insert(mp(l,pos-1));
    if (pos < r)
        s.insert(mp(pos+1,r));
}

void addbef(int pos){
    addpos(pos);

    while (s.size() && s.begin()->first < pos){
        cur -= get(s.begin()->second - s.begin()->first);
        s.erase(s.begin());
    }
}



void addall(int x){
    vector<int> pos = poss[x];

    for (int i = 0; i < (int)pos.size(); i++){
        addpos(v[pos[i]+1].first);
        used[pos[i]+1] = true;
    }
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    

  scanf("%d",&n);
  for (int i = 0; i < n; i++){
    int a;
    scanf("%d",&a);
    if (luck(a)){
        v.pb(mp(i,a));
        poss[a].pb(i);
    }
  }

  v.pb(mp(n,0));
  reverse(v.begin(),v.end());
  v.pb(mp(-1,-1));
  reverse(v.begin(),v.end());


  ll ans = 0;
  cur = 0;

  for (int i = 1; i < (int)v.size()-1; i++){
    reset();
    for (int j = i; j < (int)v.size(); j++){
        ans = ans  + cur * (v[i].first - v[i-1].first) * 1LL * (v[j+1].first - v[j].first);
        cerr << i <<" "<<j<<" "<<cur << endl;
        if (!used[j])
            addall(v[j].first);
        addbef(v[j].first);
    }    
  }


  cout << ans << endl;



  return 0;
}

