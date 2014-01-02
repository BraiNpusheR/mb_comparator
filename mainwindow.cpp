#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      default_font_(QFont("Ubuntu Mono", 12)),
      ui_(new Ui::MainWindow),
      font_dialog_(new QFontDialog(this)),
      left_file_dialog_(new QFileDialog(this)),
      right_file_dialog_(new QFileDialog(this)) {
  ui_->setupUi(this);
  ui_->mainLayout->setMargin(10);
  ui_->centralWidget->setLayout(ui_->mainLayout);
  SetDefautFont();
  connect(font_dialog_, SIGNAL(fontSelected(QFont)),
          this, SLOT(ChangeFont(QFont)));
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
  ui_->rightText->setFont(font);
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
  ui_->rightText->setFont(default_font_);
}

void MainWindow::on_compareButton_clicked() {
  // Reading left
  ui_->leftText->clear();
  QFile fileLeft(ui_->leftFileName->text());
  fileLeft.open(QFile::ReadOnly);
  QTextStream streamLeft(&fileLeft);
  while (!streamLeft.atEnd()) {
    ui_->leftText->insertPlainText(streamLeft.readLine() + "\n");
  }
  // Reading right
  ui_->rightText->clear();
  QFile fileRight(ui_->rightFileName->text());
  fileRight.open(QFile::ReadOnly);
  QTextStream streamRight(&fileRight);
  while (!streamRight.atEnd()) {
    ui_->rightText->insertPlainText(streamRight.readLine() + "\n");
  }
}
