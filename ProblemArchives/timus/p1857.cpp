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


struct tlong{

  static const int base;
  static const int baselen;
    
    vector<int> c;

    int& back(){
        return c.back();
    }
    int back() const{
        return c.back();
    }

    void push_back(int x){
        c.pb(x);
    }

    void pop_back(){
        c.pop_back();
    }

    int& operator[](int id){
        return c[id];
    }


    int operator[](int id) const{
        return c[id];
    }

    int size() const{
        return c.size();
    }

    void mult(int n){
            ll p = 0;
          for (int i = 0; i < (int)c.size() || p; i++){
            if (i == (int)c.size())
                c.pb(0);
            p = p + c[i]*1LL*n;
            c[i] = p % base;
            p /= base;
          }
    }

    void divide(int n){
            ll p = 0;
            for (int i = (int)c.size() - 1; i >= 0; --i){
                p += c[i];
                c[i] = p/n;
                p %= n;
                p *= base;
            }
            for (;c.size() > 1 && c.back() == 0; c.pop_back());     
    }

    void add(const tlong& r){
            int p = 0;
            int sz = r.size();
            for (int i = 0; i < sz || i < (int)c.size() || p; i++){
                    if (i < sz)
                        p += r[i];
                  if (i == (int)c.size())
                    c.pb(0);
                  p += c[i];
                  c[i] = p % base;
                  p /= base;
            }
    }


    void dec(const tlong& r){
            int p = 0;
            int sz = r.size();
            for (int i = 0; i < sz || p; i++){
                    if (i < sz)
                        p -= r[i];
                  p += c[i];
                  c[i] = (p +base)% base;
                  if (p < 0)
                    p = -1;
                  else
                    p = 0;
            }       
            for (;c.size() > 1 && c.back() == 0; c.pop_back());     
    }


  void print(){
            printf("%d",c.back());
            for (int i = (int)c.size() -2; i >= 0; --i)
                printf("%0*d",baselen,c[i]);
            printf("\n");
  }       
};

const int tlong::base = 1000000000;
const int tlong::baselen = 9;



tlong t[11000];





int main(void)
{
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
  int a,n;
  scanf("%d %d",&a,&n);
  t[1].pb(a);

  for (int i = 2; i <= n; i++){
    t[i] = t[i-1];
    t[i].mult(a);
  }

  for (int i = 1; i <= n; i++){
//      t[i].print();

    tlong dk = t[i];
    for (int j = 2*i; j <= n; j+= i)
        t[j].dec(dk);
  }

  t[n].divide(n);
  t[n].print();

  return 0;
}