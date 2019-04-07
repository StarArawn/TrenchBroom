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

#include "GameListBox.h"

#include "StringUtils.h"
#include "IO/Path.h"
#include "IO/ResourceUtils.h"
#include "Model/GameConfig.h"
#include "Model/GameFactory.h"

#include <cassert>

namespace TrenchBroom {
    namespace View {
        GameListBox::GameListBox(QWidget* parent) :
        ImageListBox("No Games Found", parent) {
            reloadGameInfos();
        }

        String GameListBox::selectedGameName() const {
            const Model::GameFactory& gameFactory = Model::GameFactory::instance();
            const StringList& gameList = gameFactory.gameList();

            const auto index = currentRow();
            if (index >= static_cast<int>(gameList.size())) {
                return "";
            } else {
                return gameList[index];
            }
        }

        void GameListBox::selectGame(const size_t index) {
            setCurrentRow(index);
        }

        void GameListBox::reloadGameInfos() {
            m_gameInfos.clear();

            const Model::GameFactory& gameFactory = Model::GameFactory::instance();
            for (const String& gameName : gameFactory.gameList()) {
                const auto gamePath = gameFactory.gamePath(gameName);
                auto iconPath = gameFactory.iconPath(gameName);
                if (iconPath.isEmpty()) {
                    iconPath = IO::Path("DefaultGameIcon.png");
                }
                const auto experimental = gameFactory.gameConfig(gameName).experimental();

                m_gameInfos.emplace_back(Info{
                    gameName,
                    IO::loadPixmapResource(iconPath),
                    QString::fromStdString(gameName + (experimental ? " (experimental)" : "")),
                    QString::fromStdString(gamePath.isEmpty() ? String("Game not found") : gamePath.asString())
                });
            }

            refresh();
        }

        size_t GameListBox::itemCount() const {
            return m_gameInfos.size();
        }

        QPixmap GameListBox::image(size_t index) const {
            ensure(index < m_gameInfos.size(), "index out of range");
            return m_gameInfos[index].image;
        }

        QString GameListBox::title(const size_t n) const {
            ensure(n < m_gameInfos.size(), "index out of range");
            return m_gameInfos[n].title;
        }

        QString GameListBox::subtitle(const size_t n) const {
            ensure(n < m_gameInfos.size(), "index out of range");
            return m_gameInfos[n].subtitle;
        }

        void GameListBox::currentRowChanged(const int index) {
            if (index >= 0 && index < count()) {
                emit currentGameChanged(QString::fromStdString(m_gameInfos[static_cast<size_t>(index)].name));
            }
        }
    }
}
