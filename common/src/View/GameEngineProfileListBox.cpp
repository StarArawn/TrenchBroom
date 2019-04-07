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

#include "GameEngineProfileListBox.h"

#include "Model/GameEngineConfig.h"
#include "Model/GameEngineProfile.h"
#include "View/wxUtils.h"

#include <QBoxLayout>
#include <QLabel>

namespace TrenchBroom {
    namespace View {
        GameEngineProfileItemRenderer::GameEngineProfileItemRenderer(Model::GameEngineProfile* profile, QWidget* parent) :
        ControlListBoxItemRenderer(parent),
        m_profile(profile),
        m_nameLabel(nullptr),
        m_pathLabel(nullptr) {
            ensure(m_profile != nullptr, "profile is null");
            createGui();
            refresh();
            addObservers();
        }

        GameEngineProfileItemRenderer::~GameEngineProfileItemRenderer() {
            if (m_profile != nullptr) {
                removeObservers();
            }
        }

        void GameEngineProfileItemRenderer::setSelected(bool selected) {
            ControlListBoxItemRenderer::setSelected(selected);
        }

        void GameEngineProfileItemRenderer::createGui() {
            // FIXME: needs ellipses
            m_nameLabel = new QLabel();
            m_pathLabel = new QLabel();

            makeEmphasized(m_nameLabel);
            makeInfo(m_pathLabel);

            auto* layout = new QVBoxLayout();
            setLayout(layout);

            layout->addWidget(m_nameLabel);
            layout->addWidget(m_pathLabel);
        }

        void GameEngineProfileItemRenderer::refresh() {
            if (m_profile == nullptr) {
                m_nameLabel->setText("");
                m_pathLabel->setText("");
            } else {
                m_nameLabel->setText(QString::fromStdString(m_profile->name()));
                m_pathLabel->setText(QString::fromStdString(m_profile->path().asString()));
            }
            if (m_nameLabel->text().isEmpty()) {
                m_nameLabel->setText("not set");
            }
        }

        void GameEngineProfileItemRenderer::addObservers() {
            m_profile->profileWillBeRemoved.addObserver(this, &GameEngineProfileItemRenderer::profileWillBeRemoved);
            m_profile->profileDidChange.addObserver(this, &GameEngineProfileItemRenderer::profileDidChange);
        }

        void GameEngineProfileItemRenderer::removeObservers() {
            m_profile->profileWillBeRemoved.removeObserver(this, &GameEngineProfileItemRenderer::profileWillBeRemoved);
            m_profile->profileDidChange.removeObserver(this, &GameEngineProfileItemRenderer::profileDidChange);
        }

        void GameEngineProfileItemRenderer::profileWillBeRemoved() {
            if (m_profile != nullptr) {
                removeObservers();
                m_profile = nullptr;
            }
        }

        void GameEngineProfileItemRenderer::profileDidChange() {
            refresh();
        }

        GameEngineProfileListBox::GameEngineProfileListBox(const Model::GameEngineConfig& config, QWidget* parent)  :
        ControlListBox("Click the '+' button to create a game engine profile.", parent),
        m_config(config) {
            m_config.profilesDidChange.addObserver(this, &GameEngineProfileListBox::profilesDidChange);
            refresh();
        }

        GameEngineProfileListBox::~GameEngineProfileListBox() {
            m_config.profilesDidChange.removeObserver(this, &GameEngineProfileListBox::profilesDidChange);
        }

        Model::GameEngineProfile* GameEngineProfileListBox::selectedProfile() const {
            if (currentRow() >= 0 && static_cast<size_t>(currentRow()) < m_config.profileCount()) {
                return m_config.profile(static_cast<size_t>(currentRow()));
            } else {
                return nullptr;
            }
        }

        void GameEngineProfileListBox::profilesDidChange() {
            refresh();
        }

        size_t GameEngineProfileListBox::itemCount() const {
            return m_config.profileCount();
        }

        ControlListBoxItemRenderer* GameEngineProfileListBox::createItemRenderer(QWidget* parent, const size_t index) {
            auto* profile = m_config.profile(index);
            return new GameEngineProfileItemRenderer(profile, parent);
        }

        void GameEngineProfileListBox::currentRowChanged(const int index) {
            if (index >= 0 && index < count()) {
                emit currentProfileChanged(m_config.profile(static_cast<size_t>(index)));
            } else {
                emit currentProfileChanged(nullptr);
            }
        }
    }
}
