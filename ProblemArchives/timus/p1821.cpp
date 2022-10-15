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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char s[1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    vector<string> v;

    int n;
    scanf("%d",&n);

    int best = 1<<30;

    vector<pair<pair<int,int> ,string> > sp;

    for (int i = 0; i < n; i++){
    	int a,b,c;
    	scanf(" %s %d:%d.%d",s,&a,&b,&c);
    	int t = (a*60 + b)*10 + c;
    	int t1 = t+ 300*i;
    	sp.pb(mp(mp(t1,t),s));
    }

    sort(sp.begin(),sp.end());
    
    for (int i = 0; i < n; i++){
    	if (sp[i].first.second < best){
    		best = sp[i].first.second;
    		v.pb(sp[i].second);
    	}
    }

    sort(v.begin(),v.end());

    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++)
    	cout << v[i] << endl;

  return 0;
}