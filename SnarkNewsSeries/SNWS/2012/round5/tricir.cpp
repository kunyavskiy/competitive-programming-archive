#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "tricir"

using namespace std;

typedef long long ll;
typedef long double ld;

ll r1[1100];
pair<ll,ll> r2[1100];
int ptr1,ptr2;

bool cmp(pair<ll,ll> a,pair<ll,ll> b){
    /*if (a.first <= 1000000 && a.second <= 1000000 && b.first <= 1000000 && b.second <= 1000000)
        return a.first *b.second < a.second * b.first;
    if (a.second == 0)
        return false;
    if (b.second == 0)
        return true;
    ll _a = a.first / a.second;
    ll _b = b.first / b.second;
    if (_a != _b)
        return _a < _b;
    a.first %= a.second;
    b.first %= b.second;   
    swap(a.first,a.second);
    swap(b.first,b.second);
    return cmp(b,a);*/
    return ld(a.first)/a.second < ld(b.first)/b.second-(1e-5);
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

        int n;
        scanf("%d",&n);
        ptr1 = ptr2 = 0;
        for (int i = 0; i < n; i++){
            int t;
            scanf("%d",&t);
            if (t == 1){
                assert(cin >> r1[ptr1]);
                r1[ptr1]*=r1[ptr1];
                ptr1++;
            }
            else {
                ll a,b,c;
                assert(cin >> a >> b >> c);
                if (a < b)
                    swap(a,b);
                if (a < c)
                    swap(a,c);
                pair<ll,ll> res = mp(a*a*b*b*c*c,(a+b+c)*(a-b+c)*(a+b-c)*(-a+b+c));
                if (a*a > b*b+c*c)
                    res = mp(a*a,4);
                r2[ptr2++] = res;
            }
        }

        sort(r1,r1+ptr1);
        sort(r2,r2+ptr2);


//        cerr << r2[0] << endl;


        int ans = 0;
        int ptr3 = 0;
        for (int i = 0; i < ptr2; i++){
//            cerr << r2[i].first <<" "<<r2[i].second <<" "<<r1[ptr3] << endl;
            while(ptr3 < ptr1 && cmp(mp(r1[ptr3],1),r2[i]))
                ptr3++;
            ans += ptr3 < ptr1;
            ptr3++;
        }

        cout << ans << endl;


  	    return 0;
} 