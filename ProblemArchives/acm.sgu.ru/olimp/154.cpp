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

int l1[1010][1010];
int l[1010];
int w[1010];
int t[1010];
int from[1010][2];
string s1,s2;
int n,m;

int cnt(int i,int j)
{
	if ((i==n) || (j==m))
		return 0;         
	if (l1[i][j]!=-1)
		return l1[i][j];
	if (s1[i]!=s2[j])
		return l1[i][j]=0;
	return l1[i][j]=1+cnt(i+1,j+1);
}

void print(int i,int kol){
	if (i==0)
	{
		printf("%d\n",kol);
		return;
	}
	print(from[i][0],kol+1);
	if (from[i][1]==1)
	{
		printf("New ");
		for (int j=from[i][0]+1;j<=i;j++)
			printf("%c",s2[j]);
		printf("\n");
		return;
	}
	printf("Old %d %d\n",w[from[i][0]+1],i-from[i][0]);
	return;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int L1,L2;
  cin>>L2>>L1;
  setval(l1,-1);
  setval(t,1);  
  cin>>s1>>s2;
  s1=((char)0)+s1;
  s2=((char)1)+s2;
  n=s1.size();
  m=s2.size();  
//  for (int i=0;i<m;i++)
 // 	cerr<<s2[i]<<" ";
 // cerr<<endl;
  for (int i=0;i<m;i++)
  {
  	l[i]=0;
  	for (int j=0;j<n;j++)
  	{
  		int tmp=cnt(j,i);
  		if (l[i]<tmp)
  			{
  				l[i]=tmp;
  				w[i]=j;
  			}
  	}
 // 	cerr<<l[i]<<" ";
  }
//  cerr<<endl;
  t[0]=0;

  for (int i=0;i<m;i++)
  {
  	 for (int j=i+1;j<m;j++)
  	 {
  	 		 if (j-i<=l[i+1])
  	 		 {
  	 		 		if (t[j]>t[i]+L2)
  	 		 			{
  	 		 				t[j]=t[i]+L2;
  	 		 				from[j][0]=i;
  	 		 				from[j][1]=0;
  	 		 			}        
  	 		 }
				 if (t[j]>t[i]+L1+j-i)
  	 		 {
  	 		 		t[j]=t[i]+L1+j-i;
  	 		 		from[j][0]=i;
  	 		 		from[j][1]=1;
  	 		 }
  	 }
  //	 for (int j=0;j<m;j++)
//  	 	cerr<<t[j]<<" ";
//  	cerr<<endl;
  }     
  printf("%d\n",t[m-1]);
  print(m-1,0);
  return 0;
}