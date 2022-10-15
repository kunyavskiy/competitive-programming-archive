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
	int n;
	cin >> n;
	if (n * 6 > 100000){
		cout << "TOO LONG" << endl;
		return 0;
	}


	for (int i = 0; i < n; i++)
		printf("%c","abc"[i%3]);
	puts("");

	if (n > 1)
	for (int i = 0; i < n; i++)
		printf("%c","acb"[i%3]);
	puts("");

	for (int i = 0; i < n; i++)
		printf("%c","bac"[i%3]);
	puts("");

	if (n > 1)
	for (int i = 0; i < n; i++)
		printf("%c","bca"[i%3]);
	puts("");


	for (int i = 0; i < n; i++)
		printf("%c","cab"[i%3]);
	puts("");

	if (n > 1)
	for (int i = 0; i < n; i++)
		printf("%c","cba"[i%3]);
	puts("");

  return 0;
}