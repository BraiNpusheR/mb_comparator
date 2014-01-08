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
  for (int i = 0; i < compare_result.size(); ++i) {
    // TODO: Добавить нормальный парсинг строки в html
    switch (compare_result[i]) {
      case none:
        left_html_stream<<HtmlPTag(left_text[left_index++], "#FFFFFF", "").toString();
        left_numbers_stream<<"<p align=\"right\" style=\"white-space:pre;margin:0;\">"<<left_index<<"</p>";
        right_html_stream<<HtmlPTag(right_text[right_index++], "#FFFFFF", "").toString();
        right_numbers_stream<<"<p align=\"right\" style=\"white-space:pre;margin:0;\">"<<right_index<<"</p>";
      break;
      case away:
        left_html_stream<<HtmlPTag(left_text[left_index++], "#FF7070", "").toString();
        left_numbers_stream<<"<p align=\"right\" style=\"white-space:pre;margin:0;\">"<<left_index<<"</p>";
        right_html_stream<<HtmlPTag(left_text[left_index - 1], "#FF7070", "#C85f5f").toString();
        right_numbers_stream<<"<p align=\"right\" style=\"white-space:pre;margin:0;\"> </p>";
      break;
      case insert:
        left_html_stream<<HtmlPTag(right_text[right_index], "#7070FF", "#6161B5").toString();
        left_numbers_stream<<"<p align=\"right\" style=\"white-space:pre;margin:0;\"> </p>";
        right_html_stream<<HtmlPTag(right_text[right_index++], "#7070FF", "").toString();
        right_numbers_stream<<"<p align=\"right\" style=\"white-space:pre;margin:0;\">"<<right_index<<"</p>";
      break;
    }
  }

  LeftHtmlReady(left_html_);
  LeftNumbersReady(left_numbers_);
  RightHtmlReady(right_html_);
  RightNumbersReady(right_numbers_);
}
