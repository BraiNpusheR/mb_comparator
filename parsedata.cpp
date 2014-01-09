#include "parsedata.h"
#include "htmlptag.h"

#include <QTextStream>

ParseData::ParseData(QObject *parent) :
    QObject(parent) {}

void ParseData::Parsing(const QVector<QString>& left_text,
                        const QVector<QString>& right_text,
                        const QVector<Actions>& compare_result) {
  left_html_.clear();
  right_html_.clear();
  left_numbers_.clear();
  right_numbers_.clear();
  int left_index = 0;
  int right_index = 0;
  QTextStream left_html_stream(&left_html_);
  QTextStream left_numbers_stream(&left_numbers_);
  QTextStream right_html_stream(&right_html_);
  QTextStream right_numbers_stream(&right_numbers_);
  QString left_index_string;
  QTextStream left_index_string_stream(&left_index_string);
  QString right_index_string;
  QTextStream right_index_string_stream(&right_index_string);
  for (int i = 0; i < compare_result.size(); ++i) {
    switch (compare_result[i]) {
      case none:
        left_html_stream<<HtmlPTag(left_text[left_index++], "#FFFFFF", "", "").toString();
        left_index_string.clear();
        left_index_string_stream<<left_index;
        left_numbers_stream<<HtmlPTag(left_index_string, "", "", "right").toString();
        right_html_stream<<HtmlPTag(right_text[right_index++], "#FFFFFF", "", "").toString();
        right_index_string.clear();
        right_index_string_stream<<right_index;
        right_numbers_stream<<HtmlPTag(right_index_string, "", "", "right").toString();
      break;
      case away:
        left_html_stream<<HtmlPTag(left_text[left_index++], "#FF7070", "", "").toString();
        left_index_string.clear();
        left_index_string_stream<<left_index;
        left_numbers_stream<<HtmlPTag(left_index_string, "", "", "right").toString();
        right_html_stream<<HtmlPTag(left_text[left_index - 1], "#FF7070", "#C85f5f", "").toString();
        right_numbers_stream<<HtmlPTag(" ", "", "", "right").toString();
      break;
      case insert:
        left_html_stream<<HtmlPTag(right_text[right_index], "#7070FF", "#6161B5", "").toString();
        left_numbers_stream<<HtmlPTag(" ", "", "", "right").toString();
        right_html_stream<<HtmlPTag(right_text[right_index++], "#7070FF", "", "").toString();
        right_index_string.clear();
        right_index_string_stream<<right_index;
        right_numbers_stream<<HtmlPTag(right_index_string, "", "", "right").toString();
      break;
    }
  }

  LeftHtmlReady(left_html_);
  LeftNumbersReady(left_numbers_);
  RightHtmlReady(right_html_);
  RightNumbersReady(right_numbers_);
}
