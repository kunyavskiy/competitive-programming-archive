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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;



vector< pair< int, pair<int,int> > > evs;

void change(set<int,greater<int> >& s,int a){
	if (s.find(a) == s.end())
		s.insert(a);
	else
		s.erase(a);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  evs.pb(mp(0,mp(-1,0)));
  evs.pb(mp(1000000000,mp(-1,0)));
  evs.pb(mp(0,mp(-2,1)));
  evs.pb(mp(1000000000,mp(-2,1)));


  scanf("%d",&n);

  for (int i = 0; i < n; i++){
  	int a,b;
  	char c;
  	scanf("%d %d %c",&a,&b,&c);
  	evs.pb(mp(a,mp(i,c=='b')));
  	evs.pb(mp(b,mp(i,c=='b')));
  }

  sort(evs.begin(),evs.end());

  set<int, greater<int> > s[2];

  int last = 1<<30;
  int ans = 0;
  int ansi=0,ansj = 0;

  n = evs.size();

  for (int i = 0; i < n;){
  	//if (i)
	 // 	cerr << evs[i].first <<" "<<last << " "<<*s[0].begin()<<" "<<*s[1].begin()<<endl;
  	int j = i;
  	for (;evs[j].first == evs[i].first; j++)
  		change(s[evs[j].second.second],evs[j].second.first);
  	if (ans < evs[i].first - last){
		ans = evs[i].first - last;
		ansi = last;
		ansj = evs[i].first;
	}
  	if ((j == n || *s[0].begin() > *s[1].begin())){
  		if (last == (1<<30))
			last = evs[i].first;  	
	}
  	else 
  		last = 1<<30;  	
  	i = j;
  }

  cout << ansi<<" "<<ansj << endl;
  return 0;
}