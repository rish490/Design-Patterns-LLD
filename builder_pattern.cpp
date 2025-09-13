#include <bits/stdc++.h>
using namespace std;

class Car{
  protected:
  string brand;
  string engine;
  string gear;
  bool roof;
  int tyrecount;
  
  
  public:
  Car(string brand, string engine, string gear, bool roof, int tyrecount) {
    this->brand = brand;
    this->engine = engine;
    this->gear = gear;
    this->roof = roof;
    this->tyrecount = tyrecount;
}
  void showSpecs(){
      cout<<"Engine "<<engine<<endl;
      cout<<"Brand "<<brand<<endl;
      cout<<"Gear "<<gear<<endl;
      cout<<"Roof "<<roof<<endl;
      cout<<"Tyrecount "<<tyrecount<<endl;
  }
};

class VehicleBuilder{
    protected:
    virtual VehicleBuilder& setEngine(string s)=0;  //this ensures we return reference and keep working on the same copy 
    virtual VehicleBuilder& setBrand(string b)=0; //we are initialising statically here no new keyword used 
    virtual VehicleBuilder& setGear(string g)=0;
    virtual VehicleBuilder& hasRoof(bool r)=0;
    virtual VehicleBuilder& setTyreCount(int r)=0;
};

class CarBuilder : public VehicleBuilder{
  string brand;
  string engine;
  string gear;
  bool roof;
  int tyrecount;
  public:
  CarBuilder& setEngine(string s){
      engine=s;
      return *this;
  }
  CarBuilder& setBrand(string b){
      brand=b;
      return *this; //returns reference to current variable 
  }
  CarBuilder& setGear(string g){
      gear=g;
      return *this;
  }
  CarBuilder& hasRoof(bool r){
      roof=r;
      return *this;
  }
  CarBuilder& setTyreCount(int r){
      tyrecount=r;
      return *this;
  }
  Car build(){
      return Car(brand,engine,gear,roof,tyrecount);
  }
};

int main()
{
    Car car=CarBuilder().setEngine("eng").setBrand("bmw").setGear("gg").hasRoof(false).setTyreCount(4).build();
    car.showSpecs();
    return 0;
}
