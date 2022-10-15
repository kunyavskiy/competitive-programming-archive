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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;


const int maxn=1000000;
int bkol[2*maxn+1];
char s[maxn+10];

int main()
{
  freopen("dance.in","r",stdin);
  freopen("dance.out","w",stdout);
  int bal=maxn;
  bkol[bal]++;
  int n;
  scanf("%d\n",&n);
  gets(s);
  int64 res=0;
  for (int i=0;i<n;i++){
		if (s[i]=='a')
			bal++;
		else
			bal--;
		res+=bkol[bal];
		bkol[bal]++;		
  }
	cout<<res<<endl;
  return 0;
}