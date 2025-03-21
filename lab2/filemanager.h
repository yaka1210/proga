#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "kursvalut.h"
#include <vector>

class FileManager {
public:
    static bool loadFromFile(const QString& filename, std::vector<Kursvalut*>& records);
};

#endif // FILEMANAGER_H
