#ifndef UPDATEMAILCOUNT_H
#define UPDATEMAILCOUNT_H

#include <QFileSystemWatcher>
#include "mailchecker.h"

class UpdateMailCount : public QFileSystemWatcher
{
    Q_OBJECT
public:
    UpdateMailCount();

signals:
     void valueMailChanged(int);

public slots:
    void slotCount();

private:
    MailChecker mailChecker;
};
#endif // UPDATEMAILCOUNT_H
