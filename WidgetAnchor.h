#ifndef WIDGETANCHOR_H
#define WIDGETANCHOR_H

#include <QQuickItem>

class WidgetAnchor: public QObject
{
    QWidget* _pWidget;
    QQuickItem* _pQuickItem;
public:
    WidgetAnchor(QWidget* pWidget, QQuickItem* pItem)
        : QObject(pWidget), _pWidget(pWidget), _pQuickItem(pItem)
    {
        connect(_pQuickItem, &QQuickItem::xChanged, this, &WidgetAnchor::updateGeometry);
        connect(_pQuickItem, &QQuickItem::yChanged, this, &WidgetAnchor::updateGeometry);
        connect(_pQuickItem, &QQuickItem::widthChanged, this, &WidgetAnchor::updateGeometry);
        connect(_pQuickItem, &QQuickItem::heightChanged, this, &WidgetAnchor::updateGeometry);
        updateGeometry();
    }
private:
    void updateGeometry()
    {
        if (_pQuickItem)
        {
            QRectF r = _pQuickItem->mapRectToItem(0, QRectF(_pQuickItem->x(), _pQuickItem->y(), _pQuickItem->width(), _pQuickItem->height()));
            _pWidget->setGeometry(r.toRect());
        }
    }
};

#endif // WIDGETANCHOR_H
