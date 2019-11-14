#ifndef QPREVIEW_H
#define QPREVIEW_H

#include <QtWidgets/QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QDebug>
#include "VideoPlugin.h"

class QPreview:public QObject
{
Q_OBJECT
public slots:
    void cppSlot(const QString &msg) {
        qDebug() << "Called the C++ slot with message:" << msg;
    }
public:
    QPreview();
    void CreatePlugin(QWidget* widget);
    void InitPlugin();
    ~QPreview();
    static void _stdcall CB_MessageCallback(void* pPluginInstance, const char* pRspJsonMsg, void* pUserData);
private:
    void* m_pInstance = nullptr;
};

#endif // QPREVIEW_H
