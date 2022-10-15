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

char buf[1000];
char buf2[1000];
set<string> f;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	gets(buf);
  	int Y,n,q;
  	sscanf(buf,"%d %d %d",&Y,&n,&q);

  	for (int i = 0; i < n; i++){
  		gets(buf);
  		sscanf(buf,"%[^#]",buf2);
  		string tmp = buf2;
  		if (f.find(tmp) == f.end())
  		{
  			--q;
  			if (q == -1){
  				puts(buf);
  				return 0;
  			}
  			f.insert(tmp);
  		}
  	}

  	assert(false);


  return 0;
}