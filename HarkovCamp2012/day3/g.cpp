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

#define taskname "g"

const int inf = 1000000000;
const ld eps = 1e-9;

char s[1000010];

char s1[1000010];
char s2[1000010];
char d1[1000010];
char d2[1000010];
short mask[1000010];
int sz;

void compare(){
  int p = 0;
  for (int j = sz-1; j >= 0; j--){
  	p = s1[j] - s[j] + p;
  	if (p < 0){
  		p = p+10;
	  	d1[j] = p+'0';
	  	p = -1;
	}
	else {
	  	d1[j] = p+'0';
	  	p = 0;
	}
  }

  p = 0;
  for (int j = sz-1; j >= 0; j--){
  	p = s[j] - s2[j] + p;
  	if (p < 0){
  		p = p+10;
	  	d2[j] = p+'0';
	  	p = -1;
	}
	else {
	  	d2[j] = p+'0';
	  	p = 0;
	}
  }

  

  for (int i = 0; i < sz; i++)
  	if (d1[i] != d2[i]){
  		if (d1[i] < d2[i]){
  			puts(s1+(s1[0] == '0'));
  		}
  		else {
  			puts(s2+(s2[0] == '0'));
  		}
	  	return ;	
  	}

   puts(s1);

}


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  int K;
  scanf("%d %s",&K,s);

  
  sz = strlen(s);



  for (int i = 0; i < sz; i++)
	mask[i] = (i?mask[i-1]:0)|(1<<(s[i]-'0'));

  bool ok = false;	

  if (__builtin_popcount(int(mask[sz-1])) <= K){
  	puts(s);
  	return 0;
  }

  for (int i = sz-1; i >= 0 && !ok; i--){
  	for (int j = s[i]-'0'+1; j < 10 && !ok; j++){
  		if (__builtin_popcount((int)((i?mask[i-1]:0) | (1<<j))) <= K){
  			memcpy(s1,s,sizeof(s));
  			s1[i] = j+'0';
  			ok = true;
  			int add = -1;
  			for (int k = 0; k < 10; k++)
  				if (__builtin_popcount((int)((i?mask[i-1]:0) | (1<<j) | (1<<k))) <= K){
  					add = k;
  					break;
  				}
  			assert(add != -1);
  			for (int k = i+1; k< sz; k++)
  				s1[k] = add+'0';
  		}
  	}
  }	

  if (!ok){
  	for (int j = 0; j < sz; j++)
  		s1[j] = '9';
  }
  ok = false;

  for (int i = sz-1; i >= 0 && !ok; i--){
  	for (int j = s[i]-'0'-1; j >= !i && !ok; j--)
  		if (__builtin_popcount((int)((i?mask[i-1]:0) | (1<<j))) <= K){
  			memcpy(s2,s,sizeof(s));
  			s2[i] = j+'0';
  			ok = true;
  			int add = -1;
  			for (int k = 9; k >= 0; k--)
  				if (__builtin_popcount((int)((i?mask[i-1]:0) | (1<<j) | (1<<k))) <= K){
  					add = k;
  					break;
  				}
  			assert(add != -1);
  			for (int k = i+1; k< sz; k++)
  				s2[k] = add+'0';
  		}
  }	
  if (!ok){
  	s2[0] = '0';
  	for (int j = 1; j < sz; j++)
  		s2[j] = '9';
  }

//  cerr <<s1 <<" "<<s2<<endl;

  compare();
  return 0;
}

