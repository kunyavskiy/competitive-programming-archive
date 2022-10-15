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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int a[100][100];
int n;

bool checkx(int x1,int x2){
	for (int i=0;i<n;i++)
		if (a[x1][i] > a[x2][i])
			return false;
	return true;
}

bool checky(int y1,int y2){
	for (int i=0;i<n;i++)
		if (a[i][y1] < a[i][y2])
			return false;
	return true;
}

bool dltx[100];
bool dlty[100];



int main()
{
  #ifndef ONLINE_JUDGE
 //   freopen("input.txt","r",stdin);
 //   freopen("output.txt","w",stdout);
  #endif

for (n=1;n<50;n++){

	memset(dltx,false,sizeof(dltx));
	memset(dlty,false,sizeof(dlty));
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			a[i][j]=(abs(i-j)!=1)*2-1;
	
/*	for (int i=0;i<n;i++){
			if (dltx[i]) continue;
			for (int j=0;j<n;j++){
				if (dlty[j]) continue;
				printf("%d ",a[i][j]);				
			}			printf("\n");
		}
		printf("\n\n");*/
		
	int ans=n;
			

	for (;;){
		bool upd=false;
		for (int i=0;i<n;i++)
			if (!dltx[i]){
				for (int j=0;j<n;j++)
					if (i!=j && !dltx[j] && checkx(i,j)){
//						cerr<<"DELX "<<i<<" BY "<<j<<endl;
						for (int k=0;k<n;k++)
							a[i][k]=0;
						upd=true;
						--ans;
						dltx[i]=true;
						break;
					}
						
			}
			
		for (int i=0;i<n;i++){
			if (dlty[i]) continue;
			for (int j=0;j<n;j++){
				if (i==j || dlty[j]) continue;
				if (checky(i,j)){				
				//	cerr<<"DELY "<<i<<" BY "<<j<<endl;
					for (int k=0;k<n;k++)
						a[k][i]=0;
					dlty[i]=true;
					upd=true;
					break;
				}
			}
		}		
				
		if (!upd) break;			
		
		/* for (int i=0;i<n;i++){
			if (dltx[i]) continue;
			for (int j=0;j<n;j++){
				if (dlty[j]) continue;
				printf("%d ",a[i][j]);				
			}			printf("\n");
		}
		printf("\n\n");*/
	}

 	cout<< ans << endl;
 }

    return 0;
}