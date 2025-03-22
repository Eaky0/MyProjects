#include "payment.h"

Payment::Payment(QJsonValue CardInfo, CardType CardSort, int CardNumber) : Card{CardInfo, CardSort, CardNumber}
{


    if (CardSort == CardType::CHANCE){
        //"Make general repairs on all your property.\nFor each house pay £25.\nFor each hotel pay £100."
        if (CardNumber == 10){
            m_Money.append(CardInfo["payment"][0].toInt());
            m_Money.append(CardInfo["payment"][1].toInt());
        }
        else
            m_Money.append(CardInfo["payment"].toInt());

        //Sets the payment type according to whether the payment card says to collect or pay money.
        if (CardInfo["type"].toString() == "Collect")
            m_PaymentType = TransactionType::Recieve;
        else
            m_PaymentType = TransactionType::Pay;
    }
    //else CardSort = CardType::COMMUNITYCHEST
    else{
        //"You are assessed for street repairs.\n£40 per house.\n£115 per hotel."
        if (CardNumber == 13){
            m_Money.append(CardInfo["payment"][0].toInt());
            m_Money.append(CardInfo["payment"][1].toInt());
        }
        else
            m_Money.append(CardInfo["payment"].toInt());


        //Sets the payment type according to whether the payment card says to collect or pay money.
        if (CardInfo["type"].toString() == "Collect")
            m_PaymentType = TransactionType::Recieve;
        else
            m_PaymentType = TransactionType::Pay;
    }
}


QList<int> Payment::getPayment() {
    return m_Money;
}

TransactionType Payment::getTypeOfPayment(){
    return m_PaymentType;
}
