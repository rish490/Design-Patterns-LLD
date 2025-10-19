#include <iostream>
#include <memory>
using namespace std;

/*
==============================================================
🧩 Design Pattern: Chain of Responsibility (CoR)
==============================================================

📘 Definition:
---------------
The Chain of Responsibility pattern lets you pass a request along 
a chain of handlers. Each handler decides either to process the 
request or to pass it to the next handler in the chain.

This pattern helps decouple the sender of a request from its receivers, 
allowing multiple objects a chance to handle that request.

--------------------------------------------------------------
💼 Real-world Example:
--------------------------------------------------------------
Imagine an expense approval workflow:
- Manager can approve expenses up to $1,000
- Director can approve up to $10,000
- CEO approves anything above that

Each approver either handles the request or forwards it up the chain.

--------------------------------------------------------------
❌ Without Chain of Responsibility:
--------------------------------------------------------------
We’d have a long if-else ladder like this:

if (amount <= 1000)
   handleByManager();
else if (amount <= 10000)
   handleByDirector();
else
   handleByCEO();

Problems:
- Hard to extend (add new approver => modify old code)
- Violates Open/Closed Principle
- Not flexible or testable
- All logic tightly coupled

--------------------------------------------------------------
✅ With Chain of Responsibility:
--------------------------------------------------------------
Each approver is an independent handler. 
You can easily add, remove, or reorder them without breaking code.

--------------------------------------------------------------
🧠 Use Cases:
--------------------------------------------------------------
- Approval systems (expense, leave, etc.)
- Logging frameworks (INFO → DEBUG → ERROR)
- Middleware request handling (e.g., HTTP filters)
- Access control and validation pipelines

--------------------------------------------------------------
🏗️ Structure:
--------------------------------------------------------------
Handler (Abstract class):
    + setNext(Handler)
    + handleRequest(request)

ConcreteHandler:
    + Handles the request if possible
    + Else passes it to the next handler

--------------------------------------------------------------
🧩 Example Implementation: Expense Approval System
--------------------------------------------------------------
*/

// -------------------- Abstract Handler ----------------------
class Approver {
protected:
    shared_ptr<Approver> nextApprover;

public:
    void setNext(shared_ptr<Approver> next) {
        nextApprover = next;
    }

    virtual void approve(double amount) = 0;
    virtual ~Approver() = default;
};

// -------------------- Concrete Handlers ---------------------
class Manager : public Approver {
public:
    void approve(double amount) override {
        if (amount <= 1000)
            cout << "✅ Manager approved expense: $" << amount << endl;
        else if (nextApprover)
            nextApprover->approve(amount);
    }
};

class Director : public Approver {
public:
    void approve(double amount) override {
        if (amount <= 10000)
            cout << "✅ Director approved expense: $" << amount << endl;
        else if (nextApprover)
            nextApprover->approve(amount);
    }
};

class CEO : public Approver {
public:
    void approve(double amount) override {
        cout << "✅ CEO approved expense: $" << amount << endl;
    }
};

// -------------------- Client Code ----------------------------
int main() {
    // Create the chain: Manager → Director → CEO
    auto manager = make_shared<Manager>();
    auto director = make_shared<Director>();
    auto ceo = make_shared<CEO>();

    manager->setNext(director);
    director->setNext(ceo);

    // Test requests of different amounts
    double expenses[] = {500, 3000, 20000};

    for (double amount : expenses) {
        cout << "\nRequesting approval for $" << amount << endl;
        manager->approve(amount);
    }

    return 0;
}

/*
--------------------------------------------------------------
🧾 Output:
--------------------------------------------------------------
Requesting approval for $500
✅ Manager approved expense: $500

Requesting approval for $3000
✅ Director approved expense: $3000

Requesting approval for $20000
✅ CEO approved expense: $20000

--------------------------------------------------------------
🚀 Benefits:
--------------------------------------------------------------
✅ Decouples sender and receiver
✅ Easy to extend new handlers
✅ Follows Open/Closed Principle
✅ Flexible and maintainable

--------------------------------------------------------------
⚠️ When NOT to Use:
--------------------------------------------------------------
- When the chain is too long (can reduce performance)
- When you always know exactly which handler to call
--------------------------------------------------------------
*/
