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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	ld x,y;
	x = y = 0;
	for (char c; cin >> c;){
		if (c == '0')
			break;
		switch (c){
			case '1': x -= sqrt(0.5), y -= sqrt(0.5);
						break;
			case '2': y -= 1;
						break;
			case '3': x += sqrt(0.5), y -= sqrt(0.5);
						break;
			case '4': x -= 1;
						break;
			case '5': ;
						break;
			case '6': x += 1;
						break;
			case '7': x -= sqrt(0.5), y += sqrt(0.5);
						break;
			case '8': y += 1;
						break;
			case '9': x += sqrt(0.5), y += sqrt(0.5);
						break;
		}
	}

	cout.precision(15);
	cout << fixed << x << " "<<y<<endl;
  return 0;
}