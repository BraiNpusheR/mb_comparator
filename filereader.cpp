#include "filereader.h"

#include <QFile>
#include <QTextStream>

FileReader::FileReader() { }

FileReader::ReturnCode FileReader::ToVectorOfStrings(const QString& file_name,
                                                     QVector<QString>& text) {
  QFile file(file_name);
  if (!file.open(QFile::ReadOnly)) return Error;
  text.clear();
  QTextStream file_stream(&file);
  while (!file_stream.atEnd()) {
    text.push_back(file_stream.readLine());
  }
  return Done;
}
