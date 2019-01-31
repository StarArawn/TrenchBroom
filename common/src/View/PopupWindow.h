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

#ifndef PopupWindow_h
#define PopupWindow_h

#include <QWidget>

namespace TrenchBroom {
    namespace View {
        class PopupWindow : public QWidget {
            Q_OBJECT
        public:
            explicit PopupWindow(QWidget* parent = nullptr);
            void positionTouchingWidget(QWidget* refWidget);

        protected: // QWidget overrides
            void closeEvent(QCloseEvent* event) override;
            void showEvent(QShowEvent* event) override;

        signals:
            void visibilityChanged(bool visible);
        };
    }
}

#endif /* PopupWindow_h */
