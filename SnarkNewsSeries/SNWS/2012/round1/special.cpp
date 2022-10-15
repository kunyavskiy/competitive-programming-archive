#include <iostream>
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

#define taskname "special"

using namespace std;

typedef long long int64;
typedef long double ld;

const int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int dinm(int m,int y){
    return days[m] + (m == 2 && (y%400 == 0 || (y %4 == 0 && y % 100 != 0)));
}

void next(int& d,int& m,int& y){
    d++;
    if (d == dinm(m,y)+1){
        d = 1;
        m++;
        if (m == 13){
            m = 1;
            y++;
        }
    }
}


string str(int a,int b){
    if (b == 2)
        a %= 100;
    char buf[10];
    sprintf(buf,"%0*d",b,a);
    return buf;
}

bool check(string s){   
    int sz = s.size();
    bool ok = true;
    for (int i = 0; i < sz; i++)
        ok &= s[i] == s[sz-i-1];

    if (ok)
        return true;
    for (int i = 1; i < sz; i++)
        if (sz % i == 0){
            ok = true;
            for (int j = 0; j+i < sz; j++)
                ok &= s[j] == s[i+j];            
            if (ok)
                return true;
        }
    return false;    
}

bool check(int d,int m,int y){
    if (check(str(d,2)+str(m,2)+str(y,2)))
        return true;
    if (check(str(d,2)+str(m,2)+str(y,4)))
        return true;

    if (check(str(d,1)+str(m,2)+str(y,2)))
        return true;
    if (check(str(d,1)+str(m,2)+str(y,4)))
        return true;


    if (check(str(d,2)+str(m,1)+str(y,2)))
        return true;
    if (check(str(d,2)+str(m,1)+str(y,4)))
        return true;


    if (check(str(d,1)+str(m,1)+str(y,2)))
        return true;
    if (check(str(d,1)+str(m,1)+str(y,4)))
        return true;
    return false;
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

        int d,m,y;
        cin >> d >> m >> y;

        for (;!check(d,m,y);next(d,m,y));
        cout << d << " "<<m <<" "<< y << endl;
    	return 0;
} 