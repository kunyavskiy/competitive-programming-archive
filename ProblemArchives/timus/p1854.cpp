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

int main(void)
{
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
  ll n;
  cin >> n;

  while (n%2 == 0)
    n /= 2;

  ll ans = 1;

  for (ll i = 2; i*i*i <= n; i++){
     while (n % (i*i) == 0){
            n /= (i*i);
            ans *= i;
     }
     if (n % i == 0)
            n /= i;         
  }

  ll sq = sqrt(n*1.0);
  while (sq * sq > n)
    --sq;
  while ((sq+1)*(sq+1) <= n)
    ++sq;

  if (sq*sq == n)
    ans *= sq;

    cout << ans*ans << endl;

  return 0;
}