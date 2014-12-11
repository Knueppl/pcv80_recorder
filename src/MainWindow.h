#ifndef ___MAIN_WINDOW_H___
#define ___MAIN_WINDOW_H___

#include <string>

#include <QMainWindow>
#include <QTimer>

#include "Rs485.h"
#include "Pcv80.h"
#include "Measure.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(const std::string& device);

private slots:
    void tick(void);
    void exportToCsv(void);

private:
    Ui::MainWindow* _ui;
    Rs485 _bus;
    Pcv80 _sensor;
    QTimer _timer;
    QAction* _record;

    std::vector<Measure> _measurements;
};

#endif
