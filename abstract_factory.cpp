#include <iostream>
#include <memory>
using namespace std;

// ---------------- Abstract Product ----------------
class Pizza {
public:
    virtual void Bake() = 0;
    virtual ~Pizza() = default;
};

// ---------------- Concrete Products ----------------
class IndiaPizza : public Pizza {
public:
    void Bake() {
        cout << "This is a generic India pizza baked." << endl;
    }
};

class AmericanPizza : public Pizza {
public:
    void Bake() {
        cout << "This is a generic American pizza baked." << endl;
    }
};

// ---------------- India Specific Pizzas ----------------
class IndiaCheesePizza : public IndiaPizza {
public:
    void Bake() {
        cout << "This India Cheese Pizza is being baked." << endl;
    }
};

class IndiaSpicyPizza : public IndiaPizza {
public:
    void Bake() {
        cout << "This India Spicy Pizza is being baked." << endl;
    }
};

// ---------------- American Specific Pizzas ----------------
class AmericanCheesePizza : public AmericanPizza {
public:
    void Bake() {
        cout << "This American Cheese Pizza is being baked." << endl;
    }
};

class AmericanSpicyPizza : public AmericanPizza {
public:
    void Bake() {
        cout << "This American Spicy Pizza is being baked." << endl;
    }
};

// ---------------- Abstract Factory ----------------
class PizzaFactory {
public:
    virtual Pizza* createCheesePizza() = 0;
    virtual Pizza* createSpicyPizza() = 0;
    virtual ~PizzaFactory() = default;
};

// ---------------- Concrete Factories ----------------
class IndiaPizzaFactory : public PizzaFactory {
public:
    Pizza* createCheesePizza() {
        return new IndiaCheesePizza();
    }
    Pizza* createSpicyPizza() {
        return new IndiaSpicyPizza();
    }
};

class AmericanPizzaFactory : public PizzaFactory {
public:
    Pizza* createCheesePizza() {
        return new AmericanCheesePizza();
    }
    Pizza* createSpicyPizza() {
        return new AmericanSpicyPizza();
    }
};

// ---------------- Client Code ----------------
int main() {
    unique_ptr<PizzaFactory> indiaFactory(new IndiaPizzaFactory());
    unique_ptr<Pizza> indiaCheese(indiaFactory->createCheesePizza());
    unique_ptr<Pizza> indiaSpicy(indiaFactory->createSpicyPizza());

    unique_ptr<PizzaFactory> americanFactory(new AmericanPizzaFactory());
    unique_ptr<Pizza> americanCheese(americanFactory->createCheesePizza());
    unique_ptr<Pizza> americanSpicy(americanFactory->createSpicyPizza());

    // Bake pizzas
    indiaCheese->Bake();
    indiaSpicy->Bake();
    americanCheese->Bake();
    americanSpicy->Bake();

    return 0;
}
