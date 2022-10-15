#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

typedef long long ll;
typedef long double ld;

#define zero(a) memset (a, 0, sizeof(a))
#define pb push_back
#define mp make_pair
#define sz(a) ((int)(a.size()))
#define sqr(a) ((a) * (a))


struct permutation{
    vector<int> v;

    permutation(int sz,const int* a):v(a,a+sz){
    }
    permutation(int sz){
        v.resize(sz);
        for (int i = 0;i < sz; i++)
            v[i] = i;
    }
    permutation(){
    }

    int size() const{
        return v.size();
    }

    int operator[](int id) const{
        return v[id];
    }

    int& operator[](int id){
        return v[id];
    }

    void print(){
        for (int i = 0; i < (int)v.size(); i++)
            cerr << v[i] <<" \t"[i%9 == 8];
        cerr << endl;
    }

};


bool operator==(const permutation& a,const permutation& b){
    assert(a.size() == b.size());   
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}


permutation operator*(const permutation& a,const permutation& b){
    assert(a.size() == b.size());
    permutation c(a.size());
    for (int i = 0;i < (int)a.size(); i++)
        c[i] = b[a[i]];
    return c;
}

permutation operator!(const permutation& a){
    permutation c(a.size());
    for (int i = 0;i < (int)a.size(); i++)
        c[a[i]] = i;
    assert(a*c == permutation(a.size()));
    return c;
}



permutation genrot1(){
    const int _rot1s[6] = {3,0,1,2,4,5};permutation rot1s(6,_rot1s);
    const int _rot1d[9] = {6,3,0,7,4,1,8,5,2};permutation rot1d(9,_rot1d);
    const int _rot1u[9] = {2,5,8,1,4,7,0,3,6};permutation rot1u(9,_rot1u);

    permutation res(54);

    for (int i = 0; i < 9*4; i++)
        res[i] = rot1s[i/9]*9+(i%9);

    for (int i = 0; i < 9; i++)
        res[i+9*5] = rot1d[i]+9*5;

    for (int i = 0; i < 9; i++)
        res[i+9*4] = rot1u[i]+9*4;
        
//  res.print();
    return res; 
}

permutation genrot2(){
    const int _rot2s[6] = {0,5,2,4,1,3};permutation rot2s(6,_rot2s);
    const int _rot2r[9] = {6,3,0,7,4,1,8,5,2};permutation rot2r(9,_rot2r);
    const int _rot2l[9] = {2,5,8,1,4,7,0,3,6};permutation rot2l(9,_rot2l);

    permutation res(54);

    for (int i = 0; i < 9*6; i++)       
        res[i] = rot2s[i/9]*9+(i%9);

    for (int i = 0; i < 9; i++)
        res[i+2*9] = rot2r[i]+2*9;

    for (int i = 0; i < 9; i++)
      res[i+3*9] = 8-i+4*9, res[i+5*9] = 8-i+3*9;;  

    for (int i = 0; i < 9; i++)
        res[i] = rot2l[i];
        
    return res; 
}

permutation rot1 = genrot1();
permutation rot2 = genrot2();


permutation genleft(){
    permutation res = rot2;

    for (int i = 2*9; i < 3*9; i++)
        res[i] = i;
    for (int i = 9; i < 54; i++)
        if (i % 3 != 0 && i/9 != 3)
            res[i] = i;
    for (int i = 27; i < 36; i++)
        if (i % 3 != 2)
            res[i] = i;
     return res;
}


permutation p[255];


bool used[55];


ll gcd(ll a,ll b){
    if (!a || !b)
        return a+b;
    return gcd(b,a%b);
}

ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
}


int main(void)
{
 // freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  p['l'] = genleft();
  p['L'] = !p['l'];
  p['b'] = rot1*p['l']*!rot1;
  p['B'] = !p['b'];
  p['r'] = rot1*p['b']*!rot1;
  p['R'] = !p['r'];
  p['f'] = rot1*p['r']*!rot1;
  p['F'] = !p['f'];

  p['u'] = rot2*p['b']*!rot2;
  p['U'] = !p['u'];
  p['d'] = !rot2*p['b']*rot2;
  p['D'] = !p['d']; 

//  p['b'].print();
  //return 0;


  permutation res(54);

  string s;
  getline(cin,s);

  for (int i = 0; i < (int)s.size(); i++){
    char c=s[i];
    if (c == 'b' || c == 'f')
        c = 'b'+(int)'f'-c;
        if (c == 'B' || c == 'F')
        c = 'B'+(int)'F'-c;
    res = res * p[(int)c];
  }

  ll ans = 1;

  for (int i = 0; i < 54; i++)
    if (!used[i]){
        int cnt = 0;
        for (int j=i;!used[j];j = res[j])
            cnt++,used[j] = true;
        ans = lcm(ans,cnt);
    }

  cout << ans-1 << endl;
  return 0;
}