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
#include <bitset>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

int64 ans[11][11];
int n,p;
int cnt[11];
int fact[11];
int kol;
int first;

void addtoans(){
	int sum,last;
	sum=last=0;
	for (int i=0;i<p;i++){
		sum+=cnt[i];
		if (cnt[i])
			last=i;
	}
	int64 add=fact[sum];
	for (int i=0;i<p;i++)
		add/=fact[cnt[i]];
	ans[sum+1][max(last,first)+1]+=add;
}



void calc(int maxv,const bitset<200>& used){
//	for (int i=80;i<=120;i++)
//		cerr<<used.test(i)<<" ";
//	cerr<<endl;
	if (used.test(100))
		addtoans();
	if (kol==n-1)
		return;
	for (int i=maxv;i<p;i++){
		++cnt[i];++kol;
		calc(i,(used<<i)|(used>>i));
		--cnt[i];--kol;	
	}
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&p);
	fact[0]=1;
	for (int i=1;i<11;i++)
		fact[i]=fact[i-1]*i;
	for (int i=0;i<p;i++){
		bitset<200> tmp;
		for (int j=0;j<200;j++)
			tmp[j]=0;
		tmp.set(100+i);
		calc(0,tmp);
	}
	for (int i=0;i<=n;i++)
		for (int j=1;j<=p;j++)
			ans[i][j]+=ans[i][j-1];
	cout<<ans[n][p]<<endl;
    return 0;
}