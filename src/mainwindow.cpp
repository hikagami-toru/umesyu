#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e) {
    if (!e->mimeData()->hasFormat("text/uri-list"))
        return;
    e->acceptProposedAction();
}

#include "model.hpp"

void MainWindow::dropEvent(QDropEvent* e) {
    auto filename = e->mimeData()->urls().first().toLocalFile().toStdString();
    ui->mainview->mesh() = std::make_unique<model::Mesh>(model::Mesh::load(filename.c_str()));
    ui->mainview->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
