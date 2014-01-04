#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include <vector>
#include <QString>
#include <QVector>

enum Actions {
  none = 0, insert, away
};

class Subsequence {
public:
  static QVector<Actions> getLongestCommonSubsequence(const QVector<QString>&,
                                                      const QVector<QString>&);
};

#endif // SUBSEQUENCE_H
