#ifndef ___MEASURE_H___
#define ___MEASURE_H___

#include <QTime>
#include <QString>

struct Measure
{
    Measure(const float p, const float s)
        : position(p),
          speed(s),
          stamp(QTime::currentTime())
    {

    }

    QString toString(void) const
    {
        return stamp.toString("[hh:mm:ss.zzz]") + QString::number(position) + QString(" m, ") +
            QString::number(speed) + QString(" m/s");
    }

    float position;
    float speed;
    QTime stamp;
};

#endif
