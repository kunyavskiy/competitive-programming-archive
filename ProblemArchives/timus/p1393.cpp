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
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
                 

const int MAXN = 510000;

string s;
int n;

int a[MAXN];
int b[MAXN];
int c[MAXN];
int a1[MAXN];
int c1[MAXN];
int cnt[MAXN];


void build(){
	n = s.size();

	for (int i = 0; i < n; i++)
		cnt[(unsigned char)s[i]]++;
	for (int i = 1; i < 255; i++)
		cnt[i] += cnt[i-1];

	for (int i = 255; i > 0; i--)
		cnt[i] = cnt[i-1];
	cnt[0] = 0;

	
	for (int i = 0; i < n; i++){
		a[cnt[(unsigned char)s[i]]] = i;
		b[i] = cnt[(unsigned char)s[i]];
		cnt[(unsigned char)s[i]]++;
	}


	int ptr = -1;
	for (int i = 0; i < n; i++){
		if (!i || s[a[i-1]] != s[a[i]])
			ptr++;
		c[a[i]] = ptr;
	}


	for (int it = 1; (1<<it) <= 2*n; it++){
		memset(cnt,0,sizeof(cnt));

		for (int i = 0; i < n; i++)
			cnt[c[i]]++;

		for (int i = 1; i <n; i++)
			cnt[i] += cnt[i-1];

		for (int i = n-1; i > 0; i--)
			cnt[i] = cnt[i-1];
		cnt[0] = 0;

		for (int i = 0; i < n; i++)
			a1[cnt[c[(a[i]-(1<<(it-1))+2*n)%n]]++] = (a[i]-(1<<(it-1))+2*n)%n;
                                                                       
		for (int i = 0; i < n; i++)
			a[i] = a1[i], b[a[i]] = i;

		ptr = -1;
		for (int i = 0; i < n; i++){
			if (i == 0 || mp(c[a[i]],c[(a[i]+(1<<(it-1)))%n]) != mp(c[a[i-1]],c[(a[i-1]+(1<<(it-1)))%n]))
				ptr++;
			c1[a[i]] = ptr;
		}
		for (int i = 0; i< n; i++)
			c[i] = c1[i];
	}		
}




int main(){
  #ifdef LOCAL
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
  #endif
  getline(cin,s);
  getline(cin,s);
  build();

  #ifdef LOCAL
	  for (int i = 0; i < n; i++){
  		cout << string(s.begin()+a[i],s.end())+string(s.begin(),s.begin()+a[i]) << endl;
        if (i && c[a[i]] == c[a[i-1]])
            assert(string(s.begin()+a[i],s.end())+string(s.begin(),s.begin()+a[i]) ==
                   string(s.begin()+a[i-1],s.end())+string(s.begin(),s.begin()+a[i-1]));
      }
  	  cout << endl;	
  #endif

  int ptr = 0;

  ll sum = 0;

  for (int i = 0; i < n; i++){
     if (b[i] == n-1){
        ptr = 0;
        continue;
     }
     ptr = max(0,ptr-1);

     while (ptr < n && s[(a[b[i]] + ptr)%n] == s[(a[b[i]+1]+ptr)%n])
        ptr++;

     sum += ptr;

     if (b[i+1] > b[a[b[i]+1]+1])
        ptr = 0;
  }

  cout.precision(15);
  cout << fixed << ld(sum)/ld(n-1) << endl;

  return 0;
}

