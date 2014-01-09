#include "comparatorwidget.h"
#include "ui_comparatorwidget.h"
#include "subsequence.h"
#include "parsedata.h"
#include "filereader.h"

#include <QFileDialog>

ComparatorWidget::ComparatorWidget(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::ComparatorWidget) {
  ui_->setupUi(this);
  ui_->mainLayout->setMargin(10);
  this->setLayout(ui_->mainLayout);
  SynchronizeVerticalScrollBars();
  SynchronizeHorizontalScrollBars();
}

ComparatorWidget::~ComparatorWidget() {
  delete ui_;
}

void ComparatorWidget::SetFont(const QFont& font) {
  ui_->leftText->setFont(font);
  ui_->leftLineNumbers->setFont(font);
  ui_->rightText->setFont(font);
  ui_->rightLineNumbers->setFont(font);
}

void ComparatorWidget::on_compareButton_clicked() {
  if (!ui_->compareButton->isEnabled()) return;
  // Reading files
  QVector<QString> left_text;
  QVector<QString> right_text;
  FileReader::ToVectorOfStrings(ui_->leftFileName->text(), left_text);
  FileReader::ToVectorOfStrings(ui_->rightFileName->text(), right_text);
  // Creating Subsequence object
  Subsequence* compare_obj = new Subsequence(this);
  compare_obj->setLeftText(left_text);
  compare_obj->setRightText(right_text);
  // Connect Finished() to deleteLater()
  connect(compare_obj, SIGNAL(Finished()), compare_obj, SLOT(deleteLater()));
  // Creating ParseDeta object
  ParseData* parse_data_obj = new ParseData(this);
  parse_data_obj->setLeftText(left_text);
  parse_data_obj->setRightText(right_text);
  connect(parse_data_obj, SIGNAL(Finished()),
          parse_data_obj, SLOT(deleteLater()));
  connect(compare_obj, SIGNAL(CompareIsDone(QVector<Actions>)),
          parse_data_obj, SLOT(setCompareResult(QVector<Actions>)));
  connect(compare_obj, SIGNAL(Finished()),
          parse_data_obj, SLOT(Parsing()));
  connect(parse_data_obj, SIGNAL(LeftHtmlReady(QString)),
          this, SLOT(SetLeftTextHTML(QString)));
  connect(parse_data_obj, SIGNAL(LeftNumbersReady(QString)),
          this, SLOT(SetLeftNumbersHTML(QString)));
  connect(parse_data_obj, SIGNAL(RightHtmlReady(QString)),
          this, SLOT(SetRightTextHTML(QString)));
  connect(parse_data_obj, SIGNAL(RightNumbersReady(QString)),
          this, SLOT(SetRightNumbersHTML(QString)));

  compare_obj->findLCS();

  //StartCompare();
}

void ComparatorWidget::on_leftSelectFileButton_clicked() {
  QFileDialog* file_dialog = new QFileDialog(this);
  connect(file_dialog, SIGNAL(fileSelected(QString)),
          this, SLOT(SelectLeftFile(QString)));
  connect(file_dialog, SIGNAL(finished(int)),
          file_dialog, SLOT(deleteLater()));
  file_dialog->show();
}

void ComparatorWidget::on_rightSelectFileButton_clicked() {
  QFileDialog* file_dialog = new QFileDialog(this);
  connect(file_dialog, SIGNAL(fileSelected(QString)),
          this, SLOT(SelectRightFile(QString)));
  connect(file_dialog, SIGNAL(finished(int)),
          file_dialog, SLOT(deleteLater()));
  file_dialog->show();
}

void ComparatorWidget::SelectLeftFile(const QString& file_name) {
  ui_->leftFileName->setText(file_name);
  if (0 != ui_->leftFileName->text().size() &&
      0 != ui_->rightFileName->text().size()) {
    ui_->compareButton->setEnabled(true);
  }
}

void ComparatorWidget::SelectRightFile(const QString& file_name) {
  ui_->rightFileName->setText(file_name);
  if (0 != ui_->leftFileName->text().size() &&
      0 != ui_->rightFileName->text().size()) {
    ui_->compareButton->setEnabled(true);
  }
}

void ComparatorWidget::SetLeftTextHTML(const QString& text) {
  ui_->leftText->setHtml(text);
}

void ComparatorWidget::SetRightTextHTML(const QString& text) {
   ui_->rightText->setHtml(text);
}

void ComparatorWidget::SetLeftNumbersHTML(const QString& text) {
  ui_->leftLineNumbers->setHtml(text);
}

void ComparatorWidget::SetRightNumbersHTML(const QString& text) {
   ui_->rightLineNumbers->setHtml(text);
}

void ComparatorWidget::SetVerticalScrollBarRange(int min, int max) {
  ui_->verticalScrollBar->setRange(min, max);
  ui_->verticalScrollBar->setPageStep(
      ui_->leftText->verticalScrollBar()->pageStep());
  ui_->verticalScrollBar->setSingleStep(
      ui_->leftText->verticalScrollBar()->singleStep());
}

void ComparatorWidget::SetLeftHorizontalScrollBarRange(int min, int max) {
  ui_->leftHorizontalScrollBar->setRange(min, max);
  ui_->leftHorizontalScrollBar->setPageStep(
      ui_->leftText->horizontalScrollBar()->pageStep());
  ui_->leftHorizontalScrollBar->setSingleStep(
      ui_->leftText->horizontalScrollBar()->singleStep());
}

void ComparatorWidget::SetRightHorizontalScrollBarRange(int min, int max) {
  ui_->rightHorizontalScrollBar->setRange(min, max);
  ui_->rightHorizontalScrollBar->setPageStep(
      ui_->rightText->horizontalScrollBar()->pageStep());
  ui_->rightHorizontalScrollBar->setSingleStep(
      ui_->rightText->horizontalScrollBar()->singleStep());
}

void ComparatorWidget::SynchronizeVerticalScrollBars() {
  // Synchronize left vertical scroll bar and general vertical scroll bar
  connect(ui_->leftText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->verticalScrollBar, SLOT(setValue(int)));
  connect(ui_->verticalScrollBar, SIGNAL(valueChanged(int)),
          ui_->leftText->verticalScrollBar(), SLOT(setValue(int)));
  // Synchronize right vertical scroll bar and general vertical scroll bar
  connect(ui_->rightText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->verticalScrollBar, SLOT(setValue(int)));
  connect(ui_->verticalScrollBar, SIGNAL(valueChanged(int)),
          ui_->rightText->verticalScrollBar(), SLOT(setValue(int)));
  // Synchronize text and numbers
  connect(ui_->leftText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->leftLineNumbers->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->leftLineNumbers->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->leftText->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->rightText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->rightLineNumbers->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->rightLineNumbers->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->rightText->verticalScrollBar(), SLOT(setValue(int)));
  // Synchronize resizing
  connect(ui_->leftText->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
          this, SLOT(SetVerticalScrollBarRange(int, int)));
}

void ComparatorWidget::SynchronizeHorizontalScrollBars() {
  // Synchronize left horizontal scroll bars
  connect(ui_->leftText->horizontalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->leftHorizontalScrollBar, SLOT(setValue(int)));
  connect(ui_->leftHorizontalScrollBar, SIGNAL(valueChanged(int)),
          ui_->leftText->horizontalScrollBar(), SLOT(setValue(int)));
  // Synchronize right horizontal scroll bars
  connect(ui_->rightText->horizontalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->rightHorizontalScrollBar, SLOT(setValue(int)));
  connect(ui_->rightHorizontalScrollBar, SIGNAL(valueChanged(int)),
          ui_->rightText->horizontalScrollBar(), SLOT(setValue(int)));
  // Synchronize resizing
  connect(ui_->leftText->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
          this, SLOT(SetLeftHorizontalScrollBarRange(int, int)));
  connect(ui_->rightText->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
          this, SLOT(SetRightHorizontalScrollBarRange(int, int)));
}
