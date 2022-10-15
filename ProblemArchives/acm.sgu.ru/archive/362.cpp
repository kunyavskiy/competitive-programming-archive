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

bool used[10][10];
const string name="DLUR";
const int dx[4]={1,0,-1,0};
const int dy[4]={0,-1,0,1};
int n,m;
bool good(int i,int j)
{
	return (i>=0) && (j>=0) && (i<n) && (j<m) && !used[i][j];
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  cin>>n>>m;
  int i,j;
  cin>>i>>j;
  --i,--j;
  for (;;)
  {
	  used[i][j]=true;
  	for (int t=0;t<4;t++)
  		if (good(i+dx[t],j+dy[t]))
  			{
  				printf("%c",name[t]);
  				i=i+dx[t];
  				j=j+dy[t];
  				break;
  			}
  	if (used[i][j])
  		break;
  }
  return 0;
}