#include "parsedata.h"
#include "htmlptag.h"

#include <QTextStream>
#include <QVector>

ParseData::ParseData(QObject *parent) :
    QObject(parent) {}

void ParseData::setLeftText(const QVector<QString>& text) {
  left_text_ = text;
}

void ParseData::setRightText(const QVector<QString>& text) {
  right_text_ = text;
}

void ParseData::setCompareResult(const QVector<Actions>& comp_res) {
  compare_result_ = comp_res;
}

QVector<QString> ParseData::Parsing() {
  QString left_html;
  QString right_html;
  QString left_numbers;
  QString right_numbers;
  int left_index = 0;
  int right_index = 0;
  QTextStream left_html_stream(&left_html);
  QTextStream left_numbers_stream(&left_numbers);
  QTextStream right_html_stream(&right_html);
  QTextStream right_numbers_stream(&right_numbers);
  // String with left_index
  QString left_index_string;
  QTextStream left_index_string_stream(&left_index_string);
  // String with right_index
  QString right_index_string;
  QTextStream right_index_string_stream(&right_index_string);
  for (int i = 0; i < compare_result_.size(); ++i) {
    switch (compare_result_[i]) {
      case none:
        left_html_stream<<HtmlPTag(left_text_[left_index++], "#FFFFFF", "", "").toString();
        left_index_string.clear();
        left_index_string_stream<<left_index;
        left_numbers_stream<<HtmlPTag(left_index_string, "", "", "right").toString();
        right_html_stream<<HtmlPTag(right_text_[right_index++], "#FFFFFF", "", "").toString();
        right_index_string.clear();
        right_index_string_stream<<right_index;
        right_numbers_stream<<HtmlPTag(right_index_string, "", "", "right").toString();
      break;
      case away:
        left_html_stream<<HtmlPTag(left_text_[left_index++], "#FF7070", "", "").toString();
        left_index_string.clear();
        left_index_string_stream<<left_index;
        left_numbers_stream<<HtmlPTag(left_index_string, "", "", "right").toString();
        right_html_stream<<HtmlPTag(" ", "#FF7070", "", "").toString();
        right_numbers_stream<<HtmlPTag(" ", "", "", "right").toString();
      break;
      case insert:
        left_html_stream<<HtmlPTag(" ", "#589fff", "", "").toString();
        left_numbers_stream<<HtmlPTag(" ", "", "", "right").toString();
        right_html_stream<<HtmlPTag(right_text_[right_index++], "#589fff", "", "").toString();
        right_index_string.clear();
        right_index_string_stream<<right_index;
        right_numbers_stream<<HtmlPTag(right_index_string, "", "", "right").toString();
      break;
    }
  }
  QVector<QString> result;
  result.push_back(left_html);
  result.push_back(left_numbers);
  result.push_back(right_html);
  result.push_back(right_numbers);
  return result;
}
