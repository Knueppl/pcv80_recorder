#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(const std::string& device)
    : QMainWindow(0),
      _ui(new Ui::MainWindow),
      _bus(device, Rs485::BR115200),
      _sensor(_bus, 0)
{
    _ui->setupUi(this);
    this->connect(&_timer, SIGNAL(timeout()), this, SLOT(tick()));

    QMenuBar* bar = this->menuBar();
    QMenu* menu = bar->addMenu("Recorder");
    _record = new QAction("Run", menu);
    _record->setCheckable(true);
    menu->addAction(_record);

    menu->addAction("Export", this, SLOT(exportToCsv()));

    _timer.start(1);
}

void MainWindow::tick(void)
{
    _sensor.grab();

    _ui->_labelPosition->setText(QString("Position: ") + QString::number(_sensor.position()) + QString(" m"));
    _ui->_labelSpeed->setText(QString("Speed: ") + QString::number(_sensor.speed()) + QString(" m/s"));

    if (_record->isChecked())
    {
        Measure measure(_sensor.position(), _sensor.speed());
        _measurements.push_back(measure);
        _ui->_list->addItem(measure.toString());
    }
}

void MainWindow::exportToCsv(void)
{
    QString name(QFileDialog::getSaveFileName(this, "Save File", "/home", "*.csv"));

    if (name.isNull())
        return;

    QFile file(name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (std::vector<Measure>::const_iterator measure(_measurements.begin());
         measure < _measurements.end();
         ++measure)
    {
        out << measure->stamp.toString("hh:mm:ss.zzz") << "; " << measure->position << "; "
            << measure->speed << "\n";
    }
}
