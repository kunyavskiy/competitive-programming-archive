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

#define OK {printf("equal");return 0;}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	string s,t;
	cin >> s >> t;

	string p = (((string("")+t[0])+t[1])+t[2])+t[3];

	for (int i = 0; i < 3; i++){
		if (s == p)
			OK;
		rotate(p.begin()+1,p.begin()+2,p.begin()+4);
	}



	p = (((string("")+t[1])+t[3])+t[2])+t[0];

	for (int i = 0; i < 3; i++){
		if (s == p)
			OK;
		rotate(p.begin()+1,p.begin()+2,p.begin()+4);
	}



	p = (((string("")+t[2])+t[1])+t[3])+t[0];

	for (int i = 0; i < 3; i++){
		if (s == p)
			OK;
		rotate(p.begin()+1,p.begin()+2,p.begin()+4);
	}



	p = (((string("")+t[3])+t[2])+t[1])+t[0];

	for (int i = 0; i < 3; i++){
		if (s == p)
			OK;
		rotate(p.begin()+1,p.begin()+2,p.begin()+4);
	}


	printf("different\n");
  return 0;
}