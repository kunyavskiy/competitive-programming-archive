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

bool can[2][11000];
int last[11000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin >> n;
	for (int i = 0; i<n; i++){
		int a;
		cin >> a;
//		cerr << a <<endl;
		if (!can[0][a%n]){
			can[1][a%n] = true;
			last[a%n] = a;
		}
		int j = a%n;
		for (int i = 0; i < n; i++){
			if (can[0][i] && !can[0][j]){
//				cerr << i <<" -> "<<j<<endl;
				can[1][j] = true;
				last[j] = a;
			}
			++j;
			if (j == n)
				j = 0;

		}
		for (int i = 0; i < n; i++){
			can[0][i] |= can[1][i],can[1][i] = 0;
//			cerr << can[0][i] <<"/"<<last[i] << "/"<<(i-last[i]+n*10)%n<<" ";
		}                          
//		cerr << endl;
	}

	if (can[0][0] == 0){
		printf("0\n");
		return 0;
	}

	int a = 0;
	vector<int> ans;

	do {
		ans.pb(last[a]);
		a -= last[a];       
        while (a < 0)
        	a += 10000*n;
        a %= n;
	}while(a);

	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] <<endl;
  return 0;
}