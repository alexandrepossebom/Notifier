#include <QtGui>
#include <QDBusConnection>
#include <QDBusInterface>
#include "window.h"

Window::Window()
{
    createMessageGroupBox();
    createActions();
    createTrayIcon();
	 timer = new QTimer(this);
	 QDBusConnection dbus = QDBusConnection::sessionBus();
	 dbus.registerObject("/Interface", this);
	 dbus.registerService("org.mandriva.Launcher");

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(5000);
	 connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	 connect(durationSpinBox,SIGNAL(valueChanged(int)),this, SLOT(setInterval()));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);
	 trayIcon->setIcon(QIcon(":/images/nonew.gif"));
    trayIcon->show();
    setWindowTitle(tr("Systray"));

    resize(130, 100);
}
void Window::setInterval()
{
	timer->setInterval(durationSpinBox->value() * 1000);
}
void Window::update()
{
	printf("oi\n");
	if(exists())
	{	
		trayIcon->setIcon(QIcon(":/images/new.gif"));
	}else{
		trayIcon->setIcon(QIcon(":/images/nonew.gif"));
	}
}

bool Window::exists()
{
	if (FILE * file = fopen("/tmp/irc_msg", "r"))
	{
		fclose(file);
		return true;
	}
	return false;

}
void Window::setVisible(bool visible)
{
    restoreAction->setEnabled(isMaximized() || !visible);
    QWidget::setVisible(visible);
}

void Window::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
		QFile::remove("/tmp/irc_msg");
		trayIcon->setIcon(QIcon(":/images/nonew.gif"));
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void Window::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox(tr("Configuration"));
    durationLabel = new QLabel(tr("Duration:"));
    durationSpinBox = new QSpinBox;
    durationSpinBox->setRange(1, 300);
    durationSpinBox->setSuffix(" s");
    durationSpinBox->setValue(5);
    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(durationLabel, 1, 0);
    messageLayout->addWidget(durationSpinBox, 1, 1);
    messageGroupBox->setLayout(messageLayout);
}

void Window::createActions()
{
    restoreAction = new QAction(tr("Configure"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
