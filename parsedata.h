#ifndef PARSEDATA_H
#define PARSEDATA_H

#include "subsequence.h"

#include <QObject>

class ParseData : public QObject
{
  Q_OBJECT
public:
  explicit ParseData(QObject *parent = 0);
  void Parsing(const QVector<QString>&, const QVector<QString>&,
               const QVector<Actions>&);

signals:
  void LeftHtmlReady(const QString&);
  void LeftNumbersReady(const QString&);
  void RightHtmlReady(const QString&);
  void RightNumbersReady(const QString&);

public slots:
private:
  QString left_html_;
  QString left_numbers_;
  QString right_html_;
  QString right_numbers_;
};

#endif // PARSEDATA_H
