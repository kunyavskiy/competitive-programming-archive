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
typedef double ld;

ld v1,v2;

ld g[210][210];

int n;
ld x[210];
ld y[210];

double d[210];
double d2[210];
int p[210];
bool u[210];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%lf %lf",&v1,&v2);
    scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%lf %lf",&x[i],&y[i]);

  	for (int i = 0; i < n; i++)
	  	for (int j = 0; j < n; j++)
	  		g[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]))/v1;
  		
	while (true){
		int i,j;
		scanf("%d %d",&i,&j);
		if (i == 0 && j == 0) break;
		--i,--j;
		g[i][j] = g[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]))/v2;
	}

	scanf("%lf %lf",&x[n],&y[n]);
	scanf("%lf %lf",&x[n+1],&y[n+1]);
	n += 2;

  	for (int i = n-2; i < n; i++)
	  	for (int j = 0; j < n; j++)
	  		g[i][j] = g[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]))/v1;

	memset(p,-1,sizeof(p));

	int from,to;
	from = n-2;
	to = n-1;


	p[from] = from;
	for (int i = 0; i < n; i++)
		d[i] = 1e100;
	d[from] = 0;

	for (int i = 0; i < n; i++){
		int id = min_element(d,d+n) - d;
		u[id] = true;
		for (int j = 0; j < n; j++)
			if (!u[j] && d[j] > d[id] + g[id][j]){
				d[j] = d[id] + g[id][j];
				p[j] = id;
			} 
		d2[id] = d[id];
		d[id] = 1e100;
	}


	vector<int> v;
		while (from != to){
		v.pb(p[to]);
		to = p[to];
	}

	v.pop_back();
	reverse(v.begin(),v.end());

	cout.precision(15);
	cout << fixed << d2[n-1] << endl;
	cout << v.size();
	for (int i = 0; i < (int)v.size(); i++)
		cout <<" "<<v[i]+1;
	cout << endl;


    return 0;
}