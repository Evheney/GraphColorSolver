#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QXmlStreamReader>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "colorersolver.h"
#include "edge.h"
#include "graph.h"
#include "node.h"
#include "vertex.h"

const int kDefaultIterations = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graph_(nullptr),
    methodId_(ColorerSolver::Unknown),
    iterations_(kDefaultIterations)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene_);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graph_;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::sceneChanged(Node *data)
{
    int index = data->getIndex();

    Vertex* node = graph_->getVertex(index);
    node->setX(data->x());
    node->setY(data->y());
    updateEdges();
}

void MainWindow::nodeDeleted(Node *node)
{
    graph_->removeVertex(node->getIndex());
    for(int i=0; i<graphicsNodes_.count(); i++) {
        graphicsNodes_[i]->deleteLater();
    }
    graphicsNodes_.clear();
    updateNodes();
}

void MainWindow::updateNodes()
{
    qDeleteAll(graphicsNodes_);
    graphicsNodes_.clear();

    for (int i=0; i < graph_->vertexCount(); i++)
    {
        Node* nn = new Node(i);
        scene_.addItem(nn);

        Vertex* vx = graph_->getVertex(i);
        nn->setPos(vx->x(),vx->y());
        nn->setZValue(2);
        nn->setObjectName(vx->name());
        nn->setColor(vx->color());

        connect(nn,SIGNAL(moved(Node*)),SLOT(sceneChanged(Node*)));
        connect(nn,SIGNAL(deleted(Node*)),SLOT(nodeDeleted(Node*)));
        graphicsNodes_.push_back(nn);
    }
}

void MainWindow::updateEdges()
{
    for(int i =0; i< graphicsEdges_.count(); i++) {
        delete graphicsEdges_[i];
    }
    graphicsEdges_.clear();


    for(int i=0; i<graph_->edgeCount(); i++)
    {
        QList<QGraphicsItem *> items;
        Edge* ed = graph_->getEdge(i);

        int x1,y1, x2, y2;
        x1 = ed->v1()->x();
        y1 = ed->v1()->y();
        x2 = ed->v2()->x();
        y2 = ed->v2()->y();

        QGraphicsLineItem * line = scene_.addLine(x1,y1,x2, y2);
        if(!ed->isEnabled())
        {
            QPen pen(Qt::lightGray);
            pen.setStyle(Qt::DashLine);

            line->setPen(pen);
        }

        items.push_back(line);

        QGraphicsItem* group = scene_.createItemGroup(items);
        graphicsEdges_.push_back(group);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    if (QMessageBox::question(
                this, tr("GraphColorer"),
                tr("Would you like to close the program?"),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes) {
        QApplication::quit();
        //or we can call close();
    }
}

void MainWindow::on_actionNew_triggered()
{
    createGraph(6);
}

void MainWindow::on_actionNew_10_triggered()
{
    createGraph(10);
}

void MainWindow::createGraph(int noV)
{
    qDebug() <<"create graph"<< noV;
    if (graph_)
        delete graph_;

    graph_ = new Graph(noV);
    graph_->create(noV);

    ApplyColorerSolver();

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    updateNodes();
    updateEdges();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(
        this, tr("GraphColorer"),
        tr("Created by Eugene Martynovskyy.\n\nGroup: 3KN-15B."));
}

void MainWindow::on_actionBruteforce_triggered()
{
    QMessageBox::information(
        this, tr("GraphColorer"),
        tr("Brutforce coloring is not implemented yet."));

    ColorerMethodTriggered(ColorerSolver::Bruteforce);
}

void MainWindow::on_actionGreedy_triggered()
{
    ColorerMethodTriggered(ColorerSolver::Greedy);
}

void MainWindow::on_actionBacktrack_triggered()
{
    ColorerMethodTriggered(ColorerSolver::Backtrace);
}

void MainWindow::on_actionGreedyOpenMP_triggered()
{
    ColorerMethodTriggered(ColorerSolver::GreedyOpenMP);
}

void MainWindow::ColorerMethodTriggered(ColorerSolver::Id method)
{
    SetColorerMethodInMenu(method);

    if (graph_) {
        ColorerSolver* colorer = ColorerSolver::create(method);
        graph_->setColorer(colorer);
    }
}

void MainWindow::SetColorerMethodInMenu(ColorerSolver::Id method)
{
    bool bf=false, bt=false, gr=false, grmp=false;

    if (graph_) {
        switch(method) {
        case ColorerSolver::Bruteforce:
            bf=true;
            break;
        case ColorerSolver::Backtrace:
            bt=true;
            break;
        default:
            Q_ASSERT(0);
        case ColorerSolver::Greedy:
            gr=true;
            break;
        case ColorerSolver::GreedyOpenMP:
            grmp = true;
            break;
        }
    }

    ui->actionBruteforce->setChecked(bf);
    ui->actionBacktrack->setChecked(bt);
    ui->actionGreedy->setChecked(gr);
    ui->actionGreedyOpenMP->setChecked(grmp);
}
void MainWindow::on_actionExecute_triggered()
{
    if (!graph_) {
        QMessageBox::information(
            this, tr("GraphColorer"),
            tr("Please create or open the graph before trying to execute coloring."));
        return;
    }

    if (methodId_ == ColorerSolver::Unknown) {
        on_actionGreedy_triggered();
    }

    iterations_ = InputIterations(iterations_);

    Execute(iterations_);
}

void MainWindow::on_actionExecute_OpenMP_triggered()
{
    if (!graph_) {
        QMessageBox::information(
            this, tr("GraphColorer"),
            tr("Please create or open the graph before trying to execute coloring."));
        return;
    }

    if (methodId_ == ColorerSolver::Unknown) {
        on_actionGreedy_triggered();
    }

    iterations_ = InputIterations(iterations_);

    ExecuteOpenMP(iterations_);
}

int MainWindow::InputIterations(int iterations)
{
    bool ok;
    int newIterations = QInputDialog::getInt(
            this, tr("Enter number of iterations"),
            tr("Iterations:"), iterations, 0, 10000, 1, &ok);
    if (ok)
        iterations = newIterations;

    return iterations;
}

void MainWindow::Execute(int iterations)
{
    QElapsedTimer timer;
    timer.start();

    const int kIterations = iterations;
    for(int i=0; i<kIterations; ++i) {
        graph_->coloring();
        if (i%20) {
            QString percent = QString::number(100./kIterations*i);
            ui->statusBar->showMessage( "test" ); //percent + "% finished");
        }
    }

    qDebug() << "The Coloring took" << timer.elapsed() << "milliseconds";
    qDebug() << "The Coloring took" << timer.nsecsElapsed() << "nanoseconds";

    QString msg;
    msg +=  "The "
            + graph_->coloringName()
            + " coloring took "
            + QString::number(timer.elapsed()) + " milliseconds";
    ui->statusBar->showMessage(msg, 10000 );

    updateNodes();
}

void MainWindow::ExecuteOpenMP(int iterations)
{
    QString msg;
    msg =  "The " + graph_->coloringName()
            + " OpenMP coloring starts...";
    ui->statusBar->showMessage(msg);

    QElapsedTimer timer;
    timer.start();

#pragma omp parallel
    {
        const int kIterations = iterations;
    #pragma omp for
        for(int i=0; i<kIterations; ++i) {
            graph_->coloring();
        }
    }

    qDebug() << "The Coloring took" << timer.elapsed() << "milliseconds";
    qDebug() << "The Coloring took" << timer.nsecsElapsed() << "nanoseconds";

    msg = "The " + graph_->coloringName() + " OpenMP coloring took "
        + QString::number(timer.elapsed()) + " milliseconds";
    ui->statusBar->showMessage(msg, 10000 );

    updateNodes();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
        QDir::currentPath(), tr("*.xml"));
        QFile inFile(fileName);

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("GraphColorer"),
                                 tr("Cannot open xml file"),
                                 QMessageBox::Ok);
        return;
    }

    QXmlStreamReader xmlReader(&inFile);

    QString previousElement;
    while(!xmlReader.atEnd())
    {
        xmlReader.readNext();

        if (!xmlReader.isStartElement()) {
            continue;
        }

        QString text = xmlReader.name().toString();

        // Graph
        if (text == QStringLiteral("graph")) {
            QString uidGraph = xmlReader.attributes().value("uidGraph").toString();
            qDebug().nospace() << text;

            if (graph_)
                delete graph_;

            graph_ = new Graph(uidGraph.toInt()+1);
        }
        // Nodes
        else if (text == QStringLiteral("node")) {
            QString id = xmlReader.attributes().value("id").toString();
            QString positionX = xmlReader.attributes().value("positionX").toString();
            QString positionY = xmlReader.attributes().value("positionY").toString();
            int posX = (int)xmlReader.attributes().value("positionX").toDouble();
            int posY = (int)xmlReader.attributes().value("positionY").toDouble();

            qDebug().nospace() << text
                               << ", id=" << id
                               << ", x=" << positionX << ", ix=" << posX
                               << ", y=" << positionY << ", iy=" << posY;

            graph_->addVertex(posX, posY);
        }
        // Edges
        else if (text == QStringLiteral("edge")) {
            QString id = xmlReader.attributes().value("id").toString();
            QString vertex1 = xmlReader.attributes().value("vertex1").toString();
            QString vertex2 = xmlReader.attributes().value("vertex2").toString();

            qDebug().nospace() << text
                               << ", id=" << id
                               << ", v1= " << vertex1
                               << ", v2= " << vertex2;

            graph_->linkVertices(vertex1.toInt(), vertex2.toInt());
        }
    }

    if (xmlReader.hasError()) {
        ui->statusBar->showMessage("Error parsing XML: " + xmlReader.errorString());
    }
    else {
        ApplyColorerSolver();

        updateNodes();
        updateEdges();
    }
}

void MainWindow::ApplyColorerSolver()
{
    switch (methodId_) {
    case ColorerSolver::Backtrace:
        on_actionBacktrack_triggered();
        break;
    case ColorerSolver::Bruteforce:
        on_actionBruteforce_triggered();
        break;
    default:
        methodId_ = ColorerSolver::Greedy;
    case ColorerSolver::Greedy:
        on_actionGreedy_triggered();
        break;
    }
}
