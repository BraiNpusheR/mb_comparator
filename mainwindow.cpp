#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parsedata.h"
#include "subsequence.h"

#include <QDesktopWidget>
#include <QScrollBar>
#include <QKeyEvent>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      default_font_(QFont("Ubuntu Mono", 12)),
      ui_(new Ui::MainWindow),
      font_dialog_(new QFontDialog(this)),
      left_file_dialog_(new QFileDialog(this)),
      right_file_dialog_(new QFileDialog(this)) {
  // Setup user interface
  ui_->setupUi(this);
  ui_->mainLayout->setMargin(10);
  ui_->centralWidget->setLayout(ui_->mainLayout);
  // Move main window to center
  QRect rect = frameGeometry();
  rect.moveCenter(QDesktopWidget().availableGeometry().center());
  move(rect.topLeft());
  // Setup default font
  SetDefautFont();
  // Sinchronize nubbers of lines and text
  connect(ui_->leftText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->leftLineNumbers->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->leftLineNumbers->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->leftText->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->rightText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->rightLineNumbers->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->rightLineNumbers->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->rightText->verticalScrollBar(), SLOT(setValue(int)));
  // Sinchronize vertical scroll bars
  connect(ui_->leftText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->verticalScrollBar, SLOT(setValue(int)));
  connect(ui_->verticalScrollBar, SIGNAL(valueChanged(int)),
          ui_->leftText->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->rightText->verticalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->verticalScrollBar, SLOT(setValue(int)));
  connect(ui_->verticalScrollBar, SIGNAL(valueChanged(int)),
          ui_->rightText->verticalScrollBar(), SLOT(setValue(int)));
  connect(ui_->leftText->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
          this, SLOT(SetVerticalScrollBarRange(int,int)));
  // Sinchronize horizontal scroll bars
  connect(ui_->leftText->horizontalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->horizontalScrollBar, SLOT(setValue(int)));
  connect(ui_->horizontalScrollBar, SIGNAL(valueChanged(int)),
          ui_->leftText->horizontalScrollBar(), SLOT(setValue(int)));
  connect(ui_->rightText->horizontalScrollBar(), SIGNAL(valueChanged(int)),
          ui_->horizontalScrollBar, SLOT(setValue(int)));
  connect(ui_->horizontalScrollBar, SIGNAL(valueChanged(int)),
          ui_->rightText->horizontalScrollBar(), SLOT(setValue(int)));
  connect(ui_->leftText->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
          this, SLOT(SetHorizontalScrollBarRange(int,int)));
  // Connect slot for change font
  connect(font_dialog_, SIGNAL(fontSelected(QFont)),
          this, SLOT(ChangeFont(QFont)));
  // Connect slots for left and right file dialogs
  connect(left_file_dialog_, SIGNAL(fileSelected(QString)),
          this, SLOT(OpenLeftFile(QString)));
  connect(right_file_dialog_, SIGNAL(fileSelected(QString)),
          this, SLOT(OpenRightFile(QString)));
}

MainWindow::~MainWindow() {
  delete ui_;
  delete font_dialog_;
  delete left_file_dialog_;
  delete right_file_dialog_;
}

void MainWindow::ChangeFont(const QFont& font) {
  ui_->leftText->setFont(font);
  ui_->leftLineNumbers->setFont(font);
  ui_->rightText->setFont(font);
  ui_->rightLineNumbers->setFont(font);
}

void MainWindow::on_actionChangeFont_activated() {
  font_dialog_->show();
}

void MainWindow::on_actionDefaultFont_activated() {
  SetDefautFont();
}

void MainWindow::OpenLeftFile(const QString& file_name) {
  ui_->leftFileName->setText(file_name);
  if (0 != ui_->rightFileName->text().size()) {
    ui_->compareButton->setEnabled(true);
  }
}

void MainWindow::OpenRightFile(const QString& file_name) {
  ui_->rightFileName->setText(file_name);
  if (0 != ui_->leftFileName->text().size()) {
    ui_->compareButton->setEnabled(true);
  }
}

void MainWindow::on_leftOpenFileButton_clicked(){
  left_file_dialog_->show();
}

void MainWindow::on_rightOpenFileButton_clicked() {
  right_file_dialog_->show();
}

void MainWindow::SetDefautFont() {
  font_dialog_->setCurrentFont(default_font_);
  ui_->leftText->setFont(default_font_);
  ui_->leftLineNumbers->setFont(default_font_);
  ui_->rightText->setFont(default_font_);
  ui_->rightLineNumbers->setFont(default_font_);
}

void MainWindow::on_compareButton_clicked() {
  if (!ui_->compareButton->isEnabled()) return;
  //ui_->compareButton->setEnabled(false);
  //ui_->compareButton->setText("Wait");
  QVector<QString> left_text = ReadFile(ui_->leftFileName->text());
  QVector<QString> right_text = ReadFile(ui_->rightFileName->text());
  QVector<Actions> compare_result =
      Subsequence::getLongestCommonSubsequence(left_text, right_text);
  ParseData* parse_data_obj = new ParseData(this);
  connect(parse_data_obj, SIGNAL(LeftHtmlReady(QString)),
          this, SLOT(SetLeftText(QString)));
  connect(parse_data_obj, SIGNAL(LeftNumbersReady(QString)),
          this, SLOT(SetLeftNumbers(QString)));
  connect(parse_data_obj, SIGNAL(RightHtmlReady(QString)),
          this, SLOT(SetRightText(QString)));
  connect(parse_data_obj, SIGNAL(RightNumbersReady(QString)),
          this, SLOT(SetRightNumbers(QString)));
  parse_data_obj->Parsing(left_text, right_text, compare_result);
}

void MainWindow::SetLeftText(const QString &text) {
  ui_->leftText->setHtml(text);
}

void MainWindow::SetLeftNumbers(const QString &numbers) {
  ui_->leftLineNumbers->setHtml(numbers);
}

void MainWindow::SetRightText(const QString &text) {
  ui_->rightText->setHtml(text);
}

void MainWindow::SetRightNumbers(const QString &numbers) {
  ui_->rightLineNumbers->setHtml(numbers);
}

void MainWindow::keyReleaseEvent(QKeyEvent* key_event) {
  if (key_event->modifiers() == (Qt::CTRL + Qt::SHIFT)) {
    switch (key_event->key()) {
      case Qt::Key_C: // CTRL + SHIFT + C for compare
        on_compareButton_clicked();
      break;
      case Qt::Key_Left: // CTRL + SHIFT + Left for change left file name
        on_leftOpenFileButton_clicked();
      break;
      case Qt::Key_Right: // CTRL + SHIFT + Right for change right file name
        on_rightOpenFileButton_clicked();
      break;
      default:
      break;
    }
  }
}

void MainWindow::SetVerticalScrollBarRange(int min, int max) {
  ui_->verticalScrollBar->setMinimum(min);
  ui_->verticalScrollBar->setMaximum(max);
  ui_->verticalScrollBar->setPageStep(
        ui_->leftText->verticalScrollBar()->pageStep());
  ui_->verticalScrollBar->setSingleStep(
        ui_->leftText->verticalScrollBar()->singleStep());
}

void MainWindow::SetHorizontalScrollBarRange(int min, int max) {
  ui_->horizontalScrollBar->setMinimum(min);
  ui_->horizontalScrollBar->setMaximum(max);
  ui_->horizontalScrollBar->setPageStep(
        ui_->leftText->horizontalScrollBar()->pageStep());
  ui_->horizontalScrollBar->setSingleStep(
        ui_->leftText->horizontalScrollBar()->singleStep());
}

QVector<QString> MainWindow::ReadFile(const QString& file_name) {
  QFile file(file_name);
  file.open(QFile::ReadOnly);
  QTextStream file_stream(&file);
  QVector<QString> result;
  while (!file_stream.atEnd()) {
    result.push_back(file_stream.readLine());
  }
  return result;
}
