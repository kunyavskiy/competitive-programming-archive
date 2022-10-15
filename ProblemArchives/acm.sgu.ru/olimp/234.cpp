#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define mlen 200010

int n, len, num[mlen], sum[mlen];
char s[mlen], s1[mlen], t[mlen];

int p[mlen], code[mlen], q[mlen], ncode[mlen];
int tr[mlen * 2];

int TGet( int l, int r )
{
  if (l > r)
    swap(l, r);
  r--;
  l += n, r += n;
  int mi = (int)1e9;
  while (l <= r)
  {
    if (l & 1)
      mi <?= tr[l++];
    if (!(r & 1))
      mi <?= tr[r--];
    if (l > r)
      break;
    l >>= 1, r >>= 1;
  }
  return mi;
}

int main()
{
  int i, k;
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
  gets(s);
  len = strlen(s);
  for (i = 0; i < len; i++)
    s1[i] = s[len - i - 1];
  s1[len] = 0;
  sprintf(t, "$%s#%s!", s, s1);
  n = strlen(t);

  memset(num, 0, sizeof(num));
  for (i = 0; i < n; i++)
    num[t[i]]++;
  sum[0] = 0;
  for (i = 0; i < mlen; i++)
    sum[i + 1] = sum[i] + num[i];
  for (i = 0; i < n; i++)
    p[sum[t[i]]++] = i, code[i] = t[i];
  for (k = 1; k < n; k *= 2)
  {
    memset(num, 0, sizeof(num));
    for (i = 0; i < n; i++)
      num[code[i]]++;
    sum[0] = 0;
    for (i = 0; i < max(n, 256); i++)
      sum[i + 1] = sum[i] + num[i];
    for (i = 0; i < n; i++)
      q[sum[code[(p[i] - k + n) % n]]++] = p[i];

    int cc = 0;
    for (i = 0; i < n; i++)
    {
      if (i && (code[q[i]] != code[q[i - 1]] || code[(q[i] - k + n) % n] != code[(q[i - 1] - k + n) % n]))
        cc++;
      ncode[i] = cc;
    }
    for (i = 0; i < n; i++)
      p[i] = q[i], code[p[i]] = ncode[i];
  }
  for (i = 0; i < n; i++)
    p[i] = (p[i] - k + 1 + n * 2) % n;
  for (i = 0; i < n; i++)
    q[p[i]] = i;

  for (i = 1; i < n; i <<= 1)
    ;
  for (k = i = 0; i < n; i++)
  {
    if (k)
      k--;
    if (q[i] < n)
      while (k < n && t[i + k] == t[p[q[i] + 1] + k])
        k++;
    tr[n + q[i]] = k;
  }
  for (i = n - 1; i > 0; i--)
    tr[i] = min(tr[i + i], tr[i + i + 1]);

  long long ans = 0;
  for (i = 0; i < len; i++)
    ans += max(0, TGet(q[i + 1], q[len * 2 - i + 1]) - 1);
  for (i = 0; i < len - 1; i++)
    ans += TGet(q[i + 2], q[len * 2 - i + 1]);
  cout << ans;

  return 0;
}