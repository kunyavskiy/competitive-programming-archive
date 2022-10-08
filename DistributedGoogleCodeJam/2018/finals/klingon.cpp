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
#include "message.h"

#include "klingon.h"

//#define LOCAL


#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

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

void send_vector(int to_node_id, const vector<int> &v) {
  PutInt(to_node_id, (int)v.size());
  for (int x : v) {
    PutInt(to_node_id, x);
  }
  Send(to_node_id);
}

void send_to_all(const vector<int>& v, int nodes, int node_id) {
  for (int i = 0; i < nodes; i++) {
    if (i == node_id) continue;
    send_vector(i, v);
  }
}

void receive_vector(int node_id, vector<int> &v) {
  Receive(node_id);
  int len = GetInt(node_id);
  for (int i = 0; i < len; i++) {
    v.push_back(GetInt(node_id));
  }
}

int res_found = -1;

void sync_res_found(int node_id, int nodes, int main_node_id) {
  if (node_id == main_node_id) {
    for (int i = 0; i < nodes; i++) {
      if (i == node_id) continue;
      Receive(i);
      int x = GetInt(i);
      if (x != -1) {
        res_found = x;
      }
    }
    for (int i = 0; i < nodes; i++) {
      if (i == node_id) continue;
      PutInt(i, res_found != -1);
      Send(i);
    }
    if (res_found != -1) {
      printf("%d\n", res_found);
      exit(0);
    }
  } else {
    PutInt(main_node_id, res_found);
    Send(main_node_id);
    Receive(main_node_id);
    if (GetInt(main_node_id) == 1) {
      exit(0);
    }
  }
}


int check_vector(const vector<int>& a, const vector<int> &w) {
  for (int x : a) {
    assert(Answer(x) == 0);
  }
  int ts = 0;
  int res;

  int x = 0;
  while (x < (int)w.size() && (res = Answer(w[x])) == 0) {
    ts++;
    x++;
  }
  if (res == -1) {
    return ts;
  }
  while ((res = Answer(0)) == 0) {
    ts++;
  }
  if (res != -1) {
    res_found = res;
  }

  return ts;
}

void merge_vectors(int node_id, int nodes, int main_node_id, vector<int> &v) {
  if (node_id != main_node_id) {
    send_vector(main_node_id, v);
    v.clear();
    receive_vector(main_node_id, v);
  } else {
    vector<int> nv;
    for (int i = 0; i < nodes; i++) {
      if (i == node_id) {
        nv.insert(nv.end(), v.begin(), v.end());
        continue;
      }
      receive_vector(i, nv);
    }
    v = nv;
    send_to_all(v, nodes, node_id);
  }
}

int main() {
  int nodes = NumberOfNodes();
  int node_id = MyNodeId();
  int q = (int)GetNumberOfQuestions();
  int w = (int)GetAllowedNumberOfWrongAnswers();
  int a = (int)GetNumberOfPossibleAnswers();

  vector<int> answers;

  int main_node_id = 0;

#ifdef LOCAL
  int start = clock();
#endif


  while ((int)answers.size() + w < q) {
    int from = a * node_id / nodes;
    int to = a * (node_id + 1) / nodes;
    int fromq = w * node_id / nodes;
    int toq = w * (node_id + 1) / nodes;
    int fromq2 = (w+1) * node_id / nodes;
    int toq2 = (w+1) * (node_id + 1) / nodes;


    vector<int> rnd(w + 1);
    do {
      for (int i = 0; i <= w; i++) {
        rnd[i] = rand() % a;
      }
    } while (check_vector(answers, rnd) <= w && res_found == -1);

    sync_res_found(node_id, nodes, main_node_id);

    int val = check_vector(answers, rnd);

    vector<int> wrong;

    for (int i = fromq2; i < toq2 && res_found == -1; i++) {
      int old_val = rnd[i];
      rnd[i] = (rnd[i] + 1) % a;
      int nval = check_vector(answers, rnd);
      if (nval < val) {
        wrong.push_back(rnd[i]);
      } else {
        wrong.push_back(old_val);
      }
      rnd[i] = old_val;
    }

    merge_vectors(node_id, nodes, main_node_id, wrong);
    sync_res_found(node_id, nodes, main_node_id);

    vector<int> exists;
    for (int i = from; i < to; i++) {
      for (int x : answers) {
        assert(Answer(x) == 0);
      }
      int ts = 0;
      int res;
      while ((res = Answer(i)) == 0) {
        ts++;
      }
      if (res != -1) {
        res_found = res;
        break;
      }
      if (ts != w) {
        exists.push_back(i);
      }
    }

    merge_vectors(node_id, nodes, main_node_id, exists);
    sync_res_found(node_id, nodes, main_node_id);

    vector<int> my_answers;

    vector<int> exists2;

    for (int v : exists) {
      for (int x : answers) {
        assert(Answer(x) == 0);
      }
      for (int i = 0; i < w; i++) {
        assert(Answer((fromq <= i && i < toq) ? v : wrong[i]) == 0);
      }
      if (Answer(wrong[w]) != -1) {
        int res;
        while ((res = Answer(0)) != -1) {
          if (res != 0) {
            res_found = res;
            break;
          }
        }
        exists2.push_back(v);
      }
    }


    for (int pos = fromq; pos < toq; pos++) {
      for (int v : exists2) {
        for (int x : answers) {
          assert(Answer(x) == 0);
        }
        for (int i = 0; i < w; i++) {
          assert(Answer(i == pos ? v : wrong[i]) == 0);
        }
        if (Answer(wrong[w]) != -1) {
          int res;
          while ((res = Answer(0)) != -1) {
            if (res != 0) {
              res_found = res;
              break;
            }
          }
          my_answers.push_back(v);
          break;
        }
      }
      if ((int)my_answers.size() != pos - fromq + 1) {
        fprintf(stderr, "no answer for pos = %d!\n", pos);
        assert(0);
      }
    }


    if (node_id != main_node_id) {
      send_vector(main_node_id, my_answers);
      receive_vector(main_node_id, answers);
    } else {
      int old_size = answers.size();
      for (int i = 0; i < nodes; i++) {
        if (i != node_id) {
          Receive(i);
          int t = GetInt(i);
          for (int j = 0; j < t; j++) {
            answers.push_back(GetInt(i));
          }
        } else {
          answers.insert(answers.end(), my_answers.begin(), my_answers.end());
        }
      }
      send_to_all(vector<int>(answers.begin() + old_size, answers.end()), nodes, node_id);
    }

    sync_res_found(node_id, nodes, main_node_id);
    ++main_node_id;
#ifdef LOCAL
    fprintf(stderr, "answers.size() = %d, tm = %.2lf, ans_called = %d\n", (int)answers.size(), (clock() - start) *1.0/ CLOCKS_PER_SEC, called);
#endif

  }

  if (node_id == 0) {
    int res = 0;
    for (int i = 0; i < q; i++) {
      if (i < (int)answers.size()) {
        res = Answer(answers[i]);
      } else {
        res = Answer(0);
      }
      assert(res != -1);
    }
    assert(res != 0);
    printf("%d\n", res);
  }

  return 0;
}
