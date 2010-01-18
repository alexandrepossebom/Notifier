#include "updatemailcount.h"
#include <QDebug>
#include <QDirIterator>
#include <QDir>

UpdateMailCount::UpdateMailCount()
{
    QDir dir;
    QDirIterator it("/home/alexandre/Mail/",QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString dirName = it.next();
        if (!dirName.contains("/new")) continue;
        addPath(dirName);
        for (int i = 0; i < mailChecker.ignoreList.size(); ++i)
        {
            if (dirName.contains(mailChecker.ignoreList.at(i)))
            {
                removePath(dirName);
                break;
            }
        }
    }
    connect(this, SIGNAL(directoryChanged(QString)), this, SLOT(slotCount()));
    slotCount();
}

void UpdateMailCount::slotCount()
{
    emit valueMailChanged( mailChecker.getNewMailCount() );
}
