#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "model.h"
#include "grid.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PlotButton_clicked()
{
    int N_in = ui->spinBox1->value();
    int M_in = ui->spinBox2->value();
    Grid TestGrid(N_in, M_in);

    //QVector<double> x, y;
    QVector<double> xGrid, yGrid;
    QCPCurve *newCurve = new QCPCurve (ui->Graph->xAxis, ui->Graph->yAxis);

    QPen pen;
    QPen pennode;

    pen.setColor(Qt::GlobalColor(7));
    pen.setWidth(1);

    TestGrid.SetGrid();

    ui->Graph->clearGraphs();
    //Подписываем оси Ox и Oy
    ui->Graph->xAxis->setLabel("x");
    ui->Graph->yAxis->setLabel("y");
    //Установим область, которая будет показываться на графике
    ui->Graph->xAxis->setRange(-1.0, 4.0);//Для оси Ox
    ui->Graph->yAxis->setRange(-1.0, 2.0);//Для оси Oy

    int iGraph=-1;
    for (int i=0; i<N_in; i++)  {
        for (int j=0; j<M_in; j++) {
            xGrid.clear();
            yGrid.clear();
            for (int k=0; k<4; k++) {
                xGrid.push_back(TestGrid.Array[i][j].Point[k].X);
                yGrid.push_back(TestGrid.Array[i][j].Point[k].Y);
            }

            ui->Graph->addGraph();
            iGraph++;
            ui->Graph->graph(iGraph)->setPen(pen);
            ui->Graph->graph(iGraph)->setData(xGrid, yGrid);
            ui->Graph->graph(iGraph)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
            ui->Graph->replot();
        }
    }

    ui->Graph->addGraph();
    iGraph++;
    pennode.setColor(Qt::GlobalColor(14));
    ui->Graph->graph(iGraph)->setPen(pennode);
    xGrid.clear();
    yGrid.clear();
    xGrid.push_back(TestGrid.NodeGrid[0][0].X);
    yGrid.push_back(TestGrid.NodeGrid[0][0].Y);
    xGrid.push_back(TestGrid.NodeGrid[0][1].X);
    yGrid.push_back(TestGrid.NodeGrid[0][1].Y);
    xGrid.push_back(TestGrid.NodeGrid[1][1].X);
    yGrid.push_back(TestGrid.NodeGrid[1][1].Y);
    xGrid.push_back(TestGrid.NodeGrid[1][0].X);
    yGrid.push_back(TestGrid.NodeGrid[1][0].Y);
    xGrid.push_back(TestGrid.NodeGrid[0][0].X);
    yGrid.push_back(TestGrid.NodeGrid[0][0].Y);

    newCurve->setData(xGrid, yGrid);
    ui->Graph->graph(iGraph)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->Graph->replot();

}
