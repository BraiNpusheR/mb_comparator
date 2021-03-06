#include "subsequence.h"

Subsequence::Subsequence(QObject *parent) :
    QObject(parent){}

void Subsequence::setLeftText(const QStringList& left_text) {
  left_text_ = left_text;
}

void Subsequence::setRightText(const QStringList& right_text) {
  right_text_ = right_text;
}


QVector<Actions> Subsequence::findLCS() {
  QVector< QVector<int> > table;
  int FirstSize = left_text_.size();
  int SecondSize = right_text_.size();

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
      if (left_text_.at(i - 1) == right_text_.at(j - 1)) {
        table[i][j] = table[i - 1][j - 1] + 1;
      } else {
        table[i][j] = qMax(table[i - 1][j], table[i][j - 1]);
      }
    }
  }

  QVector<Actions> BackTrack;
  int k = left_text_.size();
  int l = right_text_.size();

  for (k, l; table[k][l] != 0 && k > 0 && l > 0; ) {
    if ((table[k][l] > table[k - 1][l]) && (table[k][l] > table[k][l - 1])) {
      BackTrack.push_front(none);
      k--;
      l--;
    } else {
      if (table[k][l] == table[k][l-1]) {
        BackTrack.push_front(insert);
        l--;
      } else {
        BackTrack.push_front(away);
        k--;
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
