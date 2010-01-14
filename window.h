#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QWidget>
#include "updatemailcount.h"

class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;

class Window : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface","org.notifier.Launcher")

public:
    Window();
    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);
    void updateIcon();

public slots:
    Q_SCRIPTABLE void newMsg();
    Q_SCRIPTABLE void nonewMsg();
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void updateMail(int mailCount);

private:
    bool exists();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();
    QGroupBox *messageGroupBox;
    QLabel *durationLabel;
    QSpinBox *durationSpinBox;
    QTimer *timer;
    QString *filename;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    UpdateMailCount updateMailCount;
    QString currentIcon;
    int mailCount;

};

#endif
