/*
 Copyright (C) 2010-2017 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "SystemPaths.h"

#include "IO/DiskIO.h"

#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QString>
#include <QStandardPaths>

namespace TrenchBroom {
    namespace IO {
        namespace SystemPaths {
            Path appDirectory() {
                return IO::Path::fromQString(QCoreApplication::applicationDirPath());
            }

            Path userDataDirectory() {
                return IO::Path::fromQString(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
            }

            Path logFilePath() {
                return userDataDirectory() + IO::Path("TrenchBroom.log");
            }

            Path findResourceFile(const Path &file) {
                // Special case for running debug builds on Linux, we want to search
                // next to the executable for resources
                const auto relativeToExecutable = appDirectory() + file;
                if (Disk::fileExists(relativeToExecutable)) {
                    return relativeToExecutable;
                }

                return IO::Path::fromQString(QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                                                    file.asQString(),
                                                                    QStandardPaths::LocateOption::LocateFile));
            }

            std::vector<Path> findResourceDirectories(const Path& directory) {
                std::vector<Path> result;

                // Special case for running debug builds on Linux
                result.push_back(appDirectory() + directory);

                const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::AppDataLocation, directory.asQString(), QStandardPaths::LocateOption::LocateDirectory);
                for (const QString& dir : dirs) {
                    result.push_back(IO::Path::fromQString(dir));
                }
                return result;
            }
        }
    }
}
