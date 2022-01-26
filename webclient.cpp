#include "webclient.h"
#include <thread>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(hostname, &QLineEdit::returnPressed, this, &Webclient::on_send_clicked);
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::responce);
}

void Webclient::connected()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_hostname + "\r\n\r\n").toLocal8Bit());
}

void Webclient::responce()
{
    output->setText(m_socket->readAll());
    m_socket->disconnectFromHost();
}

void Webclient::on_send_clicked()
{
    if(!hostname->text().isEmpty())
    {
        m_hostname = hostname->text();
        m_socket->connectToHost(m_hostname, m_port);
        if(!m_socket->waitForConnected(5000))
        {
            output->setText(m_hostname + " - Zeitüberschreitung der Anforderung!");
            m_socket->reset();
        }
    }
    else
        output->setText("Bitte geben Sie einen Hostname ein!");
}
