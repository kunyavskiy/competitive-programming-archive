#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#define pb push_back

using namespace std;

int* a[600];
int n;
int zar[1000];
vector<int> g[1000];
bool active[1000];

void error(){
	printf("NO SOLUTION\n");
	exit(0);
}

void merge(const vector<int>& nums,int nzar){
	int sz=nums.size();
	for (int i=0;i<sz;i++)
		for (int j=0;j<i;j++)
			if (a[nums[i]][nums[j]]!=nzar)
				error();
	for (int i=0;i<sz;i++)
		active[nums[i]]=false;
	g[n]=nums;
	a[n]=new int[600];
	for (int i=0;i<n;i++)
		if (active[i]){
			a[n][i]=a[i][n]=a[nums[0]][i];
			for (int j=0;j<nums.size();j++)
				if (a[n][i]!=a[nums[j]][i])
					error();
		}
	for (int i=0;i<sz;i++)
		delete a[nums[i]];
	a[n][n]=zar[n]=nzar;
	active[n]=true;
	n++;
}

vector<int> num;
bool iterate(){
	int bi=-1,bj=-1;
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (active[i] && active[j]){
				if (bi==-1 || a[bi][bj]>a[i][j])
				{
					bi=i;
					bj=j;
				}
			}
	if (bi==-1)
		return false;
	int nzar=a[bi][bj];
	num.pb(bi);
	for (int i=0;i<n;i++)
		if (a[bi][i]==nzar && active[i])
			num.pb(i);
	merge(num,nzar);
	num.clear();
	return true;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	//cout<<sizeof(a)/1024.0/1024<<endl;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	a[i]=new int[600];
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			scanf(" %d ",&a[i][j]);
	for (int i=0;i<n;i++){
		active[i]=true;
		zar[i]=a[i][i];
	}
	for (;iterate(););
	for (int i=0;i<n;i++)
		for (int j=0;j<g[i].size();j++)
			if (zar[g[i][j]]>=zar[i])
				error();
	cout<<n<<endl;
	for (int i=0;i<n;i++){
		printf("%d %d",i+1,zar[i]);
		for (int j=0;j<g[i].size();j++)
			printf(" %d",g[i][j]+1);
		printf("\n");
	}
	return 0;
}
