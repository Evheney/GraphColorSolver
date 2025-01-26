#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QMainWindow>

#include "colorersolver.h"
#include "graph.h"
#include "node.h"
#include "vertex.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void sceneChanged(Node *data);
    void nodeDeleted(Node *node);

    void on_actionQuit_triggered();

    void on_actionNew_triggered();

    void on_actionNew_10_triggered();

    void on_actionExecute_triggered();

    void on_actionAbout_triggered();

    void on_actionBruteforce_triggered();

    void on_actionGreedy_triggered();

    void on_actionBacktrack_triggered();

    void on_actionGreedyOpenMP_triggered();

    void on_actionExecute_OpenMP_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene_;
    QGraphicsItemGroup *group_;
    QVector<Node*> graphicsNodes_;
    QVector<QGraphicsItem*> graphicsEdges_;
    Graph* graph_;
    ColorerSolver::Id methodId_;
    int iterations_;

    void createGraph(int noV);

    void updateNodes();
    void updateEdges();

    void ColorerMethodTriggered(ColorerSolver::Id method);
    void SetColorerMethodInMenu(ColorerSolver::Id method);

    int InputIterations(int iterations);
    void Execute(int iterations);
    void ExecuteOpenMP(int iterations);
    void ApplyColorerSolver();
};

#endif // MAINWINDOW_H
