/*
 Copyright (C) 2010-2012 Kristian Duske
 
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
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DragPlane.h"

namespace TrenchBroom {
    namespace Controller {
        DragPlane::DragPlane() : m_normal(Vec3f::PosZ) {}

        DragPlane::DragPlane(const Vec3f& normal) : m_normal(normal.firstAxis()) {}
        
        float DragPlane::intersect(const Ray& ray, const Vec3f& planePosition) {
            Plane plane(m_normal, planePosition);
            return plane.intersectWithRay(ray);
        }
        
        const Vec3f& DragPlane::normal() {
            return m_normal;
        }

    }
}