#include <algorithm>
#include <QMouseEvent>
#include <GL/glu.h>
#include "mainview.hpp"

void MainView::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float light_color[] = {
        0.001f, 0.001f, 0.001f
    };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    float light_pos[] = {
        0.f, 0.f, 100.f
    };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color);
    float light_pos2[] = {
        0.f, 0.f, -100.f
    };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
}

static void draw_triangles(std::vector<model::Face::TriangleInfo> const& triangles) {
    glBegin(GL_TRIANGLES);
    for (auto const& triangle : triangles) {
        glNormal3dv(triangle.normal.data());
        for (auto const& pos : triangle.positions)
            glVertex3d(pos[0], pos[1], pos[2]);
    }
    glEnd();
}

void MainView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, -1.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);
    glRotated(m_view_status.rotate[0], 1.0, 0.0, 0.0);
    glRotated(m_view_status.rotate[1], 0.0, 1.0, 0.0);
    glRotated(m_view_status.rotate[2], 0.0, 0.0, 1.0);
    glTranslated(m_view_status.translate[0], m_view_status.translate[1], m_view_status.translate[2]);
    glScaled(m_view_status.scale, m_view_status.scale, m_view_status.scale);

    if (!m_mesh)
        return;

    std::vector<model::Face::TriangleInfo> triangles;
    for (auto const& face : m_mesh->faces)
        face.split_to_triangles(triangles, *m_mesh);
    draw_triangles(triangles);

    glFlush();
}

void MainView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double)w/h, 0.01, 100.0);
}

void MainView::mouseMoveEvent(QMouseEvent* e) {
    static auto last_pos = e->pos();
    QPoint d = e->pos() - last_pos;
    if (e->buttons() & Qt::LeftButton & Qt::RightButton) {
        m_view_status.translate[0] += d.x() / 1000.0;
        m_view_status.translate[1] -= d.y() / 1000.0;
    } else if (e->buttons() & Qt::LeftButton) {
        m_view_status.rotate[1] -= d.x() / 100.0;
        m_view_status.rotate[0] -= d.y() / 100.0;
    } else if (e->buttons() & Qt::RightButton) {
        m_view_status.scale += d.y() / 10000.0;
    }
    repaint();
}

void MainView::wheelEvent(QWheelEvent* e) {
}
