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

const int base=10;

void print(const vector<int>& a){
	printf ("%d", a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2; i>=0; --i)
		printf ("%d", a[i]);
}

void add(vector<int>& a,const vector<int>& b){
	int carry = 0;
	for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i) {
		if (i == a.size())
			a.push_back (0);
		a[i] += carry + (i < b.size() ? b[i] : 0);
		carry = a[i] >= base;
		if (carry)  a[i] -= base;
	}
}

void mul(vector<int> &a,int b){
	int carry = 0;
	for (size_t i=0; i<a.size() || carry; ++i) {
		if (i == a.size())
			a.push_back (0);
		long long cur = carry + a[i] * 1ll * b;
		a[i] = int (cur % base);
		carry = int (cur / base);
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

bool bit[2500];


int used[5100];
bool used2[5100];
int val[5100];
int type[5100];


void calc(int l,int r){
	
  	int mpos=-1;
  	int lpos=-1;
  	setval(used,-1);
  	for (int i=l;i<r;i++)
  			if (type[i]==1)
  				used[val[i]]=i;
  			else{
  			 	if (used[val[i]]!=-1)
  			 		if (mpos==-1 || val[mpos]<val[i]){
  			 			mpos=i;
  			 			lpos=used[val[i]];
  			 		}
  			}	
  	if (mpos==-1)
  		return;

  	
  	bit[val[mpos]]=true;
		calc(l,lpos);
		//calc(nl+1,mpos);
		calc(mpos+1,r);
		return;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d\n",&n);
  for (int i=0;i<n;i++){
  	string s;
  	cin>>s>>val[i];
  	if (s=="sell")
  		type[i]=2;
  	else if (s=="win")
  		type[i]=1;
  	else
  		assert(false);
  }
  
	calc(0,n);
	vector<int> ans;
	vector<int> st2;
	st2.pb(1);
	ans.pb(0);
	for (int i=0;i<2500;i++)
		{
			if (bit[i])
				add(ans,st2);
			mul(st2,2);
		}
  print(ans);  
  return 0;
}