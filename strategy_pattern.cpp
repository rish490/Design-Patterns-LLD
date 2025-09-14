#include <bits/stdc++.h>
#include<mutex>
using namespace std;

class PaymentStrategy{
  public:
  virtual void pay()=0;
};

class CreditCardPayment : public PaymentStrategy{
  public:
  void pay(){
      cout<<"paying this thorugh credit card"<<endl;
  }
    
};

class UpiPayment : public PaymentStrategy{
    public:
    void pay(){
        cout<<"paying thorugh upi"<<endl;
    }
};

class Checkout{
  PaymentStrategy* strategy;
  public:
  void setPaymentStrategy(PaymentStrategy* strategy){
      this->strategy=strategy;
  }
  
  void proceedToPay(){
      strategy->pay();
  }
};
int main()
{
    PaymentStrategy* strategy=new UpiPayment();
    Checkout* c=new Checkout();
    c->setPaymentStrategy(strategy);
    c->proceedToPay();
    
}
