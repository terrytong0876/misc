/**
 * Your object will be instantiated and called as such:
 * ToyFactory* tf = new ToyFactory();
 * Toy* toy = tf->getToy(type);
 * toy->talk();
 */
class Toy {
public:
    virtual void talk() const = 0;
};

class Dog: public Toy {
public:
    void talk() const override {
        cout << "Wow" << endl;
    }
};

class Cat: public Toy {
public:
    void talk() const override {
        cout << "Meow" << endl;
    }
};

class ToyFactory {
public:
    /**
     * @param type a string
     * @return Get object of the type
     */
    Toy* getToy(const string& type) {
        if (type == "Dog") {
            return new Dog();
        } else if (type == "Cat") {
            return new Cat();
        }
        return nullptr;
    }
};
