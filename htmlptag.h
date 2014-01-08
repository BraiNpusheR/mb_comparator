#ifndef HTMLPTAG_H
#define HTMLPTAG_H

#include <QObject>

class HtmlPTag : public QObject
{
  Q_OBJECT
public:
  explicit HtmlPTag(QObject* parent = 0);
  explicit HtmlPTag(const QString&, const QString&, const QString&,
                    QObject* parent = 0);
  void setText(const QString&);
  void setColor(const QString&);
  void setAlign(const QString&);
  QString toString() const;

signals:

public slots:
private:
  QString text_;
  QString color_;
  QString align_;
};

#endif // HTMLPTAG_H
