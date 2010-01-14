#include "mailchecker.h"
#include <QDir>
#include <QDebug>
#include <QDirIterator>

MailChecker::MailChecker(QObject *parent) :
        QObject(parent)
{
    ignoreList << "Trash" << "cooker" << "Null" << "Gmail/Freecycle";
}
int MailChecker::getNewMailCount()
{
    count = 0;
    QDir dir;
    QDirIterator it("/home/alexandre/Mail/",QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        ignore = false;
        QString dirName = it.next();
        dir.setPath(dirName);
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

        if (!dirName.contains("/new")) continue;

        for (int i = 0; i < ignoreList.size(); ++i)
        {
            if (dirName.contains(ignoreList.at(i)))
            {
                ignore = true;
                break;
            }
        }

        if (ignore || dir.count() == 0) continue;

        QStringList list = dirName.split("/", QString::SkipEmptyParts);
        count = count + dir.count();
//        qDebug() << dir.count() << list.at(3) << list.at(4);
    }
    return count;
}
