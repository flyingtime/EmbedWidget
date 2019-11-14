#include <QApplication>
#include <QPushButton>
#include "qpreview.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QQuickWidget>
#include <QPushButton>
#include <QDebug>
#include <QQmlProperty>
#include <QQuickView>
#include "WidgetAnchor.h"
#include "findItem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "start app";

    auto pqw = new QQuickWidget;
    const QUrl url(QStringLiteral("qrc:/EmbedWidget.qml"));
    pqw->setSource(url);
    pqw->setResizeMode(QQuickWidget::SizeRootObjectToView);
    pqw->setAttribute(Qt::WA_DeleteOnClose);
    pqw->resize(1280,720);

    QQmlEngine* engine = pqw->engine();
    QQmlComponent component(engine,url);
    QObject *object = component.create();

    qDebug() << "Property value:" << QQmlProperty::read(object, "someNumber").toInt();

    auto pOwt = new QWidget(pqw);
    pOwt->setStyleSheet("background-color:grey;");

    auto x = FindItemByName(pqw,"videoPlugin");
    if(x != NULL) {
        qDebug() << x->height();
        qDebug() << x->width();
        pOwt->move(x->x(),x->y());
        pOwt->resize(x->width(),x->height());
        //new WidgetAnchor(pOwt, x);
    } else {
        qDebug() << "layoutItem not found!!!";
    }

    QPreview *videoPlugin = new QPreview();
    QObject *item = pqw->rootObject();
    QObject::connect(item, SIGNAL(qmlSignal(QString)),
                     videoPlugin, SLOT(cppSlot(QString)));
    videoPlugin->CreatePlugin(pOwt);
    videoPlugin->InitPlugin();
    pqw->show();

    return app.exec();
}
