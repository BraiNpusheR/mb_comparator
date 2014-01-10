#ifndef SUBSEQ_H
#define SUBSEQ_H

#include <QObject>
#include <QVector>
#include <QString>

enum Actions {
  none = 0, insert, away
};

class Subsequence : public QObject
{
  Q_OBJECT
public:
  explicit Subsequence(QObject *parent = 0);
  void setLeftText(const QVector<QString>& left_text);
  void setRightText(const QVector<QString>& right_text);

signals:

public slots:
  QVector<Actions> findLCS();

private:
  QVector<QString> left_text_;
  QVector<QString> right_text_;
};

#endif // SUBSEQ_H
