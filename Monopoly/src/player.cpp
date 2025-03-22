#include "player.h"

Player::Player(const int i) : m_Figure{findFigure(i)}{}

int Player::getBalance()
{
    return m_Balance;
}

bool Player::getPlayerStatus()
{
    return m_InJail;
}

bool Player::didPlayerPass()
{
    return m_Passed;
}

void Player::setPlayerPassed(bool Status)
{
    m_Passed = Status;
}

void Player::setPlayerBankrupt()
{
    m_IsBankrupt = true;
}

bool Player::isPlayerBankrupt()
{
    return m_IsBankrupt;
}

void Player::moneyTransaction(int Amount, TransactionType ToPay)
{
    if (ToPay == TransactionType::Pay)
        m_Balance -= Amount;
    else
        m_Balance += Amount;
}

Figure Player::getFigure()
{
    return m_Figure;
}

void Player::playerInJail(bool status)
{
    if (status == true)
        m_InJail = true;
    else
        m_InJail = false;
}

int Player::getRoundsInJail()
{
    return m_RoundsInJail;
}

void Player::addCard(Card *GetOutCard)
{
    m_Cards.append(GetOutCard);
}

Card *Player::removeCard()
{
    if (m_Cards.size() > 0){
        Card* GetOutOfJailCard = m_Cards.back();
        m_Cards.removeLast();
        return GetOutOfJailCard;
    }
    else
        return nullptr;
}

bool Player::hasJailCard()
{
    int AmountCards = (int) m_Cards.size();
    return (AmountCards > 0);
}

void Player::setRoundsInJail(int Amount)
{
    m_RoundsInJail = Amount;
}

Figure Player::findFigure(const int i)
{
    switch (i){
    case 0:
        return Figure::CAR;
    case 1:
        return Figure::HAT;
    case 2:
        return Figure::WHEELBARROW;
    case 3:
        return Figure::BOOT;
    case 4:
        return Figure::SHIP;
    default:
        return Figure::CANNON;
    }
}

QList<Card *> Player::getCards()
{
    return m_Cards;
}


