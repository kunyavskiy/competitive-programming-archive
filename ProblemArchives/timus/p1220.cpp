#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <bitset>
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

typedef unsigned long long ll;
typedef long double ld;


int val[100000];         
bitset<1700000> s;
int h[1000];




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

//  cerr << (sizeof(s)+sizeof(val))/1024.0/1024 << endl;

  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
  	int a,b;
  	if (scanf(" PUSH %d %d",&a,&b) == 2){
  		--a;               
  		val[i] = b;              
  		for (int j = 0; j < 17; j++)
  			if (h[a] & (1<<j))
  				s.set(17*i+j);
  		h[a] = i;
  	}
  	else {
  		scanf(" OP %d",&a);
  		--a;
  		printf("%d\n",val[h[a]]);
  		int tmp = h[a];
  		h[a] = 0;
  		for (int j = 0; j < 17; j++)
  			h[a] |= (s.test(17*tmp+j))<<j;
  	}
  }

  return 0;
}