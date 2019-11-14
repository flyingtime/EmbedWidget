#include "qpreview.h"
#include <QVBoxLayout>
#include <QPushButton>

QPreview::QPreview() {

}

void QPreview::CreatePlugin(QWidget *widget)
{
    m_pInstance = VideoPlugin_CreatePluginInstance(reinterpret_cast<void*>(widget->winId()));
    if (m_pInstance != nullptr)
    {
        void* pHandle = VideoPlugin_GetWindowHandle(m_pInstance);

        QWidget* pWidget = QWidget::find((WId)pHandle);
        if (pWidget != nullptr)
        {
            pWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

            QVBoxLayout * layout = new QVBoxLayout();//铺满布局
            layout->addWidget(pWidget);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0,0,0,0);
            widget->setLayout(layout);

            VideoPlugin_SetMessageCallback(m_pInstance, QPreview::CB_MessageCallback, this);
        }
    }
}

void QPreview::InitPlugin(){
    QJsonObject obj;
    QJsonDocument doc;
    obj.insert("appkey", "22089243");
    obj.insert("secret", "zlb8QnaumrUU3ZoTsbGK");
    obj.insert("ip", "192.168.0.17");
    obj.insert("port", 443);
    obj.insert("playMode", 0);
    QString _layout = "2x2";
    obj.insert("layout", _layout);
    QString _snapDir = "d:\temp";
    obj.insert("snapDir", _snapDir);
    QString _videoDir = "d:\temp";
    obj.insert("videoDir", _videoDir);
    int _enableHTTPS = 1;
    obj.insert("enableHTTPS", _enableHTTPS);
    int _showSmart = 1;
    obj.insert("showSmart", _showSmart);
    int _showToolbar = 1;
    obj.insert("showToolbar", _showToolbar);
    QString _buttonIDs = "0,16,256,257,258,259,260,512,513,514,515,516,517,768,769";
    obj.insert("buttonIDs", _buttonIDs);
    doc.setObject(obj);

    QJsonObject objRoot;
    QJsonDocument docRoot;
    objRoot.insert("argument", doc.toJson(QJsonDocument::Compact).toStdString().c_str());
    objRoot.insert("funcName", "init");
    docRoot.setObject(objRoot);
    char* pszRet = VideoPlguin_GerneralRequest(m_pInstance, docRoot.toJson(QJsonDocument::Compact).toStdString().c_str());
    if (pszRet != nullptr)
    {
        // 解析，成功后需要设置一些数据
        QJsonParseError err;
        QString qszJsonRequest = QString::fromStdString(pszRet).simplified();
        QJsonDocument docRoot = QJsonDocument::fromJson(qszJsonRequest.toUtf8(), &err);
        if (QJsonParseError::NoError == err.error && docRoot.isObject())
        {
//            QJsonObject& jsonObj = docRoot.object();
//            if (jsonObj.contains("code"))
//            {
//                if (0 == jsonObj.take("code").toInt())
//                {
//                    // 获取布局信息
//                    //__getLayout(false);
//                }
//            }
        }

        //__insertMsgTip(QString(pszRet));
        VideoPlugin_ReleaseMemory(pszRet);
        pszRet = nullptr;
    }
}

QPreview::~QPreview()
{
    if (m_pInstance != nullptr)
    {
        VideoPlugin_DestroyPluginInstance(m_pInstance);
        m_pInstance = nullptr;
    }
}

void _stdcall QPreview::CB_MessageCallback(void* pPluginInstance, const char* pRspJsonMsg, void* pUserData)
{
    QPreview* pThis = reinterpret_cast<QPreview*>(pUserData);
    if (nullptr == pThis)
    {
        return;
    }

//    if (pRspJsonMsg != nullptr && pThis->ui.m_pEdtMsgTip != nullptr)
//    {
//        emit pThis->sig_Message(QString(pRspJsonMsg));
//    }
}
