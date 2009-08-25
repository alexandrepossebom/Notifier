#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QWidget>

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
    Q_CLASSINFO("qdbus interface","org.mandriva.Laucher")

public:
    Window();
    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    Q_SCRIPTABLE void update();
    void setInterval();

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
};

#endif
