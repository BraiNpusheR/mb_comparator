#include "htmlptag.h"

#include <QTextStream>

HtmlPTag::HtmlPTag() { }

HtmlPTag::HtmlPTag(const QString& text, const QString& bg_color,
                   const QString& text_color, const QString& align)
    : text_(text), bg_color_(bg_color),
    text_color_(text_color), align_(align) { }

void HtmlPTag::setText(const QString& text) {
  text_ = text;
}

void HtmlPTag::setBgColor(const QString& bg_color) {
  bg_color_ = bg_color;
}

void HtmlPTag::setTextColor(const QString& text_color) {
  text_color_ = text_color;
}

void HtmlPTag::setAlign(const QString& align) {
  align_ = align;
}

QString HtmlPTag::toString() const {
  QString result = "<p %4 style=\"white-space:pre;margin:0;%2 %3\">%1</p>";
  QString full_align;
  if (!align_.isEmpty()) {
    full_align = "align=\"" + align_ + "\"";
  }
  QString full_bg_color;
  if (!bg_color_.isEmpty()) {
    full_bg_color = "background-color:" + bg_color_ + ";";
  }
  QString full_text_color;
  if (!bg_color_.isEmpty()) {
    full_text_color = "color:" + text_color_ + ";";
  }
  QString full_text;
  QTextStream full_text_stream(&full_text);
  for (int i = 0; i < text_.size(); ++i) {
    if ('\t' == text_[i]) {
      full_text_stream<<"    ";
    } else if ('<' == text_[i]) {
      full_text_stream<<"&#60;";
    } else if ('>' == text_[i]) {
      full_text_stream<<"&#62;";
    } else if ('"' == text_[i]) {
      full_text_stream<<"&#34;";
    } else if ('&' == text_[i]) {
      full_text_stream<<"&#38;";
    } else {
      full_text_stream<<text_[i];
    }
  }
  if (0 == text_.size()) {
    full_text_stream<<" ";
  }
  return result.arg(full_text, full_bg_color, full_text_color, full_align);
}
