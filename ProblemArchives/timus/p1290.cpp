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

int a[26000],b[26000];


int convert(int n,int* a,int* b){
	int cnt = 0;
	int val = 0;

	sort(a,a+n);


	for (int ptr = 0; ; val++){
		while (ptr < n && a[ptr] <= val)
			++ptr;
		if (ptr != n)
			b[cnt++] = n - ptr;
		else
			break;
	}

	return cnt;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n,cnt;
  	cin >> n;
  	cnt = 0;
  	for (int i = 0; i < n; i++)
  		cin >> a[i];

  	n = convert(n,a,b);
  	n = convert(n,b,a);

//  	cerr <<"!!!!!!"<<n<<endl;

  	for (int i = 0; i < n; i++)
  		cout << a[i] <<"\n";  
  return 0;
}