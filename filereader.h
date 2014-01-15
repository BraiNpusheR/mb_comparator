#ifndef FILEREADER_H
#define FILEREADER_H

#include <QStringList>

class FileReader
{
public:
  FileReader();
  static bool ToVectorOfStrings(const QString& file_name,
                                QStringList& text);
};

#endif // FILEREADER_H
