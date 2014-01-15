#include "comparatorwidget.h"
#include "ui_comparatorwidget.h"
#include "filereader.h"
#include "compareandparse.h"

#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>

ComparatorWidget::ComparatorWidget(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::ComparatorWidget) {
  ui_->setupUi(this);
  ui_->mainLayout->setMargin(10);
  this->setLayout(ui_->mainLayout);
  SynchronizeVerticalScrollBars();
  SynchronizeHorizontalScrollBars();
  ui_->leftHorizontalScrollBar->setHidden(true);
  ui_->rightHorizontalScrollBar->setHidden(true);
  ui_->verticalScrollBar->setHidden(true);
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
  ui_->compareButton->setText("Wait");
  ui_->compareButton->setEnabled(false);
  // Reading files
  QStringList left_text;
  QStringList right_text;
  if (!FileReader::ToVectorOfStrings(ui_->leftFileName->text(), left_text) ||
      !FileReader::ToVectorOfStrings(ui_->rightFileName->text(), right_text)) {
    ui_->leftFileName->clear();
    ui_->rightFileName->clear();
    Warning("Warning", "File does not exist");
    return;
  }
  CompareAndParse* comp_and_parse_obj = new CompareAndParse;
  comp_and_parse_obj->setLeftText(left_text);
  comp_and_parse_obj->setRightText(right_text);
  connect(comp_and_parse_obj, SIGNAL(LeftHtmlReady(QString)),
          this, SLOT(SetLeftTextHTML(QString)));
  connect(comp_and_parse_obj, SIGNAL(LeftNumbersReady(QString)),
          this, SLOT(SetLeftNumbersHTML(QString)));
  connect(comp_and_parse_obj, SIGNAL(RightHtmlReady(QString)),
          this, SLOT(SetRightTextHTML(QString)));
  connect(comp_and_parse_obj, SIGNAL(RightNumbersReady(QString)),
          this, SLOT(SetRightNumbersHTML(QString)));
  connect(comp_and_parse_obj, SIGNAL(Finished()),
          this, SLOT(SetCompareButtonEnabled()));
  QThread* comp_and_parse_thread = new QThread(this);
  connect(comp_and_parse_thread, SIGNAL(started()),
          comp_and_parse_obj, SLOT(Start()));
  connect(comp_and_parse_thread, SIGNAL(finished()),
          comp_and_parse_obj, SLOT(deleteLater()));
  connect(comp_and_parse_thread, SIGNAL(finished()),
          comp_and_parse_thread, SLOT(deleteLater()));
  connect(comp_and_parse_obj, SIGNAL(Finished()),
          comp_and_parse_thread, SLOT(quit()));
  comp_and_parse_obj->moveToThread(comp_and_parse_thread);
  comp_and_parse_thread->start();
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
  if (max - min > 0) {
    ui_->verticalScrollBar->setVisible(true);
  } else {
    ui_->verticalScrollBar->setHidden(true);
  }
}

void ComparatorWidget::SetLeftHorizontalScrollBarRange(int min, int max) {
  ui_->leftHorizontalScrollBar->setRange(min, max);
  ui_->leftHorizontalScrollBar->setPageStep(
      ui_->leftText->horizontalScrollBar()->pageStep());
  ui_->leftHorizontalScrollBar->setSingleStep(
      ui_->leftText->horizontalScrollBar()->singleStep());
  if (max - min > 0) {
    ui_->leftHorizontalScrollBar->setVisible(true);
  } else {
    ui_->leftHorizontalScrollBar->setHidden(true);
  }
}

void ComparatorWidget::SetRightHorizontalScrollBarRange(int min, int max) {
  ui_->rightHorizontalScrollBar->setRange(min, max);
  ui_->rightHorizontalScrollBar->setPageStep(
      ui_->rightText->horizontalScrollBar()->pageStep());
  ui_->rightHorizontalScrollBar->setSingleStep(
      ui_->rightText->horizontalScrollBar()->singleStep());
  if (max - min > 0) {
    ui_->rightHorizontalScrollBar->setVisible(true);
  } else {
    ui_->rightHorizontalScrollBar->setHidden(true);
  }
}

void ComparatorWidget::SetCompareButtonEnabled() {
  ui_->compareButton->setText("Compare");
  ui_->compareButton->setEnabled(true);
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

void ComparatorWidget::Warning(const QString& title, const QString& message) {
  QMessageBox* warning_box = new QMessageBox(QMessageBox::Warning,
                                             title, message,
                                             QMessageBox::NoButton, this);
  connect(warning_box, SIGNAL(finished(int)),
          warning_box, SLOT(deleteLater()));
  warning_box->show();
}

void ComparatorWidget::keyReleaseEvent(QKeyEvent* key_event) {
  if (key_event->modifiers() == (Qt::CTRL + Qt::SHIFT)) {
    switch (key_event->key()) {
      case Qt::Key_C: // CTRL + SHIFT + C for compare
        on_compareButton_clicked();
      break;
      case Qt::Key_Left: // CTRL + SHIFT + Left for change left file name
        on_leftSelectFileButton_clicked();
      break;
      case Qt::Key_Right: // CTRL + SHIFT + Right for change right file name
        on_rightSelectFileButton_clicked();
      break;
      default:
      break;
    }
  }
}
