#ifndef FILEREADER_H
#define FILEREADER_H

#include <QVector>
#include <QString>

class FileReader
{
public:
  enum ReturnCode {
    Done, Error
  };

  FileReader();
  static ReturnCode ToVectorOfStrings(const QString& file_name,
                                      QVector<QString>& text);
};

#endif // FILEREADER_H
