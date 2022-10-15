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
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const ld eps=1e-9;
int x;

vector<ld> getprob(vector<ld> result){
	vector<ld> win(27);
	vector<bool> stop(27);
	vector<ld> ans(27);
	for (int i=21;i<=26;i++){
		win[i] = result[i];
		stop[i] = true;
		ans[i] = 0;
	}
	for (int i=20;i>=0;--i){
		ld tmp = 0;
		for (int j=1;j<=6;j++)
			tmp += win[i+j];
		tmp/=6;
		if (result[i] > tmp + eps)
			stop[i] = true;
		win[i] = max(result[i],tmp);
		ans[i]=0;
	}
	ans[0] = 1;
	for (int i=0;i<=26;i++){
		if (stop[i]) continue;
		for (int j=1;j<=6;j++)
			ans[i+j]+=ans[i]/6;
		ans[i]=0;
	}
	return ans;
}

ld getresult(vector<ld> result){
	vector<ld> prob = getprob(result);
	ld ans = 0;
	for (int i=0;i<=26;i++)
		ans += prob[i] * result[i];
	return ans ;		
}

ld solve(int big){
	vector<ld> tmp(27);
	vector<ld> probmy(27);
	
	for (int i=26;i>=22;--i){
		probmy[i] = 0;
		tmp[i] = x*(big > 21);
	}
	for (int i=21;i>=0;--i)
		tmp[i] = x*(big>21 || big <= i);
	for (int i=21;i>=0;--i){
		tmp[i] ++;
		vector<ld> probcrup = getprob(tmp);
		probmy[i] = 0;
		for (int j=0;j<i;j++)
			probmy[i] += probcrup[j];
		for (int j=22;j<=26;j++)
			probmy[i] += probcrup[j];
	}
	
	return getresult(probmy);
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	vector<ld> tmp(27);
	vector<ld> probbig(27);
	
	for (int i=26;i>=22;--i){
		probbig[i] = 0;
		tmp[i] = 0;
	}
	for (int i=21;i>=0;--i){
		tmp[i] = 1;
		probbig[i] = 1 - getresult(tmp);		
	}
	
	cin>>x;

	probbig = getprob(probbig);
	ld ans = 0;
	for (int i=0;i<26;i++)
		if (probbig[i] > eps)
			ans += probbig[i] * solve(i);	
	cout << ans << endl;
    return 0;
}