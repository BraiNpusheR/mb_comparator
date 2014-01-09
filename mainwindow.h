#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "subsequence.h"
#include "comparatorwidget.h"

#include <QMainWindow>
#include <QFontDialog>
#include <QFileDialog>
#include <QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void ChangeFont(const QFont& font);
  void on_actionChangeFont_activated();
  void on_actionDefaultFont_activated();

private:
  void keyReleaseEvent(QKeyEvent* key_event);
  void SetDefautFont();

  Ui::MainWindow* ui_;
  ComparatorWidget* comp_widget_;
  QFont default_font_;
  QFont current_font_;
};

#endif // MAINWINDOW_H
