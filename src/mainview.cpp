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

static vector3d calc_triangle_normal(model::Face const& face, model::Mesh const& mesh) {
    auto const& nodes = mesh.nodes;
    auto const& indices = face.node_indices;
    auto a = nodes[indices[1].data].position - nodes[indices[0].data].position;
    auto b = nodes[indices[2].data].position - nodes[indices[0].data].position;
    return cross(a, b).normal();
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

    for (auto const& face : m_mesh->faces) {
        switch (face.type) {
        case model::Face::Type::Triangle:
            glBegin(GL_TRIANGLES);
            glNormal3dv(calc_triangle_normal(face, *m_mesh).data());
            for (auto const& node_id : face.node_indices) {
                auto const& pos = m_mesh->nodes[node_id.data].position;
                glVertex3d(pos[0], pos[1], pos[2]);
            }
            glEnd();
            break;
        case model::Face::Type::Rectangle:
            glBegin(GL_QUADS);
            glNormal3dv(calc_triangle_normal(face, *m_mesh).data());
            for (auto const& node_id : face.node_indices) {
                auto const& pos = m_mesh->nodes[node_id.data].position;
                glVertex3d(pos[0], pos[1], pos[2]);
            }
            glEnd();
            break;
        }
    }
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
