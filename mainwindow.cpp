#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->addCar = false;
    this->addCone = false;
    this->removeCone = false;
    this->carpoint = QPoint(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    if (this->carpoint.x() > 0 && this->carpoint.y() > 0) {
        QPen penCar(Qt::black);
        penCar.setWidth(10);

        painter.setPen(penCar);
        painter.drawPoint(carpoint);
    }

    if (!this->cones.empty()) {
        QPen conePen;
        conePen.setWidth(10);

        for (auto icone : this->cones) {
            QPoint cone(icone.coords.x, icone.coords.y);

            if (icone.color.compare("blue") == 0) {
                conePen.setColor(Qt::blue);
            }

            else if (icone.color.compare("yellow") == 0) {
                conePen.setColor(Qt::yellow);
            }

            else if (icone.color.compare("orange") == 0) {
                conePen.setColor("orange");
            }

            else {
                std::cout << "Cone without color!" << std::endl;
            }

            painter.setPen(conePen);
            painter.drawPoint(cone);
        }
    }
}

void MainWindow::on_buttonLoad_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "../PathSim/resources", tr("XML Files (*.xml *.sdf)"));

    if (fileName.size() > 0) {
        this->cones.clear();
        this->cones = XMLMap(fileName.toLocal8Bit().data()).getCones();

        double min_x = 0;
        double min_y = 0;
        double max_x = 0;
        double max_y = 0;

        for (auto cone : this->cones) {
            if (min_x > cone.coords.x) {
                min_x = cone.coords.x;
            }

            if (min_y > cone.coords.y) {
                min_y = cone.coords.y;
            }

            if (max_x < cone.coords.x) {
                max_x = cone.coords.x;
            }

            if (max_y < cone.coords.y) {
                max_y = cone.coords.y;
            }
        }

        for (unsigned long long i = 0; i < this->cones.size(); ++i) {
            this->cones[i].coords.x = (((this->cones[i].coords.x - min_x)
                                        * (this->size().width() - 100)) / (max_x - min_x)) + 50;

            this->cones[i].coords.y = (((this->cones[i].coords.y - min_y)
                                        * (this->size().height() - 100)) / (max_y - min_y)) + 50;

            std::cout << this->cones[i].coords.x << ' ' << this->cones[i].coords.y << ' '
                      << this->cones[i].color << std::endl;
        }
    }

    this->update();
}

void MainWindow::on_buttonCar_clicked()
{
    this->removeCone = false;
    this->addCone = false;
    this->addCar = true;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton) {
        if (addCar) {
            this->carpoint.setX(e->x());
            this->carpoint.setY(e->y());
            this->addCar = false;
        }

        if (addCone) {
            cone cone;
            cone.coords.x = e->x();
            cone.coords.y = e->y();

            if (ui->colorBox->currentText() == "Yellow") {
                cone.color = "yellow";
            }

            else if (ui->colorBox->currentText() == "Blue") {
                cone.color = "blue";
            }

            else if (ui->colorBox->currentText() == "Orange") {
                cone.color = "orange";
            }

            else {
                std::cout << "No color chosen";
            }

            this->cones.push_back(cone);
        }

        if (removeCone) {
            if (!this->cones.empty()) {
                for (auto icone = this->cones.begin(); icone != this->cones.end(); ++icone) {
                    if ((sqrt(pow(e->x() - icone->coords.x, 2) + (pow(e->y() - icone->coords.y, 2)))) < 5) {
                        this->cones.erase(icone);
                        break;
                    }
                }
            }
        }
    }

    this->update();
}

void MainWindow::on_buttonCone_clicked()
{
    this->removeCone = false;
    this->addCone = true;
}

void MainWindow::on_buttonRemove_clicked()
{
    this->addCone = false;
    this->removeCone = true;
}
