#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

string cur_token;
string next_token;

void nextToken() {
  cur_token = next_token;
  cin >> next_token;
}

string getToken() {
  nextToken();
  return cur_token;
}

string lookupToken() {
  return next_token;
}

int getIntToken() {
  string s = getToken();
  int x;
  sscanf(s.data(), "%d", &x);
  return x;
}

int lookupIntToken() {
  int x;
  sscanf(next_token.data(), "%d", &x);
  return x;
}


struct field {
  enum {optional, required, repeated} rep_type;
  string type_name;
  int id;
};


field get_field() {
  field result;
  string rep_type = getToken();
  if (rep_type == "optional") {
    result.rep_type = field::optional;
  } else if (rep_type == "required") {
    result.rep_type = field::required;
  } else if (rep_type == "repeated") {
    result.rep_type = field::repeated;
  } else {
    assert(false);
  }
  result.type_name = getToken();
  getToken();
  assert(getToken() == "=");
  result.id = getIntToken();
  assert(getToken() == ";");
  return result;
}

struct message {
  string name;
  vector<field> fields;
  bool exists;
};

message get_message() {
  message result;
  assert(getToken() == "message");
  result.name = getToken();
  assert(getToken() == "{");
  while (lookupToken() != "}") {
    result.fields.push_back(get_field());
  }
  assert(getToken() == "}");
  result.exists = false;
  return result;
}


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif
  int n;
  cin >> n;
  cin >> next_token;
  vector<message> messages;
  map<string, int> ids;
  while (lookupToken() == "message") {
    messages.push_back(get_message());
    ids[messages.back().name] = messages.size() - 1;
    sort(messages.back().fields.begin(), messages.back().fields.end(), [](const field &a, const field &b) {
      return a.id < b.id;
    });
  }
  messages.push_back({"double", {}, false});
  ids["double"] = messages.size() - 1;
  messages.push_back({"string", {}, false});
  ids["string"] = messages.size() - 1;

  {
    vector<vector<int>> gr(messages.size());
    vector<int> deg(messages.size());
    queue<int> q;
    for (int i = 0; i < (int)messages.size(); i++) {
      for (const auto &field : messages[i].fields) {
        if (field.rep_type == field::required) {
          gr[ids[field.type_name]].push_back(i);
          deg[i]++;
        }
      }
      if (!deg[i]) {
        q.push(i);
      }
    }


    while (!q.empty()) {
      int id = q.front();
      q.pop();
      messages[id].exists = true;
      for (int u : gr[id]) {
        if (--deg[u] == 0) {
          q.push(u);
        }
      }
    }
  }

  vector<vector<vector<pair<int, int>>>> es(messages.size(), vector<vector<pair<int, int>>>(messages.size()));

  auto compare = [&](int id1, int id2) {
    if (id1 == id2) return false;
    const auto &a = messages[id1];
    const auto &b = messages[id2];
    if (a.exists != b.exists) return true;
    if (!a.exists) return false;
    if (a.name == "string" || a.name == "double") return true;
    if (b.name == "string" || b.name == "double") return true;
    if (a.fields.size() != b.fields.size()) return true;
    for (int i = 0; i < (int)a.fields.size(); i++) {
      int a_id = ids[a.fields[i].type_name];
      int b_id = ids[b.fields[i].type_name];
      if (a.fields[i].id != b.fields[i].id) return true;
      bool a_exists = messages[a_id].exists;
      bool b_exists = messages[b_id].exists;
      if (a_exists != b_exists) return true;
      if (!a_exists) continue;
      if (a.fields[i].rep_type != b.fields[i].rep_type) return true;
      if (a_id == b_id) continue;
      es[a_id][b_id].emplace_back(id1, id2);
    }
    return false;
  };

  vector<vector<bool>> diffrent(messages.size(), vector<bool>(messages.size()));
  queue<pair<int, int>> queue;
  for (int i = 0; i < (int)messages.size(); i++) {
    for (int j = 0; j < (int)messages.size(); j++) {
      diffrent[i][j] = compare(i, j);
      if (diffrent[i][j]) {
        queue.emplace(i, j);
      }
    }
  }

  while (!queue.empty()) {
    int u = queue.front().first;
    int v = queue.front().second;
    queue.pop();
    for (auto x : es[u][v]) {
      if (!diffrent[x.first][x.second]) {
        diffrent[x.first][x.second] = true;
        queue.emplace(x.first, x.second);
      }
    }
  }

  int q = getIntToken();
  for (int i = 0; i < q; i++) {
    string a = getToken();
    string b = getToken();
    printf("Wire-format %scompatible.\n", diffrent[ids[a]][ids[b]] ? "in" : "");
  }


  return 0;
}
