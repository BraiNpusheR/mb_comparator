#ifndef PARSEDATA_H
#define PARSEDATA_H

#include "subsequence.h"

#include <QObject>
#include <QStringList>
#include <QVector>

class ParseData : public QObject
{
  Q_OBJECT
public:
  explicit ParseData(QObject *parent = 0);

signals:

public slots:
  void setLeftText(const QStringList& text);
  void setRightText(const QStringList& text);
  void setCompareResult(const QVector<Actions>& comp_res);
  QVector<QString> Parsing();

private:
  QStringList left_text_;
  QStringList right_text_;
  QVector<Actions> compare_result_;
};

#endif // PARSEDATA_H
