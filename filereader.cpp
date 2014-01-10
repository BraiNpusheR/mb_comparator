#include "filereader.h"

#include <QFile>
#include <QTextStream>

FileReader::FileReader() { }

bool FileReader::ToVectorOfStrings(const QString& file_name,
                                   QVector<QString>& text) {
  QFile file(file_name);
  if (!file.open(QFile::ReadOnly)) return false;
  text.clear();
  QTextStream file_stream(&file);
  while (!file_stream.atEnd()) {
    text.push_back(file_stream.readLine());
  }
  return true;
}
