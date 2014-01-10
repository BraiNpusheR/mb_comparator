#ifndef FILEREADER_H
#define FILEREADER_H

#include <QVector>
#include <QString>

class FileReader
{
public:
  FileReader();
  static bool ToVectorOfStrings(const QString& file_name,
                                QVector<QString>& text);
};

#endif // FILEREADER_H
