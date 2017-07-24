#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*) override;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
