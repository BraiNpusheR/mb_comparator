#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include <QString>
#include <QVector>
#include <QObject>

enum Actions {
  none = 0, insert, away
};

class Subsequence : public QObject
{
Q_OBJECT
public:
  explicit Subsequence(QObject* parent = 0);
  void setLeftText(const QVector<QString>& left_text);
  void setRightText(const QVector<QString>& right_text);
public slots:
  //find longest common subsequence
  void findLCS();
signals:
  void CompareIsDone(QVector<QString>);
private:
  QVector<QString> left_text_;
  QVector<QString> right_text_;
};

#endif // SUBSEQUENCE_H
