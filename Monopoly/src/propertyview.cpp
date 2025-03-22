#include "propertyview.h"

PropertyView::PropertyView(QGraphicsScene* Scene)
{
    //Buttons
    makeButtons(Scene);
    setPosition();
    setScale();
    setBeginState();

    //Property Table
    m_PlayerProperties = new QTableWidget{};

    //Init Size of table
    m_PlayerProperties->setFixedWidth(290);

    //Init Behavior of table
    m_PlayerProperties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_PlayerProperties->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_PlayerProperties->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_PlayerPropertiesProxy = Scene->addWidget(m_PlayerProperties);
    m_PlayerPropertiesProxy->setPos(1150, 300);
    m_PlayerPropertiesProxy->setScale(1.5);
    m_PlayerPropertiesProxy->hide();
}

void PropertyView::showStreetOptionButtons()
{
    m_BuyHotelButtonProxy->show();
    m_BuyHouseButtonProxy->show();
    m_SellHouseButton->show();
    m_SellHotelButton->show();
    m_CancelBuyingButtonProxy->show();
    m_MortgagePayOffButton->show();
    m_MortgageTakeOutButton->show();
    m_StreetsButton->show();
    m_StationsButton->show();
    m_CompaniesButton->show();
}

void PropertyView::hideStreetOptionButtons()
{
    m_BuyHotelButtonProxy->hide();
    m_BuyHouseButtonProxy->hide();
    m_SellHouseButton->hide();
    m_SellHotelButton->hide();
    m_CancelBuyingButtonProxy->hide();
    m_MortgagePayOffButton->hide();
    m_MortgageTakeOutButton->hide();
    m_StreetsButton->hide();
    m_StationsButton->hide();
    m_CompaniesButton->hide();
}


void PropertyView::showStationCompanyOptionButtons()
{

    m_CancelBuyingButton->show();
    m_MortgagePayOffButton->show();
    m_MortgageTakeOutButton->show();
    m_StreetsButton->show();
    m_StationsButton->show();
    m_CompaniesButton->show();

    m_MortgageTakeOutButtonProxy->setPos(1650, 350);
    m_MortgagePayOffButtonProxy->setPos(1650, 450);
}

void PropertyView::showInhertedMortgageOptions()
{
    m_MortgagePayOffButton->show();
    m_KeepMortgageButton->show();
    m_StreetsButton->hide();
    m_StationsButton->hide();
    m_CompaniesButton->hide();
    m_MortgageTakeOutButtonProxy->setPos(1650, 500);
    m_KeepMortgageButtonProxy->setPos(1650, 450);
}

void PropertyView::hideInhertedMortgageOptions()
{
    m_MortgagePayOffButton->hide();
    m_KeepMortgageButton->hide();
    m_StreetsButton->hide();
    m_StationsButton->hide();
    m_CompaniesButton->hide();
}

void PropertyView::hideStationCompanyOptionButtons()
{
    m_CancelBuyingButton->hide();
    m_MortgagePayOffButton->hide();
    m_MortgageTakeOutButton->hide();
    m_StreetsButton->hide();
    m_StationsButton->hide();
    m_CompaniesButton->hide();

    m_MortgageTakeOutButtonProxy->setPos(1650, 500);
    m_MortgagePayOffButtonProxy->setPos(1650, 550);
}


void PropertyView::disablePropertyOptionButtons()
{
    m_BuyHouseButtonProxy->setEnabled(false);
    m_BuyHotelButtonProxy->setEnabled(false);
    m_SellHouseButtonProxy->setEnabled(false);
    m_SellHotelButtonProxy->setEnabled(false);
    m_MortgagePayOffButtonProxy->setEnabled(false);
    m_MortgageTakeOutButton->setEnabled(false);
}


void PropertyView::enablePropertyOptionButton()
{
    m_BuyHouseButtonProxy->setEnabled(true);
    m_BuyHotelButtonProxy->setEnabled(true);
    m_SellHouseButtonProxy->setEnabled(true);
    m_SellHotelButtonProxy->setEnabled(true);
    m_MortgagePayOffButtonProxy->setEnabled(true);
    m_MortgageTakeOutButton->setEnabled(true);
}


void PropertyView::AdjustTableOptions()
{
    if (m_CurrentOption == OptionMode::STREET)
        setStreetOptions();
    else if (m_CurrentOption == OptionMode::STATION)
        setStationOptions();
    else if (m_CurrentOption == OptionMode::COMPANY)
        setCompanyOptions();
    else
        setInhertedOptions();
}

void PropertyView::setStreetColors(const Street::Color &StreetColor, const int &Index)
{
    switch (StreetColor){
    case Street::Color::BROWN:
        getBuildingTable()->item(Index, 0)->setBackground(QColor(165, 42, 42));
        break;
    case Street::Color::BLUE:
        getBuildingTable()->item(Index, 0)->setBackground(Qt::blue);
        break;
    case Street::Color::PINK:
        getBuildingTable()->item(Index, 0)->setBackground(QColor(255, 192, 203));
        break;
    case Street::Color::ORANGE:
        getBuildingTable()->item(Index, 0)->setBackground(QColor(255, 165, 0));
        break;
    case Street::Color::RED:
        getBuildingTable()->item(Index, 0)->setBackground(Qt::red);
        break;
    case Street::Color::YELLOW:
        getBuildingTable()->item(Index, 0)->setBackground(Qt::yellow);
        break;
    case Street::Color::GREEN:
        getBuildingTable()->item(Index, 0)->setBackground(Qt::green);
        break;
    default:
        getBuildingTable()->item(Index, 0)->setBackground(Qt::darkBlue);
    }
}

void PropertyView::setStreetOptions()
{
    m_BuyBuildingbutton->hide();
    m_PlayerProperties->show();

    m_PlayerProperties->setColumnCount(3);
    m_PlayerProperties->setColumnWidth(0, 150);
    m_PlayerProperties->setColumnWidth(1, 50);
    m_PlayerProperties->setColumnWidth(2, 50);

    m_StreetsButton->setEnabled(false);
    m_StationsButton->setEnabled(true);
    m_CompaniesButton->setEnabled(true);

    QTableWidgetItem * StreetName = new QTableWidgetItem{"Streets"};
    QTableWidgetItem * HouseAmount = new QTableWidgetItem{"Houses"};
    QTableWidgetItem * HotelAmount = new QTableWidgetItem{"Hotels"};

    m_PlayerProperties->setHorizontalHeaderItem(0, StreetName);
    m_PlayerProperties->setHorizontalHeaderItem(1, HouseAmount);
    m_PlayerProperties->setHorizontalHeaderItem(2, HotelAmount);

    hideStationCompanyOptionButtons();
    showStreetOptionButtons();
}

void PropertyView::setStationOptions()
{
    m_PlayerProperties->setColumnCount(1);
    m_PlayerProperties->setColumnWidth(0, 250);

    m_StreetsButton->setEnabled(true);
    m_StationsButton->setEnabled(false);
    m_CompaniesButton->setEnabled(true);

    QTableWidgetItem * StationName = new QTableWidgetItem{"Stations"};
    m_PlayerProperties->setHorizontalHeaderItem(0, StationName);

    hideStreetOptionButtons();
    showStationCompanyOptionButtons();
}


void PropertyView::setCompanyOptions()
{
    m_PlayerProperties->setColumnCount(1);
    m_PlayerProperties->setColumnWidth(0, 250);

    m_StreetsButton->setEnabled(true);
    m_StationsButton->setEnabled(true);
    m_CompaniesButton->setEnabled(false);

    QTableWidgetItem * CompanyName = new QTableWidgetItem{"Companies"};
    m_PlayerProperties->setHorizontalHeaderItem(0, CompanyName);

    hideStreetOptionButtons();
    showStationCompanyOptionButtons();
}

void PropertyView::setInhertedOptions()
{
    m_PlayerProperties->setColumnCount(1);
    m_PlayerProperties->setColumnWidth(0, 250);
    QTableWidgetItem * Name = new QTableWidgetItem{"Mortgage Properties"};
    m_PlayerProperties->setHorizontalHeaderItem(0, Name);

    hideStreetOptionButtons();
    showInhertedMortgageOptions();
}

void PropertyView::makeButtons(QGraphicsScene* Scene)
{
    m_BuyBuildingbutton = new QPushButton(QPushButton::tr("&Property Options"));
    m_BuyHouseButton = new QPushButton(QPushButton::tr("Purchase House"));
    m_BuyHotelButton = new QPushButton(QPushButton::tr("Purchase Hotel"));
    m_CancelBuyingButton = new QPushButton(QPushButton::tr("&Cancel"));
    m_MortgageTakeOutButton = new QPushButton(QPushButton::tr("&Take out mortgage"));
    m_MortgagePayOffButton = new QPushButton(QPushButton::tr("&Pay off mortgage"));
    m_KeepMortgageButton = new QPushButton(QPushButton::tr("&Keep mortgage"));
    m_SellHouseButton = new QPushButton(QPushButton::tr("Sell House"));
    m_SellHotelButton = new QPushButton(QPushButton::tr("Sell Hotel"));
    m_StreetsButton = new QPushButton(QPushButton::tr("Streets"));
    m_StationsButton = new QPushButton(QPushButton::tr("Stations"));
    m_CompaniesButton = new QPushButton(QPushButton::tr("Companies"));

    m_BuyBuildingButtonProxy = Scene->addWidget(m_BuyBuildingbutton);
    m_BuyHouseButtonProxy = Scene->addWidget(m_BuyHouseButton);
    m_BuyHotelButtonProxy = Scene->addWidget(m_BuyHotelButton);
    m_CancelBuyingButtonProxy = Scene->addWidget(m_CancelBuyingButton);
    m_MortgagePayOffButtonProxy= Scene->addWidget(m_MortgagePayOffButton);
    m_MortgageTakeOutButtonProxy = Scene->addWidget(m_MortgageTakeOutButton);
    m_KeepMortgageButtonProxy = Scene->addWidget(m_KeepMortgageButton);
    m_SellHouseButtonProxy = Scene->addWidget(m_SellHouseButton);
    m_SellHotelButtonProxy = Scene->addWidget(m_SellHotelButton);
    m_StreetsButtonProxy = Scene->addWidget(m_StreetsButton);
    m_StationsButtonProxy = Scene->addWidget(m_StationsButton);
    m_CompaniesButtonProxy = Scene->addWidget(m_CompaniesButton);
}

void PropertyView::setPosition()
{
    m_BuyHouseButtonProxy->setPos(1650, 300);
    m_BuyHotelButtonProxy->setPos(1650, 350);
    m_BuyBuildingButtonProxy->setPos(1105, 105);
    m_SellHouseButtonProxy->setPos(1650, 400);
    m_SellHotelButtonProxy->setPos(1650, 450);
    m_MortgageTakeOutButtonProxy->setPos(1650, 500);
    m_MortgagePayOffButtonProxy->setPos(1650, 550);
    m_KeepMortgageButtonProxy->setPos(1650,550);
    m_CancelBuyingButtonProxy->setPos(1650, 600);
    m_StreetsButtonProxy->setPos(1125, 600);
    m_StationsButtonProxy->setPos(1300, 600);
    m_CompaniesButtonProxy->setPos(1475, 600);
}

void PropertyView::setScale()
{
    const int SCALE = 2;
    m_BuyBuildingButtonProxy->setScale(SCALE);
    m_BuyHouseButtonProxy->setScale(SCALE);
    m_BuyHotelButtonProxy->setScale(SCALE);
    m_CancelBuyingButtonProxy->setScale(SCALE);
    m_MortgagePayOffButtonProxy->setScale(SCALE);
    m_MortgageTakeOutButtonProxy->setScale(SCALE);
    m_KeepMortgageButtonProxy->setScale(SCALE);
    m_SellHotelButtonProxy->setScale(SCALE);
    m_SellHouseButtonProxy->setScale(SCALE);
    m_StreetsButtonProxy->setScale(SCALE);
    m_StationsButtonProxy->setScale(SCALE);
    m_CompaniesButtonProxy->setScale(SCALE);
}

void PropertyView::setBeginState()
{
    m_BuyBuildingbutton->hide();
    m_BuyHouseButton->hide();
    m_BuyHotelButton->hide();
    m_CancelBuyingButton->hide();
    m_MortgagePayOffButton->hide();
    m_MortgageTakeOutButton->hide();
    m_KeepMortgageButton->hide();
    m_SellHouseButton->hide();
    m_SellHotelButton->hide();
    m_StreetsButton->hide();
    m_StationsButton->hide();
    m_CompaniesButton->hide();
}

QPushButton *PropertyView::getStreetsButton()
{
    return m_StreetsButton;
}

QPushButton *PropertyView::getStationsButton()
{
    return m_StationsButton;
}

QPushButton *PropertyView::getCompaniesButton()
{
    return m_CompaniesButton;
}

QPushButton *PropertyView::getBuyHotel()
{
    return m_BuyHotelButton;
}

QPushButton *PropertyView::getBuyHouse()
{
    return m_BuyHouseButton;
}

QPushButton *PropertyView::getSellHotel(){
    return m_SellHotelButton;
}

QPushButton *PropertyView::getSellHouse(){
    return m_SellHouseButton;
}

QPushButton *PropertyView::getMortgageTakeOutButton(){
    return m_MortgageTakeOutButton;
}

QPushButton *PropertyView::getMortgagePayOffButton(){
    return m_MortgagePayOffButton;
}

QPushButton *PropertyView::getKeepMortgageButton()
{
    return m_KeepMortgageButton;
}

QPushButton *PropertyView::getBuyBuilding()
{
    return m_BuyBuildingbutton;
}

QPushButton *PropertyView::getCancelButton()
{
    return m_CancelBuyingButton;
}

int PropertyView::getSelectedRow()
{
    int selectedRow = m_PlayerProperties->currentRow();
    return selectedRow;
}

QTableWidget *PropertyView::getBuildingTable()
{
    return m_PlayerProperties;
}

OptionMode PropertyView::getOptionMode(){
    return m_CurrentOption;
}

void PropertyView::setOptionMode(OptionMode newMode){
    m_CurrentOption = newMode;
}



