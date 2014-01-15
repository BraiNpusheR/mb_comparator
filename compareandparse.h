#ifndef COMPAREANDPARSE_H
#define COMPAREANDPARSE_H

#include <QObject>
#include <QStringList>

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
  void setLeftText(const QStringList& text);
  void setRightText(const QStringList& text);
  void Start();

private:
  QStringList left_text_;
  QStringList right_text_;
};

#endif // COMPAREANDPARSE_H
