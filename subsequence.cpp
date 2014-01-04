#include "subsequence.h"

QVector<Actions> Subsequence::getLongestCommonSubsequence(
    const QVector<QString>& FirstFileStrings,
    const QVector<QString>& SecondFileStrings) {
  QVector< QVector<int> > table;
  int FirstSize = FirstFileStrings.size();
  int SecondSize = SecondFileStrings.size();

  table.resize(FirstSize + 1);

  for (int i = 0; i <= FirstSize; i++) {
    table[i].resize(SecondSize + 1);
  }

  for (int i = 0; i <= FirstSize; i++) {
    table[i][0] = 0;
  }
  for (int i = 0; i <= SecondSize; i++) {
    table[0][i] = 0;
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

  QVector<Actions> BackTrack;
  int k = FirstFileStrings.size();
  int l = SecondFileStrings.size();

  for (k, l; table[k][l] != 0 && k > 0 && l > 0; ) {
    if ((table[k][l] > table[k - 1][l]) && (table[k][l] > table[k][l - 1])) {
      BackTrack.push_front(none);
      k--;
      l--;
    } else {
      if (table[k][l] == table[k - 1][l]) {
        BackTrack.push_front(away);
        k--;
      } else {
        BackTrack.push_front(insert);
        l--;
      }
    }
  }
  while ( k != 0 || l != 0) {
    if (l != 0) {
      BackTrack.push_front(insert);
      l--;
    } else if (k != 0) {
      BackTrack.push_front(away);
      k--;
    }
  }
  return BackTrack;
}
