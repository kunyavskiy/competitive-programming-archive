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

const int maxn=1000100;

typedef pair<int,int> pii;

int nums[maxn];
int kol[maxn];
int have[maxn];
pii vals[maxn];
int n,m,k;

void printans(int hod,int prop){
	for (int i=0;i<n;i++){
		if (have[nums[i]]-kol[nums[i]]+hod+prop>=m && kol[nums[i]]!=1){
			printf("%d ",i+1);
		}
		if (kol[nums[i]]==1)
			if (have[nums[i]]-kol[nums[i]]+prop>=m)
				printf("%d ",i+1);
	}
	printf("\n%d\n",hod);
	exit(0);
}


inline bool cmp(const pii &a,const pii &b){
	if (a.first!=b.first)
		return a.first<b.first;
	if (kol[nums[a.second]]!=kol[nums[b.second]])
		return kol[nums[a.second]]==1;
	return a.second<b.second;
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	scanf("%d %d %d",&n,&m,&k);
	for (int i=0;i<k;i++)
		scanf("%d",&have[i]);
	for (int i=0;i<n;i++){
		int a;
		scanf("%d",&a);
		--a;
		nums[i]=a;
		kol[a]++;
	}
	for (int i=0;i<k;i++){
		vals[i]=mp(have[i]-kol[i],i);
		assert(kol[i]>1);
	}
	sort(vals,vals+k,cmp);
	int h,pr;
	h=pr=0;
	int ptr=0;
	m-=n;
	reverse(vals,vals+k);
	for (;ptr<k;h++){
		int num=vals[ptr].second;
		int val=vals[ptr].first;
		if (kol[num]!=1 && kol[num]!=0)
			if (val+h>=m)
				printans(h+1-pr,pr);
		for (;ptr<n && (kol[num]==1 && val+h==m) || kol[num]==0;){
			if (kol[num]!=0){
			if (val+pr<m){
				pr+=val;
				h+=val;			
			}
			else
				printans(h+1-pr,pr);
			}
			++ptr;			
			num=vals[ptr].second;
			val=vals[ptr].first;
		}
	}
	printf("0\n");
  return 0;
}