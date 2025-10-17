//Sam Emison
//10/17/2025

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <memory>

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

// Secret Class (NEW)
class Secret {
private:
  std::string data;
  bool read;

public:
  Secret(const std::string& d) : data(d), read(false) {}

  std::string readOnce() {
    if (read)
      throw std::runtime_error("Error: Secret data already accessed!");
    read = true;
    return data;
  }
};

class Owner {
private:
  int id;
  std::string name;
  std::vector<std::shared_ptr<Cat>> cats;
  Secret password; // sensitive data

public:
  Owner(int i, const std::string& n, const std::string& pw)
      : id(i), name(n), password(pw) {}

  void addCat(const Cat& cat) {
    cats.push_back(std::make_shared<Cat>(cat));
  }

  void showCats() const {
    std::cout << name << "'s Cats (ID: " << id << "):\n";
    for (const auto& c : cats)
      std::cout << " - " << c->getName().get() << " (" << c->getColor() << ")\n";
  }

  // Controlled swap method
  static void swapCats(Owner& a, Owner& b, int index) {
    if (index < 0 || index >= (int)a.cats.size() || index >= (int)b.cats.size())
      throw std::out_of_range("Invalid cat index for swap");
    std::swap(a.cats[index], b.cats[index]);
  }

  // Demonstrate secure password read
  void showPasswordOnce() {
    try {
      std::cout << name << "'s password (first read): " << password.readOnce() << "\n";
      std::cout << name << "'s password (second read): " << password.readOnce() << "\n";
    } catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
    }
  }
};

int main() {
  try {
    Owner alice(1, "Alice", "AlicePass123");
    Owner bob(2, "Bob", "BobSecure456");

    alice.addCat(Cat(CatName::of("Whiskers"), "white"));
    bob.addCat(Cat(CatName::of("Mittens"), "gray"));

    std::cout << "Before swap:\n";
    alice.showCats();
    bob.showCats();

    Owner::swapCats(alice, bob, 0);

    std::cout << "\nAfter swap:\n";
    alice.showCats();
    bob.showCats();

    std::cout << "\n--- Secret Data Demonstration ---\n";
    alice.showPasswordOnce(); // Will succeed once, then fail
  } 
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
