/*
    The Color Sphere Example

    Copyright (C) 2015  Enzhaev Ivan

    Email: 8observer8@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SPHERE_H
#define SPHERE_H

#include <QOpenGLShaderProgram>
#include "LoaderOfSphere.h"

class Sphere
{
public:
    Sphere( QOpenGLShaderProgram *program, int vertexAttrLoc,
            int colorAttrLoc, int normalAttrLoc );
    ~Sphere();

    void fillFromLoader( const LoaderOfSphere *loader );

    void draw();

    std::vector<float> verticesOfSphere;
    std::vector<float> colorsOfSphere;
    std::vector<float> normalsOfSphere;

    QOpenGLShaderProgram *m_program;
    int m_vertexAttrLoc;
    int m_colorAttrLoc;
    int m_normalAttrLoc;
};

#endif // SPHERE_H
