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

int n;
int a[2100];
int l[2100];
int r[2100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&a[i]);

  	for (int i = 0; i < n; i++){
  		l[a[i]-1] = 1;
  		r[a[i]-1] = n;
  		for (int j = 0; j < i; j++)
  			if (a[j] > a[i])
  				l[a[i]-1]++;
  		for (int j = i+1; j < n; j++)
  			if (a[i] > a[j])
  				r[a[i]-1] --;
  	}

  	for (int i = 0; i < n; i++)
  		printf("%d %d\n",l[i],r[i]);

	
  return 0;
}