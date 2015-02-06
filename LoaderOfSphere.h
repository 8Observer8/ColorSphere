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

#ifndef LOADEROFSPHERE_H
#define LOADEROFSPHERE_H

#include <QString>
#include <assimp/scene.h>
#include <vector>

class LoaderOfSphere
{
public:
    LoaderOfSphere( const QString &fileName );
    ~LoaderOfSphere();

    bool isSuccessfully;

    std::vector<float> verticesOfSphere;
    std::vector<float> colorsOfSphere;
    std::vector<float> normalsOfSphere;

private:
    void init( const aiScene *scene );

    void fillVertices( const aiMesh *mesh,
                       std::vector<float> &vertices );

    void fillColors( const aiMesh *mesh,
                     const aiMaterial *material,
                     std::vector<float> &colors );

    void fillNormals( const aiMesh *mesh,
                      std::vector<float> &normals );
};

#endif // LOADEROFSPHERE_H
