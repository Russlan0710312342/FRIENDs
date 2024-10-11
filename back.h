#ifndef BACK_H
#define BACK_H

#include <QObject>
#include <print.h>


class Back : public QObject
{
    Q_OBJECT
public:
    explicit Back(QObject *parent = nullptr);;


    void start();
private slots:


signals:


private:

};

#endif // BACK_H
