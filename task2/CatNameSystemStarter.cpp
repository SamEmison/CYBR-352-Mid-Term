//Sam Emison
//10/17/2025
//Code imported from demo files

#include <iostream>
#include <string>
#include <vector>

class Cat {
public:
    std::string name;
    std::string color;

    Cat(std::string n, std::string c) : name(n), color(c) {}
};

class Owner {
public:
    std::string name;
    std::vector<Cat> cats;

    Owner(std::string n) : name(n) {}

    void addCat(const Cat& cat) {
        cats.push_back(cat);
    }

    void showCats() const {
        std::cout << name << "'s Cats:\n";
        for (const auto& c : cats)
            std::cout << " - " << c.name << " (" << c.color << ")\n";
    }
};

int main() {
    Owner alice("Alice");
    alice.addCat(Cat("Whiskers", "white"));
    alice.addCat(Cat("Mittens", "gray"));
    alice.showCats();
    return 0;
}
