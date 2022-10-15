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

ld det(ld a,ld b,ld c,ld d){
	return a*d - b*c;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	ld c1,c2,c3,c4,c5;
	c1 = c2 = c3 = c4 = c5 = 0;
	int n;
	scanf("%d",&n);

	for (int i = 0; i < n; i++){
		ld b; cin >> b;
		c1 += 1.0;
		c2 += i*i;
		c3 += 2.0*i;
		c4 += -2.0*b;
		c5 += -2.0*b*i;

//		cerr << c1 <<" "<<c2 <<" "<<c3 <<" "<<c4 <<" "<<c5 << endl;
	}

	c1 *= 2, c2 *= 2;

//	cerr << c1 <<" "<<c2 <<" "<<c3 <<" "<<c4 <<" "<<c5 << endl;

	ld a = det(-c4,c3,-c5,c2)/ det(c1,c3,c3,c2);
	ld d = det(c1,-c4,c3,-c5)/ det(c1,c3,c3,c2);

	cout.precision(15);
	cout << fixed <<a <<" "<<d<<endl;
  return 0;
}