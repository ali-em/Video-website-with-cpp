#ifndef PURCHASE_H
#define PURCHASE_H

class Purchase {
   public:
    Purchase(double _price, double _rate);
    double getMoney();

   private:
    double price;
    double rate;
    bool hasGotten;
};

#endif