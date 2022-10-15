#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#define mp make_pair
using namespace std;

pair<int,int> minmax(pair<int,int> a,pair<int,int> b)
{
	return mp(min(a.first,b.first),max(a.second,b.second));
}

long long lensqr(pair<long long,long long> a)
{
	return a.first*a.first+a.second*a.second;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	scanf("%d",&n);
	vector<map<int,pair<int,int>>> t(n+1);
	t[0][0]=mp(0,0);
	vector<pair<int,int>> a(n+1);
	a[0]=mp(0,0);
	for (int i=1;i<=n;i++)
		scanf("%d %d",&(a[i].first),&(a[i].second));
	for (int i=0;i<n;i++)
	{
		t[i+1]=t[i];
		for (map<int,pair<int,int>>::iterator iter=t[i].begin();iter!=t[i].end();iter++)
		{
			if (t[i+1].find((*iter).first+a[i+1].first)==t[i+1].end())
			{
				t[i+1][(*iter).first+a[i+1].first]=mp((*iter).second.first+a[i+1].second,(*iter).second.second+a[i+1].second);
			}
			else
			{
				pair<int,int> temp=mp((*iter).second.first+a[i+1].second,(*iter).second.second+a[i+1].second);
				t[i+1][(*iter).first+a[i+1].first]=minmax(t[i+1][(*iter).first+a[i+1].first],temp);
			}			
		}
	}
		long long maxres=0;
		for (map<int,pair<int,int>>::iterator iter=t[n].begin();iter!=t[n].end();++iter)
		{
			maxres=max(maxres,lensqr(mp((*iter).first,(*iter).second.first)));
			maxres=max(maxres,lensqr(mp((*iter).first,(*iter).second.second)));
		}
		double res=sqrt((double) maxres);
		printf("%.13f",res);
		return 0;
	
}