#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "c"

const int inf = 1000000000;
const ld eps = 1e-9;


vector<pair<ll,ll> > get(ll p,ll q){
	vector<ll> a;
	for (;q;){
		a.pb(p/q);
		p %= q;
		swap(p,q);
	}	
	vector<pair<ll,ll> > v;
	v.pb(mp(0,1));
	v.pb(mp(1,0));
	int sz = 2;

	for (int i = 0; i < (int)a.size(); i++){
		v.pb(mp(v[sz-1].first * a[i] + v[sz-2].first,v[sz-1].second * a[i] + v[sz-2].second));
		sz++;
	}
	return v;
}

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

void norm(ll& a,ll&b){
	ll g = gcd(a,b);
	a /= g;
	b /= g;
}

bool solve(){
	ll p1,q1,p2,q2;

	if (scanf(LLD" "LLD" "LLD" "LLD,&p1,&q1,&p2,&q2) != 4)
		return false;

	norm(p1,q1);
	norm(p2,q2);

	//cerr<<p1<<" "<<p2<<" "<<q1<<" "<<q2<<endl;
	vector<pair<ll,ll> > a = get(p1,q1);
	//cerr<<p1<<" "<<p2<<" "<<q1<<" "<<q2<<endl;
	vector<pair<ll,ll> > b = get(p2,q2);


	//cerr<<p1<<" "<<p2<<" "<<q1<<" "<<q2<<endl;
	int i;
	for (i = 0; i < (int)a.size() && i < (int)b.size(); i++){
		if (a[i] != b[i]){
			if (a[i] != mp(p1,q1) && b[i] != mp(p2,q2)){			    
				if (a[i].second < b[i].second){
					printf(LLD" "LLD"\n",a[i].first+a[i-1].first,a[i].second+a[i-1].second);
					return true;
				}
				if (a[i].second > b[i].second){
					printf(LLD" "LLD"\n",b[i].first+b[i-1].first,b[i].second+b[i-1].second);
					return true;
				}
				printf(LLD" "LLD"\n",min(a[i].first,b[i].first)+b[i-1].first,b[i].second+b[i-1].second);
				return true;
			}
		//cerr<<a[i].first<<" "<<a[i].second<<endl;	
		   if (a[i]>b[i]){
		     swap(a[i],b[i]);
		     swap(a[i-1],b[i-1]);
		     swap(p1,p2), swap(q1,q2);
		   }
		   pair <ll, ll> nd=mp(b[i].first,b[i].second);

		   /*cerr << a[i].first << " "<<a[i].second <<" "<<b[i].first <<" "<<b[i].second <<endl;
		   cerr << a[i-1].first << " "<<a[i-1].second <<" "<<b[i-1].first <<" "<<b[i-1].second <<endl;
		   cerr << a[i+1].first << " "<<a[i+1].second <<" "<<b[i+1].first <<" "<<b[i+1].second <<endl;*/
		   //cerr <<nd.first <<" "<<nd.second<<"   "<<p2<<" "<<q2<<endl;
		   //cerr<<p1<<" "<<q1<<" "<<i<<"    "<<nd.first<<" "<<nd.second<<endl;
		   if (nd!=mp(p2,q2) && mp(p2,q2)!=mp(nd.first+b[i-1].first,nd.second+b[i-1].second))
		   {
		     printf(LLD" "LLD"\n", nd.first+b[i-1].first,nd.second+b[i-1].second);
		     return 1;
		   }
		   ll a=p1+p2, b=q1+q2, c=gcd(a,b);
		   a/=c, b/=c;
		   printf(LLD" "LLD"\n", a,b);
		   return 1;
		   //assert(b[i]!=b[i+1]);
		   /*if (b[i]!=b[i+1])
		     printf(LLD" "LLD"\n", b[i+1].first,b[i+1].second);
		   else
		     printf(LLD" "LLD"\n", p1+p2,q1+q2);
		   return 1;*/
		   assert(0);
		}
	}
	pair <ll, ll> tres;
	if (i==(int)a.size())
	{
	  
	  tres=b[i];
	  //cerr<<"!!! "<<tres.first<<" "<<tres.second<<endl;
	  if (mp(tres.first+b[i-1].first,tres.second+b[i-1].second)==mp(p2,q2) || mp(p2,q2)==tres)
	  {
		   ll a=p1+p2, b=q1+q2, c=gcd(a,b);
		   a/=c, b/=c;
		   printf(LLD" "LLD"\n", a,b);
	    return 1;
	  }
	  else
	  {
	    printf(LLD" "LLD"\n", tres.first+b[i-1].first,tres.second+b[i-1].second);
	    return 1;
	  }
	}
	tres=a[i];
	  if (mp(tres.first+a[i-1].first,tres.second+a[i-1].second)==mp(p1,q1)  || mp(p1,q1)==tres)
	  {
		   long long a=p1+p2, b=q1+q2, c=gcd(a,b);
		   a/=c, b/=c;
		   printf(LLD" "LLD"\n", a,b);
	    return 1;
	  }
	  else
	  {
	    printf(LLD" "LLD"\n", tres.first+a[i-1].first,tres.second+a[i-1].second);
	    return 1;
	  }

	//if (a.size() == b.size())
	//    printf(LLD" "LLD"\n", p1+p2,q1+q2);

	//assert(0);
	return 0;

}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  while (solve())
  {
    //break;
  }
  return 0;
}

