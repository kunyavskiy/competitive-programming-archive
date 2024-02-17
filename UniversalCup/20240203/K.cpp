#include <bits/stdc++.h>

#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using namespace std;


/*
ll pw(ll a, ll b) {
        ll ans = 1; while (b) {
                while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
                ans = (ans * a) % MOD, --b;
        } return ans;
}
*/

vector<string> vv;

void seth(int x, int y) {
  vv[x][y] = vv[x][y + 1] = '#';
}

void setv(int x, int y) {
  vv[x][y] = vv[x + 1][y] = '#';
}

void solve() {
  int n;
  cin >> n;
  vv.clear();
  string tmp = string(n, '.');
  for (int i = 0; i < n; ++i) {
    vv.push_back(tmp);
  }
  n += 1;
  while (n > 7) {
    int l = n;
    int x = 0;
    int y = n - 6;
    while (l % 3 != 0) {
      seth(x, y); seth(x, y + 3);
      x += 2;
      l -= 2;
    }
    while (l > 0) {
      setv(x, y); setv(x, y + 2); setv(x, y + 4);
      x += 3;
      l -= 3;
    }
    l = n - 6;
    x = n - 6;
    y = 0;
    while (l % 3 != 0) {
      setv(x, y); setv(x + 3, y);
      y += 2;
      l -= 2;
    }
    while (l > 0) {
      seth(x, y); seth(x + 2, y); seth(x + 4, y);
      y += 3;
      l -= 3;
    }
    n -= 6;
  }
  if (n == 7) {
    seth(0, 0); seth(2, 0);
    seth(3, 4); seth(5, 4);
    setv(0, 3); setv(0, 5);
    setv(4, 0); setv(4, 2);
  } else if (n == 6) {
    for (int x = 0; x < n; x += 2) {
      for (int y = 0; y < n; y += 3) {
        seth(x, y);
      }
    }
  } else if (n == 5) {
    setv(0, 0); seth(0, 2);
    setv(2, 3); seth(3, 0);
  } else if (n == 4) {
    setv(0, 0); setv(0, 2);
  } else if (n == 3) {
    setv(0, 0);
  }
  for (int i = 0; i < (int)vv.size(); ++i) {
    cout << vv[i] << "\n";
  }
  //cout << "\n";
}


int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cout.setf(ios::fixed), cout.precision(20);
  int tt;
  cin >> tt;
  for (int i = 0; i < tt; ++i) {
    solve();
  }
  return 0;
}

