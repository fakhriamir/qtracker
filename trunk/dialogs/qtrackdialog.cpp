#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QResizeEvent>
#include <QDateTime>
#include "qtrackdialog.h"

#include <iostream>
//#define LOG( a ) std::cout << a
#define LOG2( a ) std::cout << a
#define LOG( a )


QNewTrackTab::QNewTrackTab(QTrackTabsDialog *parent)
    : QWidget(parent), center(0), time(0), dist(30)
{
	QDateTime curtime = QDateTime::currentDateTime().toUTC();
	QString trackname = curtime.toString("trk-yyyyMMdd-hhmmss");
	trkname = new QLineEdit(trackname,this);
	
	main = new QVBoxLayout();
	
	QHBoxLayout *namebox = new QHBoxLayout();
	namebox->addWidget(new QLabel(tr("Name:")));
	namebox->addWidget(trkname);

	QHBoxLayout *buttonbox =  new QHBoxLayout();
	QPushButton *cancel =  new QPushButton(tr("Cancel"));
	QPushButton *confirm = new QPushButton(tr("Start"));
	buttonbox->addWidget(confirm);
	buttonbox->addWidget(cancel);
	
	QGroupBox *typegroup = new QGroupBox();
	QRadioButton *typeall  = new QRadioButton(tr("All"));
	QRadioButton *typetime = new QRadioButton(tr("Time based"));
	QRadioButton *typedist = new QRadioButton(tr("Distance based"));
	QVBoxLayout *typebox = new QVBoxLayout;
	typebox->addWidget(typeall);
	typebox->addWidget(typetime);
	typebox->addWidget(typedist);
	typebox->addStretch(1);
	typegroup->setLayout(typebox);
	
	distgroup = new QGroupBox();
	distbuttons = new QButtonGroup(distgroup);
	QRadioButton *dist10m  = new QRadioButton(tr("10m"));
	QRadioButton *dist30m  = new QRadioButton(tr("30m"));
	QRadioButton *dist100m = new QRadioButton(tr("100m"));
	QRadioButton *dist300m = new QRadioButton(tr("300m"));
	QRadioButton *dist1km  = new QRadioButton(tr("1km"));
	distbuttons->addButton(dist10m,  0);
	distbuttons->addButton(dist30m,  1);
	distbuttons->addButton(dist100m, 2);
	distbuttons->addButton(dist300m, 3);
	distbuttons->addButton(dist1km,  4);
	QVBoxLayout *distbox = new QVBoxLayout();
	distbox->addWidget(dist10m);
	distbox->addWidget(dist30m);
	distbox->addWidget(dist100m);
	distbox->addWidget(dist300m);
	distbox->addWidget(dist1km);
	distbox->addStretch(1);
	distgroup->setLayout(distbox);

	timegroup = new QGroupBox();
	timebuttons = new QButtonGroup(timegroup);
	QRadioButton *time5s  = new QRadioButton(tr( "5s"));
	QRadioButton *time15s = new QRadioButton(tr("15s"));
	QRadioButton *time1m  = new QRadioButton(tr( "1m"));
	QRadioButton *time5m  = new QRadioButton(tr( "5m"));
	QRadioButton *time15m = new QRadioButton(tr("15m"));
	timebuttons->addButton(time5s, 0);
	timebuttons->addButton(time15s,1);
	timebuttons->addButton(time1m, 2);
	timebuttons->addButton(time5m, 3);
	timebuttons->addButton(time15m,4);
	QVBoxLayout *timebox = new QVBoxLayout();
	timebox->addWidget(time5s);
	timebox->addWidget(time15s);
	timebox->addWidget(time1m);
	timebox->addWidget(time5m);
	timebox->addWidget(time15m);
	timebox->addStretch(1);
	timegroup->setLayout(timebox);

    QWidget *filler = new QWidget;
    filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	center = new QBoxLayout(QBoxLayout::LeftToRight);
	center->addWidget(typegroup);
	center->addWidget(distgroup);
	center->addWidget(timegroup);
	main->addLayout(namebox);
	main->addLayout(center);
	main->addWidget(filler);
	main->addLayout(buttonbox);
	setLayout(main);
	
	typedist->setChecked(true);
	dist30m->setChecked(true);
	time15s->setChecked(true);
	distgroup->show();
	timegroup->hide();
	cancel->show();
	confirm->show();
	
	connect(cancel,SIGNAL(clicked()),parent,SLOT(reject()));
	connect(confirm,SIGNAL(clicked()),this,SLOT(emitnewtrack()));
	connect(typeall, SIGNAL(clicked()),this,SLOT(selectall()));
	connect(typetime,SIGNAL(clicked()),this,SLOT(selecttime()));
	connect(typedist,SIGNAL(clicked()),this,SLOT(selectdistance()));
	connect(timebuttons, SIGNAL(buttonClicked(int)),this,SLOT(updatetime(int)));
	connect(distbuttons, SIGNAL(buttonClicked(int)),this,SLOT(updatedistance(int)));
	
	connect(this,SIGNAL(newtrack(QString,int,int)),parent,SLOT(emitnewtrack(QString,int,int)));
}

void QNewTrackTab::resizeEvent( QResizeEvent * event )
{
    LOG( "QNewTrackTab::resizeEvent()\n"; )
    if (!center) return;
    
    if (event->size().width() < event->size().height())
	    center->setDirection(QBoxLayout::TopToBottom);
	else
	    center->setDirection(QBoxLayout::LeftToRight);

    QWidget::resizeEvent(event);
}

void QNewTrackTab::selectall()
{
	time = 0;
	dist = 0;
	timegroup->hide();
	distgroup->hide();
}

void QNewTrackTab::selecttime()
{
	dist = 0;
	distgroup->hide();
	updatetime(timebuttons->checkedId());
	timegroup->show();
}

void QNewTrackTab::updatetime(int id)
{
	int values[5] = { 5, 15, 60, 300, 900 };
	time = values[id];
}

void QNewTrackTab::selectdistance()
{
	time = 0;
	timegroup->hide();
	updatedistance(distbuttons->checkedId());
	distgroup->show();
}

void QNewTrackTab::updatedistance(int id)
{
	int values[5] = { 10, 30, 100, 300, 1000 };
	dist = values[id];
}

QNewTrackTab::~QNewTrackTab()
{
    delete trkname;
}

QTrackTabsDialog::QTrackTabsDialog(QString title, QString name, QWidget *parent)
    : QDialog(parent)
{
    tabs = new QTabWidget(this);
    //tabs->setStyleSheet("QTabBar::tab { border:1px; margin-top:1px; margin-bottom:1px }");
    tabs->addTab(new QNewTrackTab(this), tr("New"));
    tabs->addTab(new QWidget(this), tr("List"));
    tabs->addTab(new QWidget(this), tr("Options"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabs);
    setLayout(mainLayout);
    setAttribute(Qt::WA_DeleteOnClose);
}

void QTrackTabsDialog::emitnewtrack(QString name, int time, int distance)        
{ 
    LOG( "QTrackTabsDialog::emitnewtrack(" << name.toStdString() << ", " << time << ", " << distance << ")\n"; )
	emit newtrack(name,time,distance);           
    accept();
}

void QTrackTabsDialog::emitdeletetrack(QString name)                             
{ 
    LOG2( "QTrackTabsDialog::emitdeletetrack()\n"; )
	emit deletetrack(name);                      
    accept();
}

void QTrackTabsDialog::emitchangeoptions(bool autostart, int time, int distance) 
{ 
    LOG2( "QTrackTabsDialog::emitchangeoptions()\n"; )
	emit changeoptions(autostart,time,distance); 
    accept();
}

void QTrackTabsDialog::accept()
{
    QDialog::accept();
    close();
}

QTrackTabsDialog::~QTrackTabsDialog()
{
    LOG( "QTrackTabsDialog::~QTrackTabsDialog()\n"; )
    delete tabs;
}
