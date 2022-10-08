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

#define norm(x) if (x>modul) x-=modul;

using namespace std;

int t[150][150][150][3];
const int modul=51123987;

string s;



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  cin>>n>>s;
  
	int maxv=n/3+ (!!(n%3));
  

	bool q[3];
	q[0]=q[1]=q[2]=0;
	
	for (int i=0;i<=maxv;i++)
	{
		q[s[i]-'a']=1;
		if (q[0])
			t[i][i+1][0][0]=1;
		if (q[1])
			t[i][0][i+1][1]=1;
		if (q[2])
			t[i][0][0][2]=1;
	}
	
 
  for (int i=0;i<n;i++)
  	for (int j=0;j<=maxv;j++)
  		for (int k=0;k<=maxv;k++){  			
  			for (int w=0;w<3;w++){
  			if (t[i][j][k][w]==0)
  				continue;
  			
  			cerr<<i<<" "<<j<<" " <<k<<" "<<w<<" "<<t[i][j][k][w]<<endl;
  			bool q[3];
  			q[0]=q[1]=q[2]=0;
  			for (int l=1;l+i<n && l<=maxv;l++){
  					q[s[i+l]-'a']=1;
  					if (q[0] && j+l<=maxv && w!=0){
  						t[i+l][j+l][k][0]+=t[i][j][k][w];
  						norm(t[i+l][j+l][k][1]);
  					}
  					if (q[1] && k+l<=maxv && w!=1){
  						t[i+l][j][k+l][1]+=t[i][j][k][w];
  						norm(t[i+l][j][k+l][1]);
  					}
  					if (q[2] && w!=2)
  						{
  							t[i+l][j][k][2]+=t[i][j][k][w];
  							norm(t[i+l][j][k][2]);
  						}  						
  			}
  		}
  }		
  int ans=0;
  


	for (int i=maxv-1;i<=maxv;i++)
		for (int j=maxv-1;j<=maxv;j++){
			int c=n-i-j;
			if (abs(c-i)<=1 && abs(c-j)<=1)
				{
					for (int w=0;w<3;w++){
						ans+=t[n-1][i][j][w];
						norm(ans);
					}
				}
		}	
  cout<<ans<<endl;
  
  return 0;
}