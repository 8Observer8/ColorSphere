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

#include "Scene.h"
#include "LoaderOfSphere.h"
#include <QDir>

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_xRot( 0 ),
    m_yRot( 0 ),
    m_zRot( 0 ),
    m_scale( 1.0f ),
    m_sphere( 0 )
{

}

Scene::~Scene()
{
    delete m_sphere;
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    QString path =  QDir::currentPath() + QString( "/Models/ColorSphere.obj" );
    LoaderOfSphere loader( path );
    if ( !loader.isSuccessfully )
        return;

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() )
        return;

    m_vertexAttrLoc = m_program.attributeLocation( "vertexAttr" );
    m_colorAttrLoc = m_program.attributeLocation( "colorAttr" );
    m_normalAttrLoc = m_program.attributeLocation( "normalAttr" );

    m_sphere = new Sphere( &m_program, m_vertexAttrLoc, m_colorAttrLoc, m_normalAttrLoc );
    m_sphere->fillFromLoader( &loader );

    m_modelViewMatrixLoc = m_program.uniformLocation( "modelViewMatrix" );
    m_projectionMatrixLoc = m_program.uniformLocation( "projectionMatrix" );
    m_normalMatrixLoc = m_program.uniformLocation( "normalMatrix" );

    m_cameraMatrix.setToIdentity();
    QVector3D cameraPos( 0.0f, 0.0f, -3.0f );
    m_cameraMatrix.translate( cameraPos );

    m_program.bind();
    m_cameraPosLoc = m_program.uniformLocation( "cameraPos" );
    m_program.setUniformValue( m_cameraPosLoc, QVector3D( 0.0f, 0.0f, 3.0f ) );

    m_lightPosLoc = m_program.uniformLocation( "lightPos" );
    m_program.setUniformValue( m_lightPosLoc, QVector3D( 30.0f, 30.0f, 30.0f ) );
    m_program.release();
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    // Set ModelView Matrix
    m_worldMatrix.setToIdentity();
    m_worldMatrix.rotate( 180.0f - ( float ( m_xRot ) / 16.0f ), 1.0f, 0.0f, 0.0f );
    m_worldMatrix.rotate( float ( m_yRot ) / 16.0f, 0.0f, 1.0f, 0.0f );
    m_worldMatrix.rotate( float( m_zRot ) / 16.0f, 0.0f, 0.0f, 1.0f );
    m_worldMatrix.scale( m_scale );
    m_program.setUniformValue( m_modelViewMatrixLoc,
                               m_cameraMatrix * m_worldMatrix );

    // Set Projection Matrix
    m_program.setUniformValue( m_projectionMatrixLoc, m_projectionMatrix );

    // Set Normal Matrix
    QMatrix3x3 normalMatrix = m_worldMatrix.normalMatrix();
    m_program.setUniformValue( m_normalMatrixLoc, normalMatrix );

    if ( m_sphere != 0 )
        m_sphere->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );

    if ( h == 0 )
        h = 1;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective( 50.0f, float( w ) / float( h ), 0.01f, 1000.0f );
}

void Scene::mousePressEvent( QMouseEvent *event )
{
    m_lastPos = event->pos();
}

void Scene::mouseMoveEvent( QMouseEvent *event )
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if ( event->buttons() & Qt::LeftButton )
    {
        setXRotation( m_xRot + 8 * dy );
        setYRotation( m_yRot + 8 * dx );
    }
    else if ( event->buttons() & Qt::RightButton )
    {
        setXRotation( m_xRot + 8 * dy );
        setZRotation( m_zRot + 8 * dx );
    }

    m_lastPos = event->pos();
}

static void qNormalizeAngle( int angle )
{
    while ( angle < 0 )
        angle += 360 * 16;

    while ( angle > 360 * 16 )
        angle -= 360 * 16;
}

void Scene::setXRotation( int angle )
{
    qNormalizeAngle( angle );

    if ( angle != m_xRot )
    {
        m_xRot = angle;
        update();
    }
}

void Scene::setYRotation( int angle )
{
    qNormalizeAngle( angle );

    if ( angle != m_yRot )
    {
        m_yRot = angle;
        update();
    }
}

void Scene::setZRotation( int angle )
{
    qNormalizeAngle( angle );

    if ( angle != m_zRot )
    {
        m_zRot = angle;
        update();
    }
}

void Scene::wheelEvent( QWheelEvent *event )
{
    if ( event->delta() > 0 )
        scalePlus();
    else if ( event->delta() < 0 )
        scaleMinus();

    update();
}

void Scene::scalePlus()
{
    m_scale *= 1.1f;
}

void Scene::scaleMinus()
{
    m_scale /= 1.1f;
}
