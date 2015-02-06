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

#include "LoaderOfSphere.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

LoaderOfSphere::LoaderOfSphere( const QString &fileName ) :
    isSuccessfully( true )
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( fileName.toStdString(),
                                              aiProcess_Triangulate );

    if ( scene == 0 )
    {
        isSuccessfully = false;
        std::cerr << "Error in 'LoaderOfSphere::LoaderOfSphere(...)': "
                     "'scene == 0' Unable to open the file " <<
                  fileName.toStdString() << std::endl;
        return;
    }

    if ( scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE )
    {
        isSuccessfully = false;
        std::cerr << "Error in 'LoaderOfSphere::LoaderOfSphere(...)': "
                     "'scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE'" << std::endl;
        return;
    }

    if ( scene->mRootNode == 0 )
    {
        isSuccessfully = false;
        std::cerr << "Error in 'LoaderOfSphere::LoaderOfSphere(...)': "
                     "'scene->mRootNode == 0'" << std::endl;
        return;
    }

    init( scene );
}

LoaderOfSphere::~LoaderOfSphere()
{

}

void LoaderOfSphere::init( const aiScene *scene )
{
    const aiNode *node = scene->mRootNode->mChildren[0];
    const aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];
    const aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    fillVertices( mesh, verticesOfSphere );
    fillColors( mesh, material, colorsOfSphere );
    fillNormals( mesh, normalsOfSphere );
}

void LoaderOfSphere::fillVertices( const aiMesh *mesh,
                                   std::vector<float> &vertices )
{
    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        vertices.push_back( mesh->mVertices[i].x );
        vertices.push_back( mesh->mVertices[i].y );
        vertices.push_back( mesh->mVertices[i].z );
    }
}

void LoaderOfSphere::fillColors( const aiMesh *mesh,
                                 const aiMaterial *material,
                                 std::vector<float> &colors )
{
    aiColor4D color;
    aiGetMaterialColor( material, AI_MATKEY_COLOR_DIFFUSE, &color );

    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        colors.push_back( color.r );
        colors.push_back( color.g );
        colors.push_back( color.b );
    }
}

void LoaderOfSphere::fillNormals( const aiMesh *mesh,
                                   std::vector<float> &normals )
{
    if ( mesh->mNormals == 0 )
    {
        std::cerr << "Error in 'void LoaderOfSphere::fillNormals(...)' Unable to find the normals." << std::endl;
        isSuccessfully = false;
        return;
    }

    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        normals.push_back( mesh->mNormals[i].x );
        normals.push_back( mesh->mNormals[i].y );
        normals.push_back( mesh->mNormals[i].z );
    }
}
