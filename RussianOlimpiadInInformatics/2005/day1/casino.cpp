#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
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

const string TASKNAME = "casino";
const string INFILE = TASKNAME + ".in";
const string OUTFILE = TASKNAME + ".out";

#undef min

inline int min(int a,int b){
	return ((a<b)?a:b);
}

#undef max

inline int max(int a,int b){
	return ((a>b)?a:b);
}

int t[160][160];
int* t1[160][160][160];
int cost[26];
int can[160][160];
int len[160];
int sum[160];
int s[160];
int lens;
int n;

const int inf= 1<< 29;

inline int getsum(int l,int r){
	#ifdef LOCAL
		assert (l<=r);
	#endif
	return sum[r] - (l?sum[l-1]:0);
}

int calc(int,int);
bool calc1(int,int,int,int);

int calc(int l,int r){
	int& ans = t[l][r];
	if (l == r)
		return ans=0;
	if (ans != -1)
		return ans;

	if (l == r-1){
		ans = 0;
		for (int i=0;i<n;i++)
			if (len[i] == 1 && can[i][0] == s[l]){
				ans = cost[s[l]];
				break;
			}
		return ans;
	}	
	
	int bans = getsum(l,r-1);
	ans = calc(l+1,r);
	for (int i=0;i<n && ans!=bans;i++)
		if (len[i] != 1 && can[i][0] == s[l] && can[i][len[i]-1] == s[r-1]){
			if (calc1(l,r,i,len[i]))
				ans = bans;
		}
			
	for (int j=l;j<r && ans!=bans;j++)
		ans = max(ans,calc(l,j)+calc(j,r));
		
	return ans;	
}

bool calc1(int l,int r,int num,int pos){
	int& ans = t1[l][r][num][pos];
	if (l == r)    
		return ans = (pos == 0);	
	if (pos == 0)
		return ans = false;
	if (ans != -1)
		return ans;
	if (l == r-1){
		return ans = (pos == 1);
	}
	
	if (pos == 2){
		return (l+1 == r-1) || (calc(l+1,r-1) == getsum(l+1,r-2));
	}
	
	ans = 0;
	
	for (int j=r-2;j>=l+1 && !ans;j--){
		if (s[j] != can[num][pos-2])
			continue;
		if (j!=r-2 && calc(j+1,r-1) != getsum(j+1,r-2))
			continue;
		ans = calc1(l,j+1,num,pos-1);
	}
	
	return ans;			
}


char buf[200];

void read(){
	int k;
	scanf("%d",&k);
	for (int i=0;i<k;i++){
		char c;
		scanf(" %c ",&c);
		scanf(" %d ",&cost[c-'a']);
	}
	scanf(" %s ",buf);
	lens = strlen(buf);
	for (int i=0;buf[i];i++){
		s[i] = buf[i]-'a';
	}
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf(" %s ",buf);
		len[i]=strlen(buf);
		for (int j=0;j<len[i];j++)
			can[i][j] = buf[j] - 'a';
	}
}

void allocate(){
	memset(t,-1,sizeof(t));
	for (int i=0;i<=lens;i++)
		for (int j=i;j<=lens;j++)
			for (int k=0;k<n;k++){
				t1[i][j][k] = new int[len[k]+5];
				memset(t1[i][j][k],-1,sizeof(int)*(len[k]+5));
			}
}

void calcsums(){
	sum[0] = cost[s[0]];
	for (int i=1;i<lens;i++)
		sum[i] = sum[i-1] + cost[s[i]];
}



int main()
{
    //freopen(INFILE.data(),"r",stdin);
   // freopen(OUTFILE.data(),"w",stdout);
	read();
	allocate();	
	calcsums();
	int tmp = calc(0,lens);
	cout << tmp << endl;  
    return 0;
}