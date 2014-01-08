#include "htmlptag.h"

HtmlPTag::HtmlPTag(QObject *parent) :
  QObject(parent) { }

HtmlPTag::HtmlPTag(const QString& text, const QString& color,
                   const QString& align, QObject* parent)
    : QObject(parent), text_(text), color_(color), align_(align) { }

void HtmlPTag::setText(const QString& text) {
  text_ = text;
}

void HtmlPTag::setColor(const QString& color) {
  color_ = color;
}

void HtmlPTag::setAlign(const QString& align) {
  align_ = align;
}

QString HtmlPTag::toString() const {
  QString result = "<p %3 style=\"white-space:pre;margin:0;%2\">%1</p>";
  QString full_align;
  if (!align_.isEmpty()) {
    full_align = "align=\"" + align_ + "\"";
  }
  QString full_color;
  if (!color_.isEmpty()) {
    full_color = "background-color:" + color_ + ";";
  }
  return result.arg(text_, full_color, full_align);
}
