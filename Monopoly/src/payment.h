//Kumas Atakan
#ifndef PAYMENT_H
#define PAYMENT_H

#include <card.h>

class Payment : public Card
{
public:
    //Constructor:
    Payment(QJsonValue CardInfo, CardType CardSort, int CardNumber);


    void DynamicFunc(){}; //Empty function Used for making class Card polymorphic and effective for dynamic casting;

    //Method:
    //Returns the payment type of the payment Card. This could either be PAY or RECEIVE.
    TransactionType getTypeOfPayment();

    //Method:
    //Returns the payment value of the payment Card.
    QList<int> getPayment();

private:

    //Members:
    QList<int> m_Money;
    TransactionType m_PaymentType;

};

#endif // PAYMENT_H
