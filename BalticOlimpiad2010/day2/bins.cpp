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
#define filename "bins"
using namespace std;

int val[20100];

int kol[1010][2];

bool check(){
	int sum1=0;
	int sum2=kol[1005][1];
	for (int i=1004;i>=0;i--){
		if (sum1<sum2)
			return false;
		sum1+=kol[i+1][0];
		sum2+=kol[i][1];
	}
	return sum1>=sum2;
}

int main()
{
  freopen(filename".in","r",stdin);
  freopen(filename".out","w",stdout);
	int m,n;
  scanf("%d %d",&m,&n);
  for (int i=0;i<n;i++){
  	scanf("%d",&val[i]);
  }
  int ans=-1;
  kol[val[0]][1]++;
  kol[val[1]][0]++;
  if (check())
  	ans=1;
  for (int k=2;2*k<=n;++k){
  	kol[val[k-1]][1]++;
  	kol[val[k-1]][0]--;
  	kol[val[2*k-2]][0]++;
  	kol[val[2*k-1]][0]++;
  	if (check())
  		ans=k;
  }
  cout<<ans<<endl;
  return 0;
}