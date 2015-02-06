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

#include "Sphere.h"

Sphere::Sphere( QOpenGLShaderProgram *program, int vertexAttrLoc,
                int colorAttrLoc, int normalAttrLoc ) :
    m_program( program ),
    m_vertexAttrLoc( vertexAttrLoc ),
    m_colorAttrLoc( colorAttrLoc ),
    m_normalAttrLoc( normalAttrLoc )
{

}

Sphere::~Sphere()
{

}

void Sphere::fillFromLoader( const LoaderOfSphere *loader )
{
    verticesOfSphere = loader->verticesOfSphere;
    colorsOfSphere = loader->colorsOfSphere;
    normalsOfSphere = loader->normalsOfSphere;
}

void Sphere::draw()
{
    m_program->setAttributeArray( m_vertexAttrLoc, verticesOfSphere.data(), 3 );
    m_program->setAttributeArray( m_colorAttrLoc, colorsOfSphere.data(), 3 );
    m_program->setAttributeArray( m_normalAttrLoc, normalsOfSphere.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttrLoc );
    m_program->enableAttributeArray( m_colorAttrLoc );
    m_program->enableAttributeArray( m_normalAttrLoc );

    glDrawArrays( GL_TRIANGLES, 0, verticesOfSphere.size() / 3 );

    m_program->disableAttributeArray( m_vertexAttrLoc );
    m_program->disableAttributeArray( m_colorAttrLoc );
    m_program->disableAttributeArray( m_normalAttrLoc );
}

