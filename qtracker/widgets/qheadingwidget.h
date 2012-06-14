#ifndef QHEADINGWIDGET_H
#define QHEADINGWIDGET_H

#include <QWidget>
#include <QSettings>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>
#include <QCompass>
#include "qgaugewidget.h"
#include "waypointlist.h"

const int STEPS = 3;
const int TIMER = 330;

using namespace QtMobility;

class QHeadingWidget : public QGaugeWidget
{
    Q_OBJECT
public:
    QHeadingWidget(QWidget *parent = 0);

    void SetDial(double v);
    void SetNeedle(double v);
    void SetRing(double v);

public slots:
    void timerStep();
    void SelectOptions();
	void UpdateHeading(double h);
	void UpdateAzimuth(double a);
	void UpdateDials();
	void ReadSettings();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QSettings settings;
    QTimer *timer;
    double heading;
    double azimuth;
    double setdial;
    double curdial;
    double deltadial;
    int    stepsdial;
    double setneedle;
    double curneedle;
    double deltaneedle;
    int    stepsneedle;
    double setring;
    double curring;
    double deltaring;
    int    stepsring;
    int view;
};

#endif // QHEADINGWIDGET_H