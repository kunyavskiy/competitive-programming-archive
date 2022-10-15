#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define SZ(a) (int)(a.size())

#define sinf sinf_nklbggl

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "k"

const int inf = 1000000000;
const ld eps = 1e-9;

string sinf,sinf2;

vector<int> g[450];
vector<int> l[450];
vector<string> gs[450];
bool fin[450];
int d[450];
string ans[450];
string s[25];
int num[25][25];
int n;
int ptr;
int anslen;




void dijkstra(){
	set<pair<int,int> > s;
	s.insert(mp(0,0));

	for (;s.size();){
		int v = s.begin()->second;
		s.erase(s.begin());


		for (int i = 0; i < (int)g[v].size(); i++){		
			int to = g[v][i];
			if (d[to] > d[v] +l[v][i]){
				s.erase(mp(d[to],to));
				d[to] = d[v] + l[v][i];
				s.insert(mp(d[to],to));
			}
		}
	}
}


string gen(int v){
//	cerr << v << " "<<ans[v] <<" "<<d[v]<<" "<<anslen<<endl;
	if (d[v] > anslen)
		return sinf;
	if (ans[v] != sinf)
		return ans[v];

	ans[v] = sinf2;
	for (int i = 0; i < (int)g[v].size(); i++){
		int to = g[v][i];
		if (d[to] != d[v] + l[v][i])
			continue;
		string temp = gen(to);
		if (temp == sinf || temp == sinf2)
			continue;
		temp = gs[v][i] + temp;
		ans[v] = min(ans[v],temp);
	}

	return ans[v];
}

bool check(int id1,int suff,int id2){
	for (int i = 0; i+suff < (int)s[id1].size() && i < (int)s[id2].size(); i++)
		if (s[id1][i+suff] != s[id2][i])
			return false;
	return true;
}

pair<int,string> get(int id1,int suff,int id2){
	pair<int,string> res;
    if (suff + SZ(s[id2]) <= SZ(s[id1])){
    	res.first = num[id1][suff+SZ(s[id2])];
    	res.second = "";
    	return res;
    }
//    cerr << s[id1] <<" "<<SZ(s[id1]) << endl;
  //  cerr << s[id2] <<" "<<SZ(s[id2]) << endl;
    int t = SZ(s[id1]) -suff ;
//    cerr <<id1 <<" "<<suff <<" "<<id2 <<"     :    "<<t<<endl;
    res.first = num[id2][t];
    res.second = string(s[id2].begin()+t,s[id2].end());
    return res;
}


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  getline(cin,s[0]);
  sscanf(s[0].data(),"%d",&n);

  for (int i = 0; i < n; i++)
  	getline(cin,s[i]);

  ptr = 1;

  for (int i = 0; i < n; i++){
  	 for (int j = 0; j <= (int)s[i].size(); j++){
  	 	num[i][j] = ptr++;
//  	 	cerr << i <<" "<<j<<" "<<num[i][j] <<endl;
  	 }
  	 g[0].pb(num[i][0]);
  	 l[0].pb(s[i].size());
  	 gs[0].pb(s[i]);
	 fin[num[i][s[i].size()]] = true;
  }


//  get(3,5,0);
//  return 0;

  for (int i = 0; i < n; i++)
  	for (int j = 0; j < (int)s[i].size(); j++){
  		
	  	for (int k= 0; k < n; k++)
	  		if (check(i,j,k)){
	  			if (i == k && j == 0)
	  				continue;
	  			//cerr <<"!!!"<<i<<" "<<j<<" "<<k<<endl;
	  			pair<int,string> temp = get(i,j,k);
	  			g[num[i][j]].pb(temp.first);
	  			l[num[i][j]].pb(s[k].size());
	  			gs[num[i][j]].pb(temp.second);
	  		}	  				  	
  	}

  
  n = ptr;

  /*for (int i = 0; i < n; i++,cerr<<endl){
  	cerr << i<<" " <<fin[i] <<" : ";
  	for (int j = 0; j < (int)g[i].size(); j++)
  		cerr <<"("<<g[i][j]<<" "<<gs[i][j]<<" "<<l[i][j]<<") ";
  }
  cerr<<endl;*/

  sinf = "1";sinf[0] = 127;
  sinf2 = sinf+sinf;

  for (int i = 0; i < n; i++){
  	d[i] = inf;
  	ans[i] = sinf;
  	if (fin[i])
  		ans[i] = "";
  }
  d[0] = 0;

  dijkstra();

  anslen = inf;
  for (int i = 0; i < n; i++)
  	if (fin[i])
  		anslen = min(anslen,d[i]);

  cout << anslen/2 <<endl;

  cerr << gen(2) << endl;
  puts(gen(0).data());
  return 0;
}

