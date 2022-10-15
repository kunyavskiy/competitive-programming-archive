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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int t;
	scanf("%d",&t);
	for (int i = 0; i < t; i++){
		int a,b;
		cin >> a >> b;
		if (b % a == 0){
			b /= a;
			int cnt = 1;
			for (int i = 2; i*i <= b; i++)
				while (b % i == 0)
					b /= i,cnt++;
			if (b != 1)
				cnt++;
			cout << cnt << endl;	
		}
		else {
			cout << 0 << endl;
		}

	}
  return 0;
}