#include <QApplication>
#include <QPushButton>
#include "QmlOSRExpMainWindow.h"
#include "WidgetOSRItem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, true);

    //register diy qml tools
    qmlRegisterType<WidgetOSRItem>("Diy.WidgetOSRItem",1,0, "WidgetOSRItem");

    QmlOSRExpMainWindow w;
    w.show();
    w.load(QUrl("qrc:/WidgetOSRExp.qml"));


    //新建一个QWebView放入qml osr item中
    //QtWebView::initialize();

    //新建一个QWebView放入qml osr item中
    //    QWebView osrWebView;
    //    osrWebView.setUrl(QUrl("http://www.baidu.com"));
    //    w.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(&osrWebView));

    QPushButton* btn = new QPushButton;
    btn->setStyleSheet("background-color:red;");
    btn->setAttribute(Qt::WA_NativeWindow);
    w.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(btn));

    int res =  a.exec();
    return res;
}
