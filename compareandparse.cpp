#include "compareandparse.h"
#include "subsequence.h"
#include "parsedata.h"

CompareAndParse::CompareAndParse(QObject *parent) :
  QObject(parent) { }

void CompareAndParse::setLeftText(const QVector<QString>& text) {
  left_text_ = text;
}

void CompareAndParse::setRightText(const QVector<QString>& text) {
  right_text_ = text;
}

void CompareAndParse::Start() {
  // Creating Subsequence object
  Subsequence* compare_obj = new Subsequence;
  compare_obj->setLeftText(left_text_);
  compare_obj->setRightText(right_text_);
  // Creating ParseDeta object
  ParseData* parse_data_obj = new ParseData;
  parse_data_obj->setLeftText(left_text_);
  parse_data_obj->setRightText(right_text_);
  parse_data_obj->setCompareResult(compare_obj->findLCS());
  // Persing and writting
  QVector<QString> result = parse_data_obj->Parsing();
  delete compare_obj;
  delete parse_data_obj;
  LeftHtmlReady(result[0]);
  LeftNumbersReady(result[1]);
  RightHtmlReady(result[2]);
  RightNumbersReady(result[3]);
  Finished();
}
