/*
 * datamonitor.h
 *
 *  Created on: 30 jul 2010
 *      Author: Mark Hurenkamp
 */

#ifndef DATAMONITOR_H_
#define DATAMONITOR_H_

#include <QObject>
#include <QWidget>
#include <QSettings>
#include <QGeoCoordinate>
#include <QGeoSatelliteInfo>
class QDateTime;
class QSettings;
class WayPoint;
class QGroupBox;
class QButtonGroup;
class QListWidget;
class QComboBox;
class QWidget;
class QRadioButton;
class QHeadingWidget;
class QBoxLayout;


namespace QtMobility
{
    class QGeoPositionInfo;
    class QGeoPositionInfoSource;
    //class QGeoSatelliteInfo;
    class QGeoSatelliteInfoSource;
    class QCompass;
    class QCompassReading;
}
using namespace QtMobility;

class QMonitorOptions: public QWidget
{
	Q_OBJECT

signals:
	void changed();
	
public:
    QMonitorOptions(QDialog* d);
    ~QMonitorOptions();
    
protected:
    virtual void resizeEvent(QResizeEvent * event);

public slots:
    void noneselected();
    void waypointselected();
    void routeselected();
    void trackselected();
    
    void apply();
    
private:
    QSettings settings;
	QBoxLayout* center;
    QGroupBox* typegroup;
    QButtonGroup* typebuttons;
    QListWidget* wptcombo;
    QListWidget* trkcombo;
    QListWidget* rtecombo;
    QWidget* filler;
    QStringList list;
    QString wptname;
    QString trkname;
    QString rtename;
    int montype;
};

class MonitorStrategy: public QObject
{
	Q_OBJECT

signals:
	void BearingUpdated(double);
	void DistanceUpdated(double);
	void TimeUpdated(const QDateTime&);

public:
	MonitorStrategy(int type=0);
	virtual void OnPositionUpdate(const QGeoPositionInfo& info) {}
	virtual void OnTimeUpdate(const QDateTime& time) {}
	virtual void OnHeadingUpdate(int heading) {}
	int Type() { return type; }
	
protected:
	void SetType(int t) { type = t; }
private:
	int type;
};

class WayPointStrategy: public MonitorStrategy
{
public:
	WayPointStrategy(const WayPoint& wpt);
	WayPointStrategy(const QString& wpt);
	
	virtual void OnPositionUpdate(const QGeoPositionInfo& info);
private:
	QString name;
	QGeoCoordinate currentposition;
	QGeoCoordinate targetposition;
};

class DataMonitor: public QObject
{
	Q_OBJECT
	
signals:
	void PositionUpdated(const QGeoPositionInfo&);
	void SatellitesInViewUpdated(const QList<QGeoSatelliteInfo>&);
	void SatellitesInUseUpdated(const QList<QGeoSatelliteInfo>&);
	
	void HeadingUpdated(double);
	void SpeedUpdated(double);
	void AltitudeUpdated(double);
	
	void BearingUpdated(double);
	void DistanceUpdated(double);
	void TimeUpdated(const QDateTime&);
	
public slots:
    void OnPositionUpdate(const QGeoPositionInfo& info);
	void OnHeadingUpdate();
	void OnTimeUpdate();
	void SetStrategy(MonitorStrategy *s);
	void UpdateSatsInUse(const QList<QGeoSatelliteInfo>& inuse)   { satsinuse = inuse;   emit SatellitesInUseUpdated(inuse); } 
	void UpdateSatsInView(const QList<QGeoSatelliteInfo>& inview) { satsinview = inview; emit SatellitesInViewUpdated(inview); } 
	
public:
    static DataMonitor& Instance();
	virtual ~DataMonitor();
	const QList<QGeoSatelliteInfo>& SatsInUse() { return satsinuse; }
	const QList<QGeoSatelliteInfo>& SatsInView() { return satsinview; }
	
private:
    static DataMonitor* instance;
	DataMonitor();
	
private:
	MonitorStrategy* strategy;
    QSettings settings;
	QGeoPositionInfoSource* possource;
    QGeoSatelliteInfoSource* satsource;
    QList<QGeoSatelliteInfo> satsinuse;
    QList<QGeoSatelliteInfo> satsinview;
    QCompass* compass;
    QCompassReading* reading;
}; 

#endif /* DATAMONITOR_H_ */
