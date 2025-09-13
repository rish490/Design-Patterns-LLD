typedef long long ll;
class ISubscriber{
    public:
    virtual void notify(string msg)=0;
};
class User: public ISubscriber{
  int id;
  string name;
  public:
  User(int id){
      this->id=id;
  }
  void notify(string msg){
      cout<<"This user with id "<<id<<" has been notified"<<endl;
  }
};

class Group {
    vector<ISubscriber*>users;
    string name;
    public:
    Group(string name){
        this->name=name;
    }
    void notify(string msg){
        for(int i=0;i<users.size();i++){
            users[i]->notify(msg);
        }
    }
    void subscribe(ISubscriber* user){
        users.push_back(user);
    }
    void unsubscribe(ISubscriber* user){
        vector<ISubscriber*>temp;
        for(int i=0;i<users.size();i++){
            if(users[i]==user){
                
            }
            else{
                temp.push_back(users[i]);
            }
        }
        users=temp;
    }
}
int main()
{
    Group* group=new Group("temp");
    User* user1=new User(1);
    User* user2=new User(2);
    User* user3=new User(3);
    group->subscribe(user1);
    group->subscribe(user2);
    group->subscribe(user3);
    
    group->notify();
    group->unsubscribe(user2);
    
    group->notify();
    
    

    return 0;
}
