//Author: Kumas Atakan, Ieracitano Alessio
//-------------------------
//Methods made by Atakan:
//PropertyView, enablePropertyOptionButton, disablePropertyOptionButtons, showStreetOptionsButtons, hide StreetOptionsButtons,
//getBuyHotel, getBuyHouse, getSellHotel, getSellHouse, getSteetsButton, getStationButtons, getCompaniesButton,
//getBuyBuilding, getBuildingTable, getOptionMode, setOptionMode, AdjustTableOptions, setStreetColors
//-------------------------
//Methods made by Alessio:
//showInhertedMortgageOptions, hideInhertedMortgageOptions, getKeepMortgagebutton, setInhertedOptions
//setScale, makebuttons, setposition
//--------------------------
#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QTableWidget>
#include <QListWidget>

#include "street.h"
enum class OptionMode {STREET, STATION, COMPANY, INHERTED};


class PropertyView
{
public:
    PropertyView(QGraphicsScene* Scene);

    //Enabling methods
    void enablePropertyOptionButton();


    //Disabling methods
    void disablePropertyOptionButtons();

    //Visual methods
    void showStreetOptionButtons();
    void hideStreetOptionButtons();

    void hideStationCompanyOptionButtons();
    void showStationCompanyOptionButtons();

    void showInhertedMortgageOptions();
    void hideInhertedMortgageOptions();

    //Getters
    QPushButton *getBuyHotel();
    QPushButton *getBuyHouse();
    QPushButton *getSellHotel();
    QPushButton *getSellHouse();
    QPushButton *getStreetsButton();
    QPushButton *getStationsButton();
    QPushButton *getCompaniesButton();

    QPushButton *getBuyBuilding();
    QPushButton *getCancelButton();

    QPushButton *getMortgageTakeOutButton();
    QPushButton *getMortgagePayOffButton();
    QPushButton* getKeepMortgageButton();

    int getSelectedRow();
    QTableWidget* getBuildingTable();

    OptionMode getOptionMode();

    //setter
    void setOptionMode(OptionMode newMode);
    void AdjustTableOptions();
    void setStreetColors(const Street::Color &StreetColor, const int &Index);
private:

    void setStreetOptions();
    void setStationOptions();
    void setCompanyOptions();
    void setInhertedOptions();

    //Method:
    //Makes all the buttons (QPushbuttons as well as their proxy)
    void makeButtons(QGraphicsScene* Scene);

    //Method:
    //Sets the position of the buttons
    void setPosition();

    //Method:
    //Sets the scale for the buttons
    void setScale();

    //Method:
    //Sets the buttons to hide
    void setBeginState();

    //Members:
    OptionMode m_CurrentOption;
    QTableWidget *m_PlayerProperties;

    QPushButton *m_BuyBuildingbutton;
    QPushButton *m_BuyHouseButton;
    QPushButton *m_BuyHotelButton;
    QPushButton *m_SellHouseButton;
    QPushButton *m_SellHotelButton;
    QPushButton *m_CancelBuyingButton;
    QPushButton *m_MortgageTakeOutButton;
    QPushButton *m_MortgagePayOffButton;
    QPushButton *m_KeepMortgageButton;
    QPushButton *m_StreetsButton;
    QPushButton *m_StationsButton;
    QPushButton *m_CompaniesButton;

    QGraphicsProxyWidget *m_BuyBuildingButtonProxy;
    QGraphicsProxyWidget *m_PlayerPropertiesProxy;
    QGraphicsProxyWidget *m_BuyHouseButtonProxy;
    QGraphicsProxyWidget *m_BuyHotelButtonProxy;
    QGraphicsProxyWidget *m_SellHouseButtonProxy;
    QGraphicsProxyWidget *m_SellHotelButtonProxy;
    QGraphicsProxyWidget *m_CancelBuyingButtonProxy;
    QGraphicsProxyWidget *m_MortgageTakeOutButtonProxy;
    QGraphicsProxyWidget *m_MortgagePayOffButtonProxy;
    QGraphicsProxyWidget *m_KeepMortgageButtonProxy;
    QGraphicsProxyWidget *m_StreetsButtonProxy;
    QGraphicsProxyWidget *m_StationsButtonProxy;
    QGraphicsProxyWidget *m_CompaniesButtonProxy;




};

#endif // PROPERTYVIEW_H
