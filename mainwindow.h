#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
  void OpenLeftFile(const QString& file_name);
  void OpenRightFile(const QString& file_name);
  void on_leftOpenFileButton_clicked();
  void on_rightOpenFileButton_clicked();
  void on_compareButton_clicked();

private:
  void SetDefautFont();

  QFont default_font_;
  Ui::MainWindow* ui_;
  QFontDialog* font_dialog_;
  QFileDialog* left_file_dialog_;
  QFileDialog* right_file_dialog_;
};

#endif // MAINWINDOW_H
