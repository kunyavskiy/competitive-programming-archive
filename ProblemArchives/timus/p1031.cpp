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

ll l1,l2,l3;
ll c1,c2,c3;
ll p1,p2,p3;

int a[110000];
ll d[110000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	cin >> l1 >> l2 >> l3;
  	cin >> c1 >> c2 >> c3;

  	int n;
  	scanf("%d",&n);
  	
  	int A,b;
  	scanf("%d %d",&A,&b);

  	if (A > b)
  		swap(A,b);

  	for (int i = 0; i < A-1; i++)
  		scanf("%d",&a[0]);
  	b -= A;

  	for (int i = 1; i <= b; i++){
  		scanf("%d",&a[i]);
  		while (a[p1] < a[i] - l1)
  			p1++;
  		while (a[p2] < a[i] - l2)
  			p2++;
  		while (a[p3] < a[i] - l3)
  			p3++;
  		d[i] = 1000000100;	
  		d[i] = min(d[p1] + c1, min(d[p2] + c2, d[p3] + c3));
  	}

  	cout << d[b] << endl;
  return 0;
}