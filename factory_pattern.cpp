class Vehicle{
    public:
    
  virtual void drive()=0;
  virtual ~Vehicle() = default;
};

class Car : public Vehicle{
    public:
  void drive(){
      cout<<"Car is driving"<<endl;
  }  
};
class Bus : public Vehicle{
    public:
  void drive(){
      cout<<"Bus is driving"<<endl;
  }  
};

class VehicleFactory{
    public:
  static Vehicle* createVehicle(string vehicleType){
      Vehicle* vehicle;
      
      if(vehicleType=="Car"){
          vehicle=new Car();
      }
      else if(vehicleType=="Bus"){
          vehicle=new Bus();
      }
      return vehicle;
  }  
};
int main()
{
    string vtype;
    cin>>vtype;
    Vehicle* vehicle=VehicleFactory::createVehicle(vtype);
    vehicle->drive();
    return 0;
}
