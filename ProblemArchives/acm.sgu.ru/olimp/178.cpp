#include <iostream>
#include <set>
#include <cstdio>
#define mp make_pair
using namespace std;

typedef long long int64;


set<pair<int64,int> > ans;

int64 lst[1000100];
int last[1100];
int primes[1100];

const int64 inf=1LL<<62LL;

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int k,n;
    scanf("%d %d",&k,&n);
    for (int i=0;i<k;i++)
    	scanf("%d",&primes[i]);
    lst[0]=1;
    for (int i=0;i<k;i++){
    	ans.insert(mp(primes[i],i));
    	last[i]=0;
    }
    
    for (int i=1;i<=n;i++){    
    	lst[i]=ans.begin()->first;
    	for (;ans.begin()->first == lst[i];)
    	{
    		int tmp=ans.begin()->second;
    		ans.erase(ans.begin());
    		++last[tmp];
    		if (lst[i] <= inf/last[tmp])    			
	    		ans.insert(mp(lst[last[tmp]]*primes[tmp],tmp));
    	}
    }    
    cout<<lst[n]<<endl;
	return 0;
}