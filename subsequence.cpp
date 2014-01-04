#include <iostream>
#include <string>
#include <vector>

enum Actions {
  none = 0, insert, away
};

class Subsequence {
public:
  std::vector<Actions> getLongestCommonSubsequence(std::vector <std::string> FirstFileStrings,
      std::vector <std::string> SecondFileStrings);
};

std::vector<Actions> Subsequence::getLongestCommonSubsequence(std::vector <std::string> FirstFileStrings,
    std::vector <std::string> SecondFileStrings) {
  std::vector< std::vector <int> > table;
  int FirstSize = static_cast<int>(FirstFileStrings.size());
  int SecondSize = static_cast<int>(SecondFileStrings.size());
  std::vector<Actions> BackTrack;

  table.resize(FirstSize + 1);

  for (int i = 0; i <= FirstSize; i++) {
    table[i].resize(SecondSize + 1);
  }

  for (int i = 0; i <= FirstSize; i++) {
    table[0][i] = 0;
  }
  for (int i = 0; i <= SecondSize; i++) {
    table[i][0] = 0;
  }

  for (int i = 1; i <= FirstSize; i++) {
    for (int j = 1; j <= SecondSize; j++) {
      if (FirstFileStrings[i - 1] == SecondFileStrings[j - 1]) {
        table[i][j] = table[i - 1][j - 1] + 1;
      } else {
        table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
      }
    }
  }

  int k = FirstFileStrings.size();
  int l = SecondFileStrings.size();

  for (k, l; table[k][l] != 0 && k > 0 && l > 0; ) {
    if ((table[k][l] > table[k - 1][l]) && (table[k][l] > table[k][l - 1])) {
      BackTrack.push_back(none);
      k--;
      l--;
    } else {
      if (table[k][l] == table[k - 1][l]) {
        BackTrack.push_back(away);
        k--;
      } else {
        BackTrack.push_back(insert);
        l--;
      }
    }
  }
  while ( k != 0 || l != 0) {
    if (l != 0) {
      BackTrack.push_back(insert);
      l--;
    } else if (k != 0) {
      BackTrack.push_back(away);
      k--;
    }

  }
  return BackTrack;
}


int main() {
  Subsequence mySub;
  std::vector <std::string> first;
  std::vector <std::string> second;

  std::vector<Actions>  BackTrack;

  first.push_back("g");
  first.push_back("t");
  first.push_back("h");
  first.push_back("s");
  first.push_back("o");
  first.push_back("d");
  first.push_back("t");

  second.push_back("t");
  second.push_back("r");
  second.push_back("g");
  second.push_back("m");
  second.push_back("t");
  second.push_back("h");
  BackTrack = mySub.getLongestCommonSubsequence(first, second);
  return 0;
}