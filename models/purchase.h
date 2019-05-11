#ifndef PURCHASE_H
#define PURCHASE_H

class Purchase {
   public:
    Purchase(int _userId, int _filmId, double _price, double _rate);
    double getMoney();

   private:
    int userId;
    int filmId;
    double price;
    double rate;
    bool hasGotten;
};

#endif