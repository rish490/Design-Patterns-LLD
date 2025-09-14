#include <bits/stdc++.h>
#include<mutex>
using namespace std;

class Singleton{
Singleton(){
    cout<<"private constructor created"<<endl;
}
Singleton(Singleton* c){
    cout<<"copy constructor private"<<endl;
}
static Singleton* instance;
static std::mutex mtx;
public:

static Singleton* getInstance(){
    std::lock_guard<std::mutex> lock(mtx);
    if(instance==nullptr){
        instance=new Singleton();
        cout<<"new instance created"<<endl;
    }
    return instance;
}
};

Singleton* Singleton::instance=nullptr;
std::mutex Singleton::mtx;
int main()
{
    Singleton* c=Singleton::getInstance();
    Singleton* d=Singleton::getInstance();
}
