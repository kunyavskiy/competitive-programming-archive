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

typedef vector<int> tlong;

void norm(tlong& a){	
	for (;a.size()>1 && a.back()==0;a.pop_back());
	if (a.size()==0)
		a.pb(0);
}

void add(tlong& a,tlong& b){
	norm(a);
	norm(b);
	int c=0;
	for (int i=0;i<b.size() || c;i++){
		if (i==a.size())
			a.pb(0);
		if (i<b.size())
			a[i]+=b[i];
		a[i]+=c;
		c=a[i]/10;
		a[i]%=10;		
	}
	norm(a);
}

bool isnull(tlong& a){
	norm(a);
	return (a.size()==1 && a[0]==0);
}

void print(tlong& t){
	norm(t);
	for (int i=(int)t.size()-1;i>=0;i--)
		printf("%d",t[i]);
	printf("\n");
	return;
}

tlong t[20][1000];
bool used[20];
int n;

int get(int k){
	for (int i=0;i<n;i++)
		if (!used[i]){
			--k;
			if (k==0){	
				used[i]=true;
				return i;				
			}
		}
	assert(false);	
}

void gen(int n,int T){
	if (isnull(t[n][T])){
		printf("-\n");
		return;
	}
	for (;n;){
		for (int k=1;k<=n;k++)
			if (n==1 || !isnull(t[n-1][T-k+1]))
				{
					T-=k-1;
					n--;
					printf("%d ",get(k)+1);
					break;
				}
	}
	printf("\n");
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int T;
	cin>>n>>T;
	t[1][0]=tlong(1,1);
	for (int i=2;i<=n;i++)
		for (int j=0;j<=T;j++){
			t[i][j]=tlong(1,0);
			for (int k=1;k<=i;k++)
				if (j>=k-1){
	//				cout<<"!!!!"<<i<<" "<<j<<" "<<k<<" ";
	//				print(t[i-1][j-k+1]);
					add(t[i][j],t[i-1][j-k+1]);
				}
	//		cout<<i<<" "<<j<<" : ";
	//		print(t[i][j]);
		}
	print(t[n][T]);
	gen(n,T);
    return 0;
}