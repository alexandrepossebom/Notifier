#ifndef UPDATEMAILCOUNT_H
#define UPDATEMAILCOUNT_H

#include <QThread>
#include "mailchecker.h"

class UpdateMailCount : public QThread
{
    Q_OBJECT
public:
    UpdateMailCount();

signals:
     void valueMailChanged(int);

protected:
    void run();
};
#endif // UPDATEMAILCOUNT_H
