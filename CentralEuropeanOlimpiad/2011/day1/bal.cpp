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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 210000;

ld x[MAXN];
ld r[MAXN];

ld a[MAXN];
ld b[MAXN];
ld c[MAXN];
ld t[MAXN];
int ptr;

inline ld get(ld x){
	if (ptr == 0)
		return 1e100;
	return (a[ptr-1]*x)*x+b[ptr-1]*x+c[ptr-1];
}

inline void pop(ld x){
	while (ptr && t[ptr-1] <= x)
		--ptr;
}

inline void push(ld A,ld B,ld C){
	while (ptr){
		if (a[ptr-1] >= A){
			--ptr;
			continue;
		}
		ld da = A - a[ptr-1];
		ld db = B - b[ptr-1];
		ld dc = C - c[ptr-1];
		ld root = (-db + sqrt(db*db - 4*da*dc))/(2*da);
	//	cerr <<"!!!!!"<<root << endl;
		if (root < t[ptr-1]){
			a[ptr] = A;
			b[ptr] = B;
			c[ptr] = C;
			t[ptr++] = root;
			return;
		}		
		--ptr;
	}
	a[ptr] = A;
	b[ptr] = B;
	c[ptr] = C;
	t[ptr++] = 1e100;
	return;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
   // freopen("output.err","w",stderr);
  #endif
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int x,r;
		scanf("%d %d",&x,&r);
/*		if (RAND_MAX < (1<<17)){
			x = ((unsigned int)(rand()<<16) | (unsigned int)rand())%1000000000;
			r = ((unsigned int)(rand()<<16) | (unsigned int)rand())%1000000000+1;
		}
		else {
			x = (rand())%1000000000;
			r = (rand())%1000000000+1;
		
		}*/
		::x[i] = x;
		::r[i] = r;
//		assert (r > 0);
	}
//	sort(x,x+n);
//	for (int i=0;i<n;i++)
//		cerr << x[i] <<" "<<r[i] << endl;
//	cerr << endl;
	for (int i=0;i<n;i++){
		pop(x[i]);
/*		cerr<< ptr << endl;
		cerr << a[0]<<" "<<b[0]<<" "<<c[0] << " "<<t[0]<< endl;
		cerr << a[1]<<" "<<b[1]<<" "<<c[1] << " "<<t[1]<< endl;
		cerr << a[2]<<" "<<b[2]<<" "<<c[2] << " "<<t[2]<<endl;
		cerr << a[3]<<" "<<b[3]<<" "<<c[3] << " "<<t[3]<<endl;
		cerr << endl;*/
		r[i] = min(r[i],get(x[i]));
		push(1/(4*r[i]),-x[i]/(2*r[i]),(x[i]/(4*r[i]))*x[i]);
		cout.precision(3);
		cout << fixed << r[i] << endl;
//		if (r[i] < 0)
//			cerr << i << endl;
/*		#ifdef LOCAL
			cerr.precision(15);
			cerr << fixed << r[i] << endl;
		#endif*/
	}
	return 0;
}