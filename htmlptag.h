#ifndef HTMLPTAG_H
#define HTMLPTAG_H

#include <QString>

class HtmlPTag
{
public:
  explicit HtmlPTag();
  explicit HtmlPTag(const QString& text, const QString& bg_color,
                    const QString& text_color, const QString& align);
  void setText(const QString& text);
  void setBgColor(const QString& bg_color);
  void setTextColor(const QString& text_color);
  void setAlign(const QString& align);
  QString toString() const;
private:
  QString text_;
  QString bg_color_;
  QString text_color_;
  QString align_;
};

#endif // HTMLPTAG_H
