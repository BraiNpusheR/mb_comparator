#ifndef SUBSEQ_H
#define SUBSEQ_H

#include <QObject>
#include <QVector>
#include <QString>

enum Actions {
  none = 0, insert, away
};
class subseq : public QObject
{
    Q_OBJECT
public:
    explicit subseq(QObject *parent = 0);
    void setLeftText(const QVector<QString>& left_text);
    void setRightText(const QVector<QString>& right_text);
signals:
    void CompareIsDone(QVector<Actions> BackTrack);
    void Finished();
public slots:
  void findLCS();
private:
  QVector<QString> left_text_;
  QVector<QString> right_text_;
};

#endif // SUBSEQ_H
