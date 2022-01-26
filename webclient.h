#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include <QAbstractSocket>
#include <QTcpSocket>
#include "ui_webclient.h"

class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

    public:
        explicit Webclient(QWidget *parent = nullptr);

    private slots:
        void on_send_clicked();

    private:
        void connected();
        void responce();

    private:
        QTcpSocket* m_socket;
        QString m_hostname;
        unsigned char m_port = 80;
};

#endif // WEBCLIENT_H
