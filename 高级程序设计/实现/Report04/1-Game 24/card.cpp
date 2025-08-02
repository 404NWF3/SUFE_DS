/*
 * File: card.cpp
 * --------------
 * This file implements the card.h interface.
 */
#include <iostream>
#include <string>
#include "card.h"
#include "error.h"
#include "strlib.h"

/* Constants */

extern const int ACE = 1;
extern const int JACK = 11;
extern const int QUEEN = 12;
extern const int KING = 13;

const double MINMUM = 0.000001;

/* Implementation of the Suit type */

Card::Card() {
   /* Empty */
}

Card::Card(std::string name) {  
   createdDone = true;
   if (name.length() < 2) {
       std::cerr << "Invalid card name!" << std::endl; createdDone = false;}
   unsigned int suitIndex = 1;
   switch (name[0]) {
    case 'A': case 'a':
      cardRank = 1;
      break;
    case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      cardRank = name[0] - '0';
      break;
    case '1':
      if (name[1] != '0') {
          std::cerr << "Invalid card name!" << std::endl; createdDone = false;}
      cardRank = 10;
      suitIndex = 2;
      break;
    case 'J': case 'j':
      cardRank = 11;
      break;
    case 'Q': case 'q':
      cardRank = 12;
      break;
    case 'K': case 'k':
      cardRank = 13;
      break;
   default:
      std::cerr << "Illegal card name!" << std::endl; createdDone = false;
   }
   expressionString = name;

   if (name.length() != suitIndex + 1) {
       std::cerr << "Illegal card name!" << std::endl; createdDone = false;}
   switch (name[suitIndex]) {
   case 'C': case 'c':
       cardSuit = CLUBS;
       break;
   case 'D': case 'd':
       cardSuit = DIAMONDS;
       break;
   case 'H': case 'h':
       cardSuit = HEARTS;
       break;
   case 'S': case 's':
       cardSuit = SPADES;
       break;
   default:
       std::cerr << "Illegal card name!" << std::endl; createdDone = false;
   }
}

Card::Card(double rank, Suit suit) {
   createdDone = true;
   cardRank = rank;
   cardSuit = suit;
   expressionString = doubleToString(cardRank);
}

Card::Card(double rank, std::string exprStr){
    createdDone = true;
    cardRank = rank;
    expressionString = exprStr;
}

std::string Card::toString() const{
   std::string str = "???";
   switch (static_cast<int>(cardRank)) {
    case ACE:   str = "A"; break;
    case JACK:  str = "J"; break;
    case QUEEN: str = "Q"; break;
    case KING:  str = "K"; break;
    default:    str = integerToString(static_cast<int>(cardRank)); break;
   }
   switch (cardSuit) {
    case CLUBS:    return str + "C";
    case DIAMONDS: return str + "D";
    case HEARTS:   return str + "H";
    case SPADES:   return str + "S";
    default:       return "???";
   }
}

bool Card::fail() const{
    return !createdDone;
}

double Card::getRank() const{
   return cardRank;
}

Suit Card::getSuit() const{
   return cardSuit;
}

std::string Card::mergeString(const std::string& s1, const std::string& s2,
                              char op) const{
    // std::string  str = s1 + " " + op + " " + s2;
    // return  op == '+' || op == '-' ? "(" + str + ")" : str;
    return  " ( " + s1 + " " + op + " " + s2 + " ) ";
}

const Card Card::calculateCard(const Card& c,char op) const{
    double result = 0;
    switch (op){
    case '+': result = this->cardRank + c.cardRank;
        break;
    case '-': result = this->cardRank - c.cardRank;
        break;
    case '*': result = this->cardRank * c.cardRank;
        break;
    case '/': result = this->cardRank / c.cardRank;
        break;
    }
    return  Card(result, mergeString(this->expressionString, c.expressionString,op));
}


std::string Card::toExpressionString() const{
    return expressionString;
}

const Card Card::operator+(const Card& c) const{
    return calculateCard(c,'+');
}

const Card Card::operator-(const Card& c) const{
    return calculateCard(c,'-');
}


const Card Card::operator*(const Card& c) const{
    return calculateCard(c,'*');
}

const Card Card::operator/(const Card& c) const{
    return calculateCard(c,'/');
}

bool Card::operator>=(const Card& c) const{
    return this->cardRank >= c.cardRank;
}

bool Card::operator <(const Card& c) const{
    if (this->cardRank != c.cardRank)
        return this->cardRank < c.cardRank;
    if (this->expressionString != c.toExpressionString())
        return this->expressionString < c.toExpressionString();
    return this->cardSuit < c.cardSuit;
}

bool Card::operator!=(const Card& c) const{
    return !(fabs(this->cardRank - c.cardRank) < MINMUM);
}

bool Card::operator!=(double num) const{
    return !(fabs(this->cardRank - num) < MINMUM);
}

bool Card::operator==(double num) const{
    return fabs(this->cardRank - num) < MINMUM;
}

std::ostream & operator<<(std::ostream & os, Card card) {
   return os << card.toString();
}

Suit operator++(Suit & suit, int) {
   Suit old = suit;
   suit = Suit(suit + 1);
   return old;
}

