/**
 *    author:  tourist
 *    created: 09.05.2021 11:47:14       
**/
#undef _GLIBCXX_DEBUG
//#define LOCAL

#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

void test(vector<string> start, vector<string> finish, vector<string> seq) {
  int sz = (int) start.size();
  vector<pair<int, int>> p(sz);
  vector<int> st(start.size());
  iota(st.begin(), st.end(), 0);
  for (string op : seq) {
    if (op == "copy") {
      if (st.size() < 1) {
        return;
      }
      st.push_back(st.back());
    }
    if (op == "swap") {
      if (st.size() < 2) {
        return;
      }
      swap(st[st.size() - 1], st[st.size() - 2]);
    }
    if (op == "roll") {
      if (st.size() < 3) {
        return;
      }
      swap(st[st.size() - 2], st[st.size() - 3]);
      swap(st[st.size() - 1], st[st.size() - 2]);
    }
    if (op == "fuse") {
      if (st.size() < 2) {
        return;
      }
      p.emplace_back(st[st.size() - 2], st[st.size() - 1]);
      st.pop_back();
      st.pop_back();
      st.push_back((int) p.size() - 1);
    }
  }
  if (st.size() < finish.size()) {
    return;
  }
  for (int i = 0; i < (int) finish.size(); i++) {
    string got = "";
    function<void(int)> Dfs = [&](int v) {
      if (v < (int) start.size()) {
        got += start[v];
        return;
      }
      Dfs(p[v].first);
      Dfs(p[v].second);
    };
    Dfs(st[st.size() - finish.size() + i]);
    if (got != finish[i]) {
      return;
    }
  }
  debug("ok!", seq.size(), seq, st, p);
  exit(0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  for (int len = 1; ; len++) {
    vector<string> ops = {"copy", "swap", "roll", "fuse"};
    for (int t = 0; t < (1 << (2 * len)); t++) {
      vector<string> seq;
      for (int i = 0; i < len; i++) {
        int id = (t >> (2 * i)) & 3;
        seq.push_back(ops[id]);
      }
      test({"a", "b"}, {"bb", "b", "a"}, seq);
    }
    debug(len, "not found");
  }
  return 0;
}
