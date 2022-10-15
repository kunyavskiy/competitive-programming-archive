#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "e"

const int inf = 1000000000;
const ld eps = 1e-9;

int f[1000010];
int n;
int m;
char buf[110];

inline void get(char* a,int& b){

	while (*a == ' ')
		a++;
	b = 0;
	for (;'0' <= *a && *a <= '9'; a++)
		b = b * 10 + *a - '0';
}

inline void get3(char* a,int& b,int& c,int& d){
	while (*a == ' ')
		a++;
	b = 0;
	for (;'0' <= *a && *a <= '9'; a++)
		b = b * 10 + *a - '0';

	c = 0;
	while (*a == ' ')
		a++;
	for (;'0' <= *a && *a <= '9'; a++)
		c = c * 10 + *a - '0';


	while (*a == ' ')
		a++;
	d = 0;
	int temp = 1;
	if (*a == '-'){
		temp *= -1;
		a++;
	}
	for (;'0' <= *a && *a <= '9'; a++)
		d = d * 10 + *a - '0';
	d = d * temp;
}

char obuf[110000];
int ptr = 0;

void print(int a){
	int tptr = ptr;
	do {
		obuf[ptr++] = a%10+'0';
		a /= 10;
	}while (a);
	reverse(obuf+tptr,obuf+ptr);
	obuf[ptr++] = '\n';
	if (ptr >= 100000){
		obuf[ptr-1] = 0;
		puts(obuf);
		ptr = 0;
	}
}

int main(){
  #ifdef LOCAL
    int START = clock();
  #endif
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  gets(buf);
  sscanf(buf,"%d%d",&n,&m);
  for (int i = 0; i < m; i++){
  	int l,r,a,d;
	gets(buf);
  	if (buf[0] == 'A'){
		get3(buf+1,l,r,d);
//  		l--,r--;
  		for (;l < n; l=(l|(l+1)))
  			f[l] += d;
  		for (r++; r < n; r = (r|(r+1)))
  			f[r] -= d;
  	}
  	else {
		get(buf+1,a);
//  		a--;
  		int ans = 0;
  		for (;a != -1; a = (a&(a+1))-1)
  			ans += f[a];
  		printf("%d\n",ans);
  	}
  }

/*  if (ptr){
	  obuf[ptr-1] = 0;
	  puts(obuf);
  }
  ptr = 0;*/

  #ifdef LOCAL
    cerr << (clock()-START)*1.0/CLOCKS_PER_SEC<<endl;
  #endif
  return 0;
}

