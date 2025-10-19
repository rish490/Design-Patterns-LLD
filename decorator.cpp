#include <iostream>
using namespace std;

/*
Decorator Design Pattern Example: Pizza Shop

Use Case:
- Base pizza: Margerita, Farmhouse
- Toppings: Cheese, Paneer
- We want to dynamically add toppings without modifying existing pizza classes
- Instead of creating a class for every combination (Margerita + Cheese + Paneer, etc.), 
  we use decorators to "wrap" the base pizza and add extra behavior (description & price)

Key Concept:
- Decorator = Inheritance + Composition
  * Inheritance: decorator "is-a" Pizza, so it can replace BasePizza anywhere
  * Composition: decorator "has-a" Pizza, so it can wrap an existing pizza object
*/

// =========================
// 1️⃣ Base Pizza Interface
// =========================
class BasePizza {
public:
    virtual void description() = 0; // description of pizza
    virtual int price() = 0;        // price of pizza
    virtual ~BasePizza() {}
};

// =========================
// 2️⃣ Concrete Pizzas
// =========================
class Margerita : public BasePizza {
    int cost;
public:
    Margerita(int cost) { this->cost = cost; }

    void description() override {
        cout << "This is a Margerita Pizza";
    }

    int price() override { return cost; }
};

class Farmhouse : public BasePizza {
    int cost;
public:
    Farmhouse(int cost) { this->cost = cost; }

    void description() override {
        cout << "This is a Farmhouse Pizza";
    }

    int price() override { return cost; }
};

// =========================
// 3️⃣ Decorator Base Class
// =========================
class PizzaDecorator : public BasePizza {
protected:
    BasePizza* pizza; // "wrap" an existing pizza

public:
    PizzaDecorator(BasePizza* pizza) { this->pizza = pizza; }

    // By default, decorator delegates to the wrapped pizza
    void description() override { pizza->description(); }
    int price() override { return pizza->price(); }
};

// =========================
// 4️⃣ Concrete Decorators
// =========================

// Cheese Topping Decorator
class CheeseTopping : public PizzaDecorator {
    int cost; // extra cost of topping
public:
    CheeseTopping(BasePizza* pizza, int cost) : PizzaDecorator(pizza) { this->cost = cost; }

    void description() override {
        pizza->description(); // first call wrapped pizza description
        cout << " with added Cheese Topping"; // then add extra behavior
    }

    int price() override { return pizza->price() + cost; }
};

// Paneer Topping Decorator
class PaneerTopping : public PizzaDecorator {
    int cost; // extra cost of topping
public:
    PaneerTopping(BasePizza* pizza, int cost) : PizzaDecorator(pizza) { this->cost = cost; }

    void description() override {
        pizza->description(); // first call wrapped pizza description
        cout << " with added Paneer Topping"; // then add extra behavior
    }

    int price() override { return pizza->price() + cost; }
};

// =========================
// 5️⃣ Usage / Test
// =========================
int main() {
    // Create base pizza
    BasePizza* pizza = new Margerita(150);
    pizza->description();
    cout << " -> Price: " << pizza->price() << endl;

    // Add Cheese topping dynamically
    pizza = new CheeseTopping(pizza, 10);
    pizza->description();
    cout << " -> Price: " << pizza->price() << endl;

    // Add Paneer topping dynamically
    pizza = new PaneerTopping(pizza, 20);
    pizza->description();
    cout << " -> Price: " << pizza->price() << endl;

    // Cleanup (important for memory management)
    delete pizza;

    return 0;
}

/*
Key Takeaways:

1. Dynamic Behavior:
   - We can add multiple toppings at runtime without creating new classes for every combination.

2. Open/Closed Principle:
   - BasePizza classes remain unchanged (open for extension, closed for modification)

3. Polymorphism:
   - Decorators can be treated as BasePizza objects anywhere in the code.

4. Composition + Inheritance:
   - Composition (has-a): decorator contains a pizza object
   - Inheritance (is-a): decorator is-a pizza, so it can be used wherever a pizza is expected

5. Real-world Use Cases:
   - GUI components:
     * Adding scrollbars, borders, or theming dynamically to windows/widgets
   - File I/O:
     * Adding compression, encryption, or buffering to input/output streams
   - Logging:
     * Adding timestamp, log level, or file/console output decorators to logger objects
   - Notifications:
     * Wrapping notification system to add Email, SMS, or Push without modifying core logic
   - Middleware in web frameworks:
     * Adding authentication, caching, or logging layers dynamically to HTTP request handlers
   - Any situation where:
     * You want to add responsibilities **dynamically at runtime**
     * You want to avoid an explosion of subclasses for every combination of features
*/
