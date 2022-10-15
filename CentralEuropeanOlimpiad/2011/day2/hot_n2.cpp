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

typedef long long int64;
typedef long double ld;

const int MAXN = 510000;

int rcost[MAXN];
int pcost[MAXN];
int size[MAXN];
int nsize[MAXN];
int n,m;

pair<int,int> temp[MAXN];

bool cmpsec(const pair<int,int>& a,const pair<int,int>& b){
	if (a.second != b.second)
		return a.second < b.second;
	return a.first < b.first;
}

bool cmpfirst(const pair<int,int>& a,const pair<int,int>& b){
	if (a.first != b.first)
		return a.first < b.first;
	return a.second < b.second;
}

void read(int n,int* cost,int* size,bool sec){
	for (int i=0;i<n;i++)
		scanf("%d %d",&temp[i].second,&temp[i].first);
	sort(temp,temp+n,sec?cmpsec:cmpfirst);
	for (int i=0;i<n;i++){
		cost[i] = temp[i].second;
		size[i] = temp[i].first;
	}
}

int ptr[MAXN];
bool usedp[MAXN];
bool usedr[MAXN];

int get(){
	for (int i=0;i<m;i++){
		while (ptr[i] < n && (usedr[ptr[i]] || size[ptr[i]] < nsize[i]))
			ptr[i]++;
	}
	
//	cerr << ptr[0] <<" "<<ptr[1] << endl;
	
//	cerr << pcost[0] - rcost[ptr[0]] << " " << pcost[1] - rcost[ptr[1]] << endl;
//	cerr << used
	
	int bestf = 0;
	for (int i=0;i<m;i++)
		if (ptr[i] < n && !usedp[i])
			bestf = max(bestf,pcost[i] - rcost[ptr[i]]);

//	cerr << bestf << endl;	
		
	for (int i=0;i<m;i++)
		if (ptr[i] < n && (bestf == pcost[i] - rcost[ptr[i]]) && !usedp[i]){
			usedp[i] = true;
			usedr[ptr[i]] = true;
			break;
		}
	return bestf;					
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.a","w",stdout);
  #endif
	int o;
	scanf("%d %d %d",&n,&m,&o);
	read(n,rcost,size,true);
	read(m,pcost,nsize,false);
	
	int64 ans = 0;
	
	for (int i=0;i<o;i++)
		ans += get();
	
	cout << ans << endl;
		
	return 0;
}