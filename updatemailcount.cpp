#include "updatemailcount.h"
#include <QDebug>

UpdateMailCount::UpdateMailCount()
{
    QThread::start();
}

void UpdateMailCount::run()
{
    MailChecker mailChecker;
    int count = 0;
    int oldcount = 0;
    while (true) {
        count = mailChecker.getNewMailCount();
        if (count != oldcount)
            emit valueMailChanged( count );
        oldcount = count;
        sleep( 10 );
    }
}
