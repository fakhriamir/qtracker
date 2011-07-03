#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include "database.h"
#include "qmldatabase.h"

#define ENABLE_DEBUG
#include "helpers.h"

qmlRefpoint::qmlRefpoint()
    : _name("refpt")
    , _refid(-1)
    , _mapid(-1)
    , _latitude(0)
    , _longitude(0)
    , _x(0)
    , _y(0)
    , _dirty(true)
{
    ENTER("")
    EXIT("")
}

qmlRefpoint::qmlRefpoint(int id)
    : _name("refpt")
    , _mapid(-1)
    , _refid(-1)
    , _latitude(0)
    , _longitude(0)
    , _x(0)
    , _y(0)
    , _dirty(true)
{
    ENTER("")
    QSqlDatabase& db = Database::Db();
    QSqlQuery q("SELECT * FROM mappoints WHERE mappt='" + QString::number(id) + "'",db);
    if (q.next())
    {
        _refid = id;
        _mapid     = getIntField(q,"mapid");
        _name      = getStringField(q,"name");
        _latitude  = getDoubleField(q,"latitude");
        _longitude = getDoubleField(q,"longitude");
        _x         = getDoubleField(q,"x");
        _y         = getDoubleField(q,"y");
        _dirty     = false;
    }
    EXIT("")
}

qmlRefpoint::qmlRefpoint(const QSqlQuery& q)
    : _dirty(false)
{
    ENTER("")
    _refid     = getIntField(q,"mappt");
    _mapid     = getIntField(q,"mapid");
    _name      = getStringField(q,"name");
    _latitude  = getDoubleField(q,"latitude");
    _longitude = getDoubleField(q,"longitude");
    _x         = getDoubleField(q,"x");
    _y         = getDoubleField(q,"y");
    EXIT("")
}

void qmlRefpoint::save()
{
    QSqlDatabase& db = Database::Db();
    QSqlQuery q(db);
    if (_refid>0)
        q.exec("REPLACE INTO mappoints (mappt,mapid,name,latitude,longitude,x,y) VALUES (\"" + QString::number(_refid) + "\",\"" + QString::number(_mapid) + "\",\"" + _name  + "\",\"" + QString::number(_latitude)  + "\",\"" + QString::number(_longitude)  + "\",\"" + QString::number(_x) + "\",\"" + QString::number(_y) + "\")");
    else
        q.exec("INSERT  INTO mappoints (mapid,name,latitude,longitude,x,y) VALUES (\"" + QString::number(_mapid) + "\",\"" + _name  + "\",\"" + QString::number(_latitude)  + "\",\"" + QString::number(_longitude)  + "\",\"" + QString::number(_x) + "\",\"" + QString::number(_y) + "\")");
    _dirty = false;
}
