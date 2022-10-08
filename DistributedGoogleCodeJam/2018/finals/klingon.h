// Sample input 3, in CPP.
#include <assert.h>

typedef long long ll;

static int correct_answers[25000] = {};

static void init() __attribute__((constructor));

static void init() {
  for (int i = 0; i < 25000; i++) {
    correct_answers[i] = rand() % 50000;
  }
}

static int current_question;
static int number_of_wrong_answers;
static int done;

ll GetNumberOfQuestions() {
  return 25000;
}

ll GetAllowedNumberOfWrongAnswers() {
  return 3000;
}

ll GetNumberOfPossibleAnswers() {
  return 50000;
}



int called;

int Answer(ll answer) {
  ++called;
  assert(answer >= 0 && answer < GetNumberOfPossibleAnswers());
  if (done) return 0;
  if (answer != correct_answers[current_question]) {
    number_of_wrong_answers += 1;
  }
  current_question += 1;
  if (number_of_wrong_answers > GetAllowedNumberOfWrongAnswers()) {
    number_of_wrong_answers = 0;
    current_question = 0;
    return -1;
  }
  if (current_question == GetNumberOfQuestions()) {
    done = 1;
    return 42;
  }
  return 0;
}
