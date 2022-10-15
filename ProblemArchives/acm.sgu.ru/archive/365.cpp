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

int64 ans[21][20];


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  /*int kol=0;
  for (int i=0;i<1000;i++)
  	if (i/100<=(i/10)%10 && (i/10)%10<=i%10)
  		kol++;
  cerr<<kol<<endl;*/
	ans[0][0]=1;
	for (int i=1;i<=20;i++)
	{
		for (int j=0;j<10;j++)
		{
			ans[i][j]=0;
			for (int k=0;k<=j;k++)
				ans[i][j]+=ans[i-1][k];
			//cerr<<ans[i][j]<<" ";
		}
		for (int j=10;j<20;j++)
		{
			ans[i][j]=0;
			for (int k=19;k>=j;k--)
				ans[i][j]+=ans[i-1][k];
			for (int k=j-9;k<10;k++)
				ans[i][j]+=ans[i-1][k];
	//		cerr<<ans[i][j]<<" ";
		}
	//	cerr<<endl;
	}
	int s;
	cin>>s;
	int64 res=0;
	for (int i=0;i<20;i++)
	{
		res+=ans[s][i];
	//	cerr<<res<<endl;
	}
	cout<<res<<endl;
				
  return 0;
}