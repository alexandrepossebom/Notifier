#ifndef MAILCHECKER_H
#define MAILCHECKER_H

#include <QObject>
#include <QStringList>

class MailChecker : public QObject
{
    Q_OBJECT
public:
    explicit MailChecker(QObject *parent = 0);
    int getNewMailCount();
    QStringList ignoreList;

private:
    bool ignore;
    int count;

};

#endif // MAILCHECKER_H
