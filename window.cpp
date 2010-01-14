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
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    currentIcon = ":/images/nonew.gif";
    mailCount = 0;
    updateIcon();

    trayIcon->show();
    setWindowTitle(tr("Systray"));
    resize(130, 100);

    connect(&updateMailCount,SIGNAL(valueMailChanged(int)),this,SLOT(updateMail(int)));
}
void Window::updateMail(int mc)
{
//    trayIcon->showMessage("New Mail",QString("You have ").append(mc));
    mailCount = mc;
    updateIcon();
}

void Window::newMsg()
{
    currentIcon = ":/images/new.gif";
    updateIcon();
}

void Window::nonewMsg()
{
    currentIcon = ":/images/nonew.gif";
    updateIcon();
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

void Window::updateIcon()
{
    QPixmap pix(currentIcon);
    if (mailCount)
    {
        QRect r(0,0,pix.width()/2,pix.height()/2);
        r.moveBottomRight(pix.rect().bottomRight());

        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing, true);

        p.setPen(Qt::red);
        p.setBrush(Qt::red);
        p.drawEllipse(r);

        QFont f = p.font();
        f.setPointSize(r.height()-10);
        f.setBold(true);
        p.setFont(f);
        p.setPen(Qt::white);
        p.drawText(r, Qt::AlignCenter, QString::number(mailCount));
    }

    trayIcon->setIcon(QIcon(pix));
}
