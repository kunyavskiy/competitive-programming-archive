/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define next next1234

typedef long long ll;

const int LEN = 1 << 10, N = 1e5 + LEN, K = N / LEN;

struct Set;

int next[N];
Set *p[N];

struct List {
  int head, tail;
  ll sum;
  List() { head = tail = -1, sum = 0; }
  void join( List l ) {
    if (head == -1)
      head = l.head, tail = l.tail;
    else if (l.head != -1) {
      //printf("heads : %d, %d; tails : %d %d\n", head, l.head, tail, l.tail);
      next[tail] = l.head, tail = l.tail;
    }
    sum += l.sum;
  } 
  void add( int i ) {
    if (head == -1)
      sum = head = tail = i, next[i] = -1;
    else
      sum += i, next[i] = head, head = i;
  }
  void owner( Set *s ) {
    if (head != -1)
      p[tail] = s;
  }
  void out() {
    if (head == -1)
      return;
    for (int i = head; i != -1; i = next[i])
      printf("%d ", i);
    puts("");
  }
};

vector<int> tmp;

struct Set {
  List l[K];
  ll all_sum;
  Set() : all_sum(0) { }
  void add( int i ) {
    l[i / LEN].add(i);
    l[i / LEN].owner(this);
    all_sum += i;   
  }
  void join( Set *s ) {
    forn(i, K)
      l[i].join(s->l[i]), l[i].owner(this);
    all_sum += s->all_sum;
  }
  void split( int k, Set *suf ) { // < k, >= k
    all_sum = suf->all_sum = 0;
    forn(i, K) {
      if ((i + 1) * LEN <= k)
        suf->l[i] = List();
      else if (k <= i * LEN)
        suf->l[i] = l[i], l[i] = List();
      else {
        List a, b;
        tmp.clear();
        for (int x = l[i].head; x != -1; x = next[x]) 
          tmp.push_back(x);
        for (int x : tmp) {
          //printf("check %d < %d\n", x, k);
          (x < k ? a : b).add(x);
        }
        l[i] = a, suf->l[i] = b;
        //a.out();
        //b.out();
      }
      l[i].owner(this);
      suf->l[i].owner(suf);
      all_sum += l[i].sum;
      suf->all_sum += suf->l[i].sum;
    }
  }
};

Set *get( int i ) {
  //printf("get %d : ", i);
  while (next[i] != -1)
    i = next[i];
  //printf("tail = %d, set = %p\n", i, p[i]);
  return p[i];
}

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  struct Query {
    int t, a, b;
    char type;
    bool operator < ( const Query &q ) const { return t < q.t; }
  } a[m + q];
  forn(i, m + q)
    if (i < m) 
      scanf("%d %c%d%d", &a[i].t, &a[i].type, &a[i].a, &a[i].b);
    else
      scanf("%d%d", &a[i].t, &a[i].a), a[i].type = '?';
  q += m;
  sort(a, a + q);
  for (int i = 1; i <= n; i++)
    (new Set())->add(i);
  vector<Set *> free(1, new Set());
  for (auto z : a)
    if (z.type == '?')
      printf("%lld\n", get(z.a)->all_sum);
    else if (z.type == 'U') {
      Set *sa = get(z.a), *sb = get(z.b); 
      if (sa != sb)
        sa->join(sb), free.push_back(sb);
    } else {
      assert(free.size());
      Set *s1 = get(z.a), *s2 = free.back();
      free.pop_back();
      s1->split(z.b, s2);
      if (!s1->all_sum) free.push_back(s1);
      if (!s2->all_sum) free.push_back(s2);
    }
}

