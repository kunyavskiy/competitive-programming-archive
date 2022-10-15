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

int t[2][1100];
int a[1100];


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
   	int n;
   	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int *t1,*t2;
	t1=t[0];
	t2=t[1];
	for (int i=0;i<=n;i++)
		t1[i]=t2[i]=1<<29;
	t1[0]=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<i-1;j++){
			t2[j]=min(t2[j],t1[j]+abs(a[i-1]-a[i]));
			t2[i-1]=min(t2[i-1],t1[j]+abs(a[i]-a[j]));
		}
		t2[0]=min(t2[0],t1[0]+abs(a[i-1]-a[i]));
		t2[i-1]=min(t2[i-1],t1[0]);
		for (int i=0;i<n;i++)
			t1[i]=1<<30;
		swap(t1,t2);	
	}
	int ans=t1[0];
	for (int i=1;i<n;i++)
		ans=min(ans,t1[i]+abs(a[n]-a[i]));
	cout<<ans<<endl;
    return 0;
}