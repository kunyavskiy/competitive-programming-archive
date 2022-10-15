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

vector<int> col;
int n,m,k;

bool svob[100100];

void gen(int n){
	col.resize(k,0);
	for (int i=0;i<k && n+k-1>0 && col[i]<10;i=(i+1)%k)	
		col[i]++,--n;		
}

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m;
	k=m-n+1;
	if (k<=0){
		printf("No solution\n");
		return 0;
	}
	gen(n);
	int sum=0;
	for (int i=0;i<k;i++){
		if (col[i]<3){
			printf("No solution\n");
			return 0;		
		}
		sum+=col[i];
		sum-=!!i;
	}
	int sv=sum-(k-1);
	if (sum+sv<n){
		printf("No solution\n");
		return 0;
	}
	int num=1;
	printf("%d\n",k);
	memset(svob,true,sizeof(svob));
	for (int i=0;i<k;i++){	
		printf("%d",col[i]);
		for (int j=0;j<col[i];j++){
			num+=!!j;
			printf(" %d",num);
		}
		printf("\n");
		if (i!=k-1)
			svob[num]=false;
	}
	printf("%d\n",n-num);
	for (int i=1;num<n;i++)
		if (svob[i])
			printf("%d %d\n",i,++num);
	return 0;
}