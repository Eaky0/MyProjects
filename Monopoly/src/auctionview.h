//Author: Ieracitano Alessio
#ifndef AUCTIONVIEW_H
#define AUCTIONVIEW_H

#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QPushButton>


class AuctionView
{
public:
    AuctionView(QGraphicsScene* Scene);

    //Method:
    //hides all the auction buttons and text
    void hideAuctionView();

    //Method:
    //Shows all the auction buttons and text
    void showAuctionView();

    //Methods:
    //Retuns an address to an button
    QPushButton* getPlusOneButton() const;
    QPushButton* getPlusFiveButton() const;
    QPushButton* getPlusTenButton() const;
    QPushButton* getPlusTwentyButton() const;
    QPushButton* getPlusFiftyButton() const;
    QPushButton* getPlusHundredButton() const;
    QPushButton* getPlusFiveHundredButton() const;
    QPushButton* getConfirmButton() const;
    QPushButton* getPassButton() const;

    //Method:
    //Sets the highest bid amount and the highest bidder Text
    void setHighestBidder(const int &BidAmount, const int &PlayerIndex);

    //Mehtod:
    //Sets the current bidder text
    void setCurrentBidder(const int &PlayerIndex);

    //Method:
    //Sets the to display auction item
    void setAuctionItem(const int &TileNumber);

    //Method:
    //Returns the amount the bidder want to increase the highest bid by
    int getBid();

    //Method:
    //Increases m_Bid by the corresponding amount
    void increaseBidBy(const int &Amount);

    //Method
    //Resets m_Bid to zero
    void resetBid();
private:
    //Methods:
    //sets the bid amount to be displayed to 20
    void setStartBid();

    //Method:
    //Sets all the scales of the buttons and text
    void setScale() const;

    //Method:
    //Sets all the positions of the buttons and text
    void setPositions() const;

    //Button to comfirm
    QPushButton* m_ConfirmButton;
    QPushButton* m_PassButton;
    QGraphicsProxyWidget *m_ConfirmButtonProxy;
    QGraphicsProxyWidget *m_PassButtonProxy;

    //Buttons to increase bid amount
    QPushButton* m_BidPlusOne;
    QPushButton* m_BidPlusFive;
    QPushButton* m_BidPlusTen;
    QPushButton* m_BidPlusTwenty;
    QPushButton* m_BidPlusFifty;
    QPushButton* m_BidPlusHundred;
    QPushButton* m_BidPlusFiveHundred;

    QGraphicsProxyWidget *m_BidPlusOneProxy;
    QGraphicsProxyWidget *m_BidPlusFiveProxy;
    QGraphicsProxyWidget *m_BidPlusTenProxy;
    QGraphicsProxyWidget *m_BidPlusTwentyProxy;
    QGraphicsProxyWidget *m_BidPlusFiftyProxy;
    QGraphicsProxyWidget *m_BidPlusHundredProxy;
    QGraphicsProxyWidget *m_BidPlusFiveHundredProxy;

    //The text that needs to be dislayed
    QGraphicsTextItem *m_HighestBidText;
    QGraphicsTextItem *m_CurrentBidderText;
    QGraphicsTextItem *m_BidText;
    QGraphicsTextItem *m_AuctionItemText;
    int m_Bid;
};

#endif // AUCTIONVIEW_H
