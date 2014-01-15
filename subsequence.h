#ifndef SUBSEQ_H
#define SUBSEQ_H

#include <QObject>
#include <QStringList>
#include <QVector>

enum Actions {
  none = 0, insert, away
};

class Subsequence : public QObject
{
  Q_OBJECT
public:
  explicit Subsequence(QObject *parent = 0);
  void setLeftText(const QStringList& left_text);
  void setRightText(const QStringList& right_text);

signals:

public slots:
  QVector<Actions> findLCS();

private:
  QStringList left_text_;
  QStringList right_text_;
};

#endif // SUBSEQ_H
