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

typedef long long ll;
typedef long double ld;
                 
#define taskname "1668"

#undef assert
//#define assert(x) if (!(x)) throw 1
#define assert(x) ;


const ld eps = 1e-7;

struct vect{
  vector<ld> v;

  void read(int n){
  	v.resize(n);
  	for (int i = 0; i < n; i++)
  		cin >> v[i];
  }

  ld& operator[](int a){
  	return v[a];
  }

  ld operator[](int a) const{
  	return v[a];
  }

  int size() const{
  	return v.size();
  }

  void resize(int n){
  	v.resize(n);
  }
  
};

vect operator+(const vect& a,const vect& b){
	assert(a.size() == b.size());
	vect res;
	res.v.resize(a.size());
	for (int i = 0; i < a.size(); i++)
		res[i] = a[i]+b[i];
  return res;
}

vect operator*(const vect& a,ld b){
	vect res;
	res.v.resize(a.size());
	for (int i = 0; i < a.size(); i++)
		res[i] = a[i] * b;
	return res;
}



vect operator/(const vect& a,ld b){
	vect res;
	res.v.resize(a.size());
	for (int i = 0; i < a.size(); i++)
		res[i] = a[i] / b;
	return res;
}



vect operator-(const vect& a,const vect& b){
	assert(a.size() == b.size());
	vect res;
	res.v.resize(a.size());
	for (int i = 0; i < a.size(); i++)
		res[i] = a[i]-b[i];
  return res;
}


ld operator*(const vect& a,const vect& b){
	assert(a.size() == b.size());
	ld res = 0;
	for (int i = 0; i < a.size(); i++)
		res += a[i]*b[i];
	return res;	
}

ld len(const vect& a){
	return sqrt(a*a);
}

ld len2(const vect& a){
	return a*a;
}


typedef vector<vect> basis;



void normalize(basis& b,vector<vect> &c){	

	vect temp;
	temp.resize(b.size());
	for (int i = 0; i < (int)b.size(); i++){
	    temp[i] = 1;
	    c.pb(temp);
	    temp[i] = 0;
	}

	
	for (int i = 0; i < (int)b.size(); i++)
		if (fabs(len(b[i])) > eps)
			for (int j = i+1; j < (int)b.size(); j++){
				ld coef = b[i]*b[j]/len2(b[i]);
				c[j] = c[j] - c[i]*coef;
				b[j] = b[j] - b[i]*coef;
				assert(fabs(b[i]*b[j]) < eps);
			}

	for (int i = 0; i < (int)b.size(); i++)
		if (abs(len(b[i])) > eps){
			c[i] = c[i] / len(b[i]);
			b[i] = b[i] / len(b[i]);
		}	

	for (int i = 0; i < (int)b.size(); i++)
		for (int j = i+1; j < (int)b.size(); j++)
			assert(fabs(b[i]*b[j]) < eps);
}

vect proec(basis b,vect v){
	vector<vect> b0 = b;
	vector<vect> c;
	normalize(b,c);
	vector<vect> _b = b;
	vect res = v;
	vect res2;
	res2.resize(b.size());
	for (int i = 0; i < (int)b.size(); i++){
		ld coef = res*b[i];
		res2 = res2 + c[i] * coef;					
		res = res - b[i] * coef;		
	}
	for (int i = 0; i < (int)b.size(); i++)
		assert(fabs(res*b[i]) < eps);
	//cout << len(res) << endl;
	vect temp;
	temp.resize(v.size());
	for (int i = 0; i < b0.size(); i++)
		temp = temp + b0[i] * res2[i];
	temp = temp + res;

	for (int i = 0; i < b.size(); i++)
		assert(fabs(temp[i] - v[i]) < eps);

	return res2;
}


basis getbasis(basis _a){
	basis a = _a;
	vector<vect> b;
	basis res;
	vect temp;
	temp.resize(a.size());
	for (int i = 0; i < (int)a.size(); i++){
	    temp[i] = 1;
	    b.pb(temp);
	    temp[i] = 0;
	}

	for (int i = 0; i < (int)a.size(); i++){
		int id = -1;
		for (int j = 0; j < a[0].size(); j++)
			if (fabs(a[i][j]) > eps){
				id = j;
				break;
			}
		if (id == -1){
			res.pb(b[i]/len(b[i]));
			continue;
		}
		for (int j = 0; j < (int)a.size(); j++)
			if (i != j){
				ld coef = a[j][id] / a[i][id];
				a[j] = a[j] - a[i]*coef;
				b[j] = b[j] - b[i]*coef;
			}
	}
	return res;
}

int n,m;


int main(){
    #ifdef LOCAL
	  assert(strlen(taskname) > 0);
	  freopen(taskname".in","r",stdin);
	  freopen(taskname".out","w",stdout);
	#endif
	  scanf("%d %d",&n,&m);
	  basis b;
	  b.resize(m);
	  for (int i = 0; i < (int)b.size(); i++){
	  	b[i].v.resize(n);
	  	for (int j = 0; j < n; j++)
	  		cin >> b[i][j];
	  }

	  vect v;
	  v.resize(n);
	  for (int i = 0; i < n; i++)
	  	cin >> v[i];

	  vect rasl = proec(b,v);
	  basis nulls = getbasis(b);
	  rasl = rasl * -1;
	  vect radd = proec(nulls,rasl);
	  rasl = rasl * -1;
	  
	  for (int i = 0; i < (int)nulls.size(); i++)
	  	rasl = rasl + nulls[i] * radd[i];
	  cout.precision(15);
	  for (int i = 0; i < m; i++)
	  	cout<<fixed<<rasl[i] <<" \n"[i==m-1];
    return 0;
}
