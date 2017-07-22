#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <memory>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "model.hpp"
#include "view_status.hpp"

struct MainView : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MainView(QWidget* parent) :
        QOpenGLWidget(parent)
    {}

    std::unique_ptr<model::Mesh> const& mesh() const {
        return m_mesh;
    }
    std::unique_ptr<model::Mesh>& mesh() {
        return m_mesh;
    }

protected:
    void  initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;

    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
private:
    std::unique_ptr<model::Mesh> m_mesh = nullptr;
    ViewStatus m_view_status;
};

#endif // MAINVIEW_HPP
