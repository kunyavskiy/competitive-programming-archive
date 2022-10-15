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


const int MAXN = 151000;
pair<int,int> a[MAXN];

bool cmp(const pair<int,int>& a,const pair<int,int>& b){
	return a.second > b.second;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
		scanf("%d %d",&a[i].first,&a[i].second);
	stable_sort(a,a+n,cmp);
	for (int i = 0; i < n; i++)
		printf("%d %d\n",a[i].first,a[i].second);
    return 0;
}