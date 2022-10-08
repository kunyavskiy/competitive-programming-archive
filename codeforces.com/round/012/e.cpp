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

int a[1000][1000];
bool u[1000][1000];
int next[1000];

int fnext(int i){
	for (;u[i][next[i]];next[i]++);
	u[i][next[i]]=true;
	return next[i];
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  cin>>n;
  for (int i=0;i<n;i++)
  	next[i]=1;
  memset(u,false,sizeof(u));
  	
  for (int i=0;i<n;i++){
  	int k=2*i+1;
  	k=k/n+k%n;
  	for (int j=i+1;j<n;j++){
  			a[j][i]=k;
  			++k;
  			if (k==n)
  				k=1;
  	}
  }
  	
  	
  for (int i=0;i<n;i++)
  	for (int j=i+1;j<n;j++)
  		a[i][j]=a[j][i];
  for (int i=0;i<n;i++)
  {
  	for (int j=0;j<n;j++)
  		printf("%d ",a[i][j]);
  	printf("\n");
  }
  return 0;
}