#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QScrollBar>
#include <QKeyEvent>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      default_font_(QFont("Ubuntu Mono", 12)){
  // Setup user interface
  ui_->setupUi(this);
  ui_->centralWidget->setLayout(ui_->mainLayout);
  comp_widget_ = new ComparatorWidget(this);
  ui_->mainLayout->addWidget(comp_widget_);
  // Move main window to center
  QRect rect = frameGeometry();
  rect.moveCenter(QDesktopWidget().availableGeometry().center());
  move(rect.topLeft());
  // Setup default font
  SetDefautFont();
}

MainWindow::~MainWindow() {
  delete ui_;
  delete comp_widget_;
}

void MainWindow::ChangeFont(const QFont& font) {
  current_font_ = font;
  comp_widget_->SetFont(current_font_);
}

void MainWindow::on_actionChangeFont_activated() {
  QFontDialog* font_dialog = new QFontDialog(current_font_, this);
  connect(font_dialog, SIGNAL(fontSelected(QFont)),
          this, SLOT(ChangeFont(QFont)));
  connect(font_dialog, SIGNAL(finished(int)),
          font_dialog, SLOT(deleteLater()));
  font_dialog->show();
}

void MainWindow::on_actionDefaultFont_activated() {
  SetDefautFont();
}

void MainWindow::SetDefautFont() {
  current_font_ = default_font_;
  comp_widget_->SetFont(current_font_);
}

void MainWindow::keyReleaseEvent(QKeyEvent* key_event) {
  if (key_event->modifiers() == (Qt::CTRL + Qt::SHIFT)) {
    /*switch (key_event->key()) {
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
    }*/
  }
}
