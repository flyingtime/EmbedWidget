#ifndef FINDITEM_H
#define FINDITEM_H

#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlApplicationEngine>

static QQuickItem* FindItemByName(QList<QObject*> nodes, const QString& name);
static QQuickItem* FindItemByName(QList<QQuickItem*> nodes, const QString& name);

static QQuickItem* FindItemByName(QList<QQuickItem*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++){
        // search for node
        if (nodes.at(i) && nodes.at(i)->objectName() == name){
            qDebug() << nodes.at(i)->objectName();
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // search in children
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0){
            QQuickItem* item = FindItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // not found
    return NULL;
}


static QQuickItem* FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++){
        // search for node
        if (nodes.at(i) && nodes.at(i)->objectName() == name){
            qDebug() << nodes.at(i)->objectName();
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // search in children
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0){
            QQuickItem* item = FindItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // not found
    return NULL;
}

static QQuickItem* FindItemByName(QQuickWidget* engine, const QString& name)
{
    if(engine->rootObject()->objectName() == name) {
        return engine->rootObject();
    }

    return FindItemByName(engine->rootObject()->childItems(), name);
}

static QQuickItem* FindItemByName(QQmlApplicationEngine* engine, const QString& name)
{
    return FindItemByName(engine->rootObjects(), name);
}

#endif // FINDITEM_H
