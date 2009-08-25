#include <QtGui>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include "window.h"

Window::Window()
{
    createActions();
    createTrayIcon();
	 QDBusConnection dbus = QDBusConnection::sessionBus();
	 dbus.registerObject("/Interface", this, QDBusConnection::ExportAllSlots);
	 dbus.registerService("org.notifier.Launcher");
	 connect(trayIcon,
			 SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			 this, 
			 SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	 trayIcon->setIcon(QIcon(":/images/nonew.gif"));
    trayIcon->show();
    setWindowTitle(tr("Systray"));
    resize(130, 100);
}
void Window::newMsg()
{
		trayIcon->setIcon(QIcon(":/images/new.gif"));
}
void Window::nonewMsg()
{
		trayIcon->setIcon(QIcon(":/images/nonew.gif"));
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
	switch (reason)
	{
		case QSystemTrayIcon::Trigger:
		case QSystemTrayIcon::DoubleClick:
			trayIcon->setIcon(QIcon(":/images/nonew.gif"));
			break;
		case QSystemTrayIcon::MiddleClick:
			break;
		default:
			;
	}
}

void Window::createActions()
{
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
