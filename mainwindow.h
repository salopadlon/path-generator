#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QtCore>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <algorithm>
#include "xmlmap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonLoad_clicked();
    void on_buttonCar_clicked();
    void on_buttonCone_clicked();
    void on_buttonRemove_clicked();

private:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

    Ui::MainWindow *ui;
    QString fileName;
    QPoint carpoint, conepoint;
    bool addCar, addCone, removeCone;
    std::vector<cone> cones;
};
#endif // MAINWINDOW_H
