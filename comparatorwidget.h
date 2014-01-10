#ifndef COMPARATORWIDGET_H
#define COMPARATORWIDGET_H

#include <QWidget>

namespace Ui {
class ComparatorWidget;
}

class ComparatorWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ComparatorWidget(QWidget *parent = 0);
  ~ComparatorWidget();

public slots:
  void SetFont(const QFont& font);

private slots:
  // Button
  void on_compareButton_clicked();
  void on_leftSelectFileButton_clicked();
  void on_rightSelectFileButton_clicked();
  // Select file
  void SelectLeftFile(const QString& file_name);
  void SelectRightFile(const QString& file_name);
  // Set
  void SetLeftTextHTML(const QString& text);
  void SetRightTextHTML(const QString& text);
  void SetLeftNumbersHTML(const QString& text);
  void SetRightNumbersHTML(const QString& text);
  void SetVerticalScrollBarRange(int min, int max);
  void SetLeftHorizontalScrollBarRange(int min, int max);
  void SetRightHorizontalScrollBarRange(int min, int max);
  void SetCompareButtonEnabled();

private:
  void SynchronizeVerticalScrollBars();
  void SynchronizeHorizontalScrollBars();
  void Warning(const QString& title, const QString& message);
  void keyReleaseEvent(QKeyEvent* key_event);

  Ui::ComparatorWidget *ui_;
};

#endif // COMPARATORWIDGET_H
