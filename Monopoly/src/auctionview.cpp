
#include "auctionview.h"

AuctionView::AuctionView(QGraphicsScene* Scene) : m_Bid{ 0 }
{
    m_BidPlusOne = new QPushButton(QPushButton::tr("&+1"));
    m_BidPlusFive = new QPushButton(QPushButton::tr("&+5"));
    m_BidPlusTen = new QPushButton(QPushButton::tr("&+10"));
    m_BidPlusTwenty = new QPushButton(QPushButton::tr("&+20"));
    m_BidPlusFifty = new QPushButton(QPushButton::tr("&+50"));
    m_BidPlusHundred = new QPushButton(QPushButton::tr("&+100"));
    m_BidPlusFiveHundred = new QPushButton(QPushButton::tr("&+500"));
    m_ConfirmButton = new QPushButton(QPushButton::tr("&Confirm"));
    m_PassButton = new QPushButton(QPushButton::tr("&Pass"));

    m_HighestBidText = Scene->addText(QGraphicsTextItem::tr("Highest bid: 10"));
    m_CurrentBidderText = Scene->addText(QGraphicsTextItem::tr("Current Bidder: Player 1"));
    m_BidText = Scene->addText(QGraphicsTextItem::tr("Increase highest bid by: 0"));
    m_AuctionItemText = Scene->addText(QGraphicsTextItem::tr("Auction Item"));

    m_BidPlusOneProxy = Scene->addWidget(m_BidPlusOne);
    m_BidPlusFiveProxy = Scene->addWidget(m_BidPlusFive);
    m_BidPlusTenProxy = Scene->addWidget(m_BidPlusTen);
    m_BidPlusTwentyProxy = Scene->addWidget(m_BidPlusTwenty);
    m_BidPlusFiftyProxy = Scene->addWidget(m_BidPlusFifty);
    m_BidPlusHundredProxy = Scene->addWidget(m_BidPlusHundred);
    m_BidPlusFiveHundredProxy = Scene->addWidget(m_BidPlusFiveHundred);
    m_ConfirmButtonProxy = Scene->addWidget(m_ConfirmButton);
    m_PassButtonProxy = Scene->addWidget(m_PassButton);

    setScale();
    setPositions();
    hideAuctionView();
}

void AuctionView::hideAuctionView()
{
    //Buttons:
    m_BidPlusOneProxy->hide();
    m_BidPlusFiveProxy->hide();
    m_BidPlusTenProxy->hide();
    m_BidPlusTwentyProxy->hide();
    m_BidPlusFiftyProxy->hide();
    m_BidPlusHundredProxy->hide();
    m_BidPlusFiveHundredProxy->hide();
    m_ConfirmButtonProxy->hide();
    m_PassButtonProxy->hide();

    setStartBid();  //Reset the display text

    //Text:
    m_HighestBidText->hide();
    m_CurrentBidderText->hide();
    m_AuctionItemText->hide();
    m_BidText->hide();
}

void AuctionView::showAuctionView()
{
    //Buttons:
    m_BidPlusOneProxy->show();
    m_BidPlusFiveProxy->show();
    m_BidPlusTenProxy->show();
    m_BidPlusTwentyProxy->show();
    m_BidPlusFiftyProxy->show();
    m_BidPlusHundredProxy->show();
    m_BidPlusFiveHundredProxy->show();
    m_ConfirmButtonProxy->show();
    m_PassButtonProxy->show();

    //Text:
    m_HighestBidText->show();
    m_CurrentBidderText->show();
    m_AuctionItemText->show();
    m_BidText->show();
}

QPushButton *AuctionView::getPlusOneButton() const
{
    return m_BidPlusOne;
}

QPushButton* AuctionView::getPlusFiveButton() const
{
    return m_BidPlusFive;
}

QPushButton* AuctionView::getPlusTenButton() const
{
    return m_BidPlusTen;
}

QPushButton* AuctionView::getPlusTwentyButton() const
{
    return m_BidPlusTwenty;
}

QPushButton* AuctionView::getPlusFiftyButton() const
{
    return m_BidPlusFifty;
}

QPushButton* AuctionView::getPlusHundredButton() const
{
    return m_BidPlusHundred;
}

QPushButton* AuctionView::getPlusFiveHundredButton() const
{
    return m_BidPlusFiveHundred;
}

QPushButton *AuctionView::getConfirmButton() const
{
    return m_ConfirmButton;
}

QPushButton *AuctionView::getPassButton() const
{
    return m_PassButton;
}

void AuctionView::setHighestBidder(const int &BidAmount, const int &PlayerIndex)
{
    int PlayerNumber = PlayerIndex + 1;
    QString Bid = "Highest Bid: " + QString::number(BidAmount) + "   Highest Bidder " + QString::number(PlayerNumber);
    m_HighestBidText->setPlainText(Bid);    //We update the display text
}

void AuctionView::setCurrentBidder(const int &PlayerIndex)
{
    int PlayerNumber = PlayerIndex + 1;
    QString CurrentBidder = "Current Bidder: Player " + QString::number(PlayerNumber);
    m_CurrentBidderText->setPlainText(CurrentBidder); //We update the display text
}

void AuctionView::setAuctionItem(const int &TileNumber)
{
    QString AuctionItem = "Auction Item: Tile " + QString::number(TileNumber + 1);
    m_AuctionItemText->setPlainText(AuctionItem); //We update the display text
}

int AuctionView::getBid()
{
    return m_Bid;
}

void AuctionView::increaseBidBy(const int &Amount)
{
    m_Bid += Amount;
    QString Text = "Increase highest bid by: " + QString::number(m_Bid);    //We update the display text
    m_BidText->setPlainText(Text);
}

void AuctionView::resetBid()
{
    const int RESET = 0;
    m_Bid = RESET;

    QString Text = "Increase highest bid by: " + QString::number(m_Bid); //We update the display text
    m_BidText->setPlainText(Text);
}

void AuctionView::setStartBid()
{
    QString Bid = "Highest Bid: 10";
    m_HighestBidText->setPlainText(Bid); //We set test that needs to be displayed at the beginning of an auction
}

void AuctionView::setPositions() const
{
    m_BidPlusOneProxy->setPos(1255,150);
    m_BidPlusFiveProxy->setPos(1255,200);
    m_BidPlusTenProxy->setPos(1255,250);
    m_BidPlusTwentyProxy->setPos(1255,300);
    m_BidPlusFiftyProxy->setPos(1255,350);
    m_BidPlusHundredProxy->setPos(1255,400);
    m_BidPlusFiveHundredProxy->setPos(1255,450);
    m_ConfirmButtonProxy->setPos(1255, 520);
    m_PassButtonProxy->setPos(1105, 520);

    m_HighestBidText->setPos(1105, -15);
    m_CurrentBidderText->setPos(1105, 20);
    m_AuctionItemText->setPos(1105, -50);
    m_BidText->setPos(1105, 600);
}

void AuctionView::setScale() const
{
    const int SCALE = 2;
    const int TEXTSCALE = 3;

    m_BidPlusOneProxy->setScale(SCALE);
    m_BidPlusFiveProxy->setScale(SCALE);
    m_BidPlusTenProxy->setScale(SCALE);
    m_BidPlusTwentyProxy->setScale(SCALE);
    m_BidPlusFiftyProxy->setScale(SCALE);
    m_BidPlusHundredProxy->setScale(SCALE);
    m_BidPlusFiveHundredProxy->setScale(SCALE);
    m_ConfirmButtonProxy->setScale(SCALE);
    m_PassButtonProxy->setScale(SCALE);
    m_HighestBidText->setScale(TEXTSCALE);
    m_CurrentBidderText->setScale(TEXTSCALE);
    m_AuctionItemText->setScale(TEXTSCALE);
    m_BidText->setScale(TEXTSCALE);
}

