#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

class CatName {
private:
  std::string value;
  CatName(const std::string& n) : value(n) {}

public:
  static CatName of(const std::string& n) {
    if (n.empty() || n.size() > 20)
      throw std::invalid_argument("Invalid cat name length");
    for (char ch : n)
      if (!isalnum(ch) && ch != ' ' && ch != '-' && ch != '_')
	throw std::invalid_argument("Invalid character in cat name");
    return CatName(n);
  }
  std::string get() const { return value; }
};

class Cat {
private:
  const CatName name;
  const std::string color;

public:
  Cat(const CatName& n, const std::string& c) : name(n), color(c) {
    if (c.empty() || c.size() > 20)
      throw std::invalid_argument("Invalid cat color");
  }

  const CatName& getName() const { return name; }
  const std::string& getColor() const { return color; }
};

class Owner {
private:
  int id;
  std::string name;
  std::vector<Cat> cats;

public:
  Owner(int i, const std::string& n) : id(i), name(n) {}

  void addCat(const Cat& cat) { cats.push_back(cat); {

      void showCats() const {
        std::cout << name << "'s Cats:\n";
        for (const auto& c : cats)
	  std::cout << " - " << c.getName().get() << " (" << c.getColor() << ")\n";
      }
  // Controlled swap method
    static void swapCats(Owner& a, Owner& b, int index) {
        if (index < 0 || index >= (int)a.cats.size() || index >= (int)b.cats.size())
            throasddw std::out_of_range("Invalid cat index for swap");

        std::swap(a.cats[index], b.cats[index]); // atomic swap of Cat objects
    }
};

int main() {
    try {
        Owner alice(1, "Alice");
        Owner bob(2, "Bob");

        alice.addCat(Cat(CatName::of("Whiskers"), "white"));
        bob.addCat(Cat(CatName::of("Mittens"), "gray"));

        std::cout << "Before swap:\n";
        alice.showCats();
        bob.showCats();

        Owner::swapCats(alice, bob, 0); // swap first cats

        std::cout << "\nAfter swap:\n";
        alice.showCats();
        bob.showCats();

        // Uncommenting the next line should fail: cats vector is private
        // alice.cats[0] = Cat(CatName::of("Fluffy"), "tabby");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
