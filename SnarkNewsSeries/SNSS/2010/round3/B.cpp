#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int64 hash[25][110000];
int hptr[25];
char s[100];
const int64 P=31;
int n,m;                           

int main(){     
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<n;i++){
		s[0]=0;
		gets(s);
		int64 h=0;
		for (int i=0;s[i];i++)
			{
				h=h*P+s[i]-'a'+1;
				hash[i][hptr[i]++]=h;
			}
	}
	for (int i=0;hptr[i];i++)
		sort(hash[i],hash[i]+hptr[i]);
	for (int it=0;it<m;it++){
		s[0]=0;
		gets(s);
		int64 h=0;                
		for (int i=0;;i++)
			{
				if (!s[i]){
					--i;
					printf("%d\n",upper_bound(hash[i],hash[i]+hptr[i],h)-lower_bound(hash[i],hash[i]+hptr[i],h));
					break;
				}
				h=h*P+s[i]-'a'+1; 
			}
		
	}
	return 0;
} 