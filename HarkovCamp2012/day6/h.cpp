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
#define sz(a) (int)(a.size())

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
typedef unsigned char uchar;


#define taskname "h"

const int inf = 1000000000;
const ld eps = 1e-9;
const ull P = 239017ULL;
const int MAXN = 310000;


char s[MAXN];
ull hash[MAXN];
ull rhash[MAXN];
ull stP[MAXN];



ull inv(ull A){
    ull B = 1;
	for (int i = 0; i < 63; i++){
		B = B * A;
		A = A * A;
	}
	return B;
}

struct mymap {
	map<ull,int> m;
	ull A,B;

	void add(ull h,int ver){
		h = (h - B) * inv(A);
		m[h] = ver;
	}

	int find(ull h){
		//cerr << "!!!!"<<h <<endl;
		h = (h - B) * inv(A);
		//cerr << "!!!!"<<h <<endl;
		if (m.find(h) == m.end())
			return -1;
		return m[h];
	}

	void merge(mymap&,int);

	void print(){
		cerr << A<<" "<<B<<"       ";
		for (map<ull,int>::iterator iter = m.begin(); iter != m.end(); ++iter)
			cerr << "("<<iter->first <<" "<<iter->second<<") ";
		cerr<<endl<<endl;
	}                                                        
};

mymap res[MAXN];
vector<int> g[MAXN];
vector<char> gc[MAXN];
int h[MAXN];
int n;
int len;

void dfs(int v,int p,int h){
//	cerr << v<<endl;
	::h[v] = h;
	res[v].add(0ULL,v);
	res[v].A = 1;
	for (int i = 0; i < (int)g[v].size(); i++){
		int to = g[v][i];
		if (to == p)
			continue;
		dfs(to,v,h+1);
		res[to].B = res[to].B*P+(ull)(uchar)gc[v][i];
		res[to].A = res[to].A*P;
		res[v].merge(res[to],v);
	}
}

void calchash(){
	stP[0] = 1;
	for (int i = 1; i < MAXN; i++)
		stP[i] = stP[i-1]*P;

	for (int i = 1; i <= len; i++)
		hash[i] = hash[i-1]*P + ((ull)(uchar)s[i-1]);
	for (int i = 1; i <= len; i++)
		rhash[i] = rhash[i-1]*P + ((ull)(uchar)s[len-i]);
}

void mymap::merge(mymap& r,int root){
//	cerr << "MERGE"<<endl;
//	print();
//	r.print();
	if (m.size() < r.m.size()){
		m.swap(r.m);
		swap(A,r.A);
		swap(B,r.B);
	}

	for (map<ull,int>::iterator iter = r.m.begin(); iter != r.m.end(); ++iter){
		ull H = iter->first;
		int v = iter->second;
		H = (H*r.A+r.B);
		int l1 = h[v] - h[root];
		//cerr << H<<" "<<l1<<endl;
		if (l1 <= len && hash[l1] == H){
			//cerr << rhash[len-l1] << endl;
			int temp = find(rhash[len-l1]);
		//	cerr << temp << endl;
			if (temp != -1){
				printf("YES\n");
				printf("%d %d\n",v+1,temp+1);
				exit(0);
			}
		}

		if (l1 <= len && rhash[l1] == H){
			int temp = find(hash[len-l1]);
			if (temp != -1){
				printf("YES\n");
				printf("%d %d\n",temp+1,v+1);
				exit(0);
			}
		}
	}
	for (map<ull,int>::iterator iter = r.m.begin(); iter != r.m.end(); ++iter){
		ull H = iter->first;
		int v = iter->second;
		H = (H*r.A+r.B);
		add(H,v);	
	}	
//	print();
//	cerr << "/MERGE"<<endl;		
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  gets(s);
  len = strlen(s);
  calchash();

  scanf("%d",&n);

  for (int i = 0; i < n-1; i++){
  	int a,b; char c;
  	scanf("%d %d %c",&a,&b,&c);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  	gc[a].pb(c);
  	gc[b].pb(c);
  }

  dfs(0,-1,0);
  printf("NO\n");
  return 0;
}

