#ifndef COMPAREANDPARSE_H
#define COMPAREANDPARSE_H

#include <QObject>
#include <QVector>

class CompareAndParse : public QObject
{
  Q_OBJECT
public:
  explicit CompareAndParse(QObject *parent = 0);

signals:
  void LeftHtmlReady(const QString&);
  void LeftNumbersReady(const QString&);
  void RightHtmlReady(const QString&);
  void RightNumbersReady(const QString&);
  void Finished();

public slots:
  void setLeftText(const QVector<QString>& text);
  void setRightText(const QVector<QString>& text);
  void Start();

private:
  QVector<QString> left_text_;
  QVector<QString> right_text_;
};

#endif // COMPAREANDPARSE_H
