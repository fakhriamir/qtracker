#ifndef QMLTIMEMODEL_H
#define QMLTIMEMODEL_H

#include <QStringList>
#include <QUrl>
#include <QObject>
#include <QTime>

class PrivateTimeModel;
class qmlTimeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int   mask    READ mask    NOTIFY maskChanged)
    Q_PROPERTY(QTime current READ current NOTIFY currentChanged)
    Q_PROPERTY(QTime elapsed READ elapsed NOTIFY elapsedChanged)
    Q_PROPERTY(QTime monitor READ monitor NOTIFY monitorChanged)

public:
    int   mask();
    QTime current();
    QTime elapsed();
    QTime monitor();

    explicit qmlTimeModel(QObject *parent = 0);
    ~qmlTimeModel() {}

public slots:
    void reset();

signals:
    void maskChanged();
    void currentChanged();
    void elapsedChanged();
    void monitorChanged();

private:
    PrivateTimeModel* p;
    Q_DISABLE_COPY(qmlTimeModel)
};

#endif // QMLTIMEMODEL_H