#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


const int perm1[6] = {0,2,3,4,1,5};
const int perm2[6] = {2,1,5,3,0,4};
const int ord[6]   = {1,3,0,2,5,4}; 





vector<int> mult(vector<int> a,vector<int> b){
	vector<int> res(6);
	for (int i = 0;i < 6; i++)
		res[i] = b[a[i]];
	return res;
}

set<vector<int> > s;


void norm(vector<int>& a){
	vector<int> temp = a;

	for (set<vector<int> > ::iterator iter = s.begin(); iter != s.end(); ++iter){
		vector<int> temp2 = mult(*iter,temp);
		a = min(a,temp2);
	}	
}

pair<vector<int>,int> a[100010];
int b[100010];





int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  s.insert(vector<int>(perm1,perm1+6));
  s.insert(vector<int>(perm2,perm2+6));

  for (;;){
  	bool q = false;
  	for (set<vector<int> >::iterator iter = s.begin(); iter != s.end() && !q; ++iter)
  		for (set<vector<int> >::iterator iter2 = s.begin(); iter2 != s.end() && !q; ++iter2){
  			vector<int> temp = mult(*iter,*iter2);
  			if (s.find(temp) == s.end()){
  				s.insert(temp);
  				//for (int i = 0;i < 6; i++)
  				//	cerr << temp[i] <<" \n"[i==5];
  				q = true;
  			}  				
  		}
  	if (!q)
  		break;  		
  }

  //cerr << endl << endl;

  int n;
  scanf("%d",&n);

  for (int i = 0; i < n; i++){
  	a[i].first.resize(6);
  	for (int j = 0; j < 6; j++)
  		scanf("%d",&a[i].first[ord[j]]),--a[i].first[ord[j]];
  	norm(a[i].first);
  	//for (int j = 0; j < 6; j++)
  	//	cerr << a[i].first[j] <<" \n"[j==5];
  	a[i].second = i;
  }

  sort(a,a+n);

  vector<vector<int> > ans;

  for (int i = 0; i < n; ){
  	vector<int> temp;
  	int j = i;
  	for (;j < n && a[i].first == a[j].first; j++);
  	for (;i < j; i++)
  		temp.pb(a[i].second);
  	sort(temp.begin(),temp.end());
  	ans.pb(temp);
  }

  sort(ans.begin(),ans.end());

  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++,printf("\n"))
  	for (int j = 0; j < ans[i].size(); j++)
  		printf("%d ",ans[i][j]+1);
  return 0;
}