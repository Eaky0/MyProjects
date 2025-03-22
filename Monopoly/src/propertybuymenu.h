
#ifndef PROPERTYBUYMENU_H
#define PROPERTYBUYMENU_H

#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QPushButton>


class PropertyBuyMenu : public QGraphicsRectItem
{
public:
    PropertyBuyMenu();
    QPushButton *getYesButton();
    QPushButton* getNoButton();
private:
    QPushButton* m_Yes;
    QPushButton* m_No;
    QGraphicsProxyWidget* m_YesProxy;
    QGraphicsProxyWidget* m_NoProxy;
};

#endif // PROPERTYBUYMENU_H
