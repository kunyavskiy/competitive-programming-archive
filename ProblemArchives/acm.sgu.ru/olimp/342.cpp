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


#define left botva854

using namespace std;

bool a[700][700];
short int left[700];
int n;

int t[700],ht;
int cnt[700],hcnt;

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    //cerr<<((sizeof(a)+sizeof(left)+sizeof(t)+sizeof(cnt))/1024.0/1024)<<endl;
    
    
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			char c;
			scanf(" %c ",&c);
			a[i][j]=(c=='.');
		}
	
	
	int64 ans=0;

	for (int j=n-1;j>=0;j--){
		for (int i=0;i<n;i++)
			left[i]=((j==n-1)?1:(left[i]+1))*a[i][j];
		ht=hcnt=0;
		int64 sum=0;
		for (int i=n-1;i>=0;i--){
			int ncnt=1;
			for (;ht>0 && t[ht-1]>=left[i];){
				sum-=t[ht-1]*cnt[hcnt-1];
				ncnt+=cnt[hcnt-1];
				ht--;
				hcnt--;
			}
			sum+=ncnt*left[i];
			ans+=sum;
			t[ht++]=left[i];
			cnt[hcnt++]=ncnt;
//			cerr<<i<<" "<<j<<" "<<sum<<endl;
		}
	}
	
	cout<<ans<<endl;		

    return 0;
}