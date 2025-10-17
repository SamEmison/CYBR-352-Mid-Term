#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

//CatName
class CatName {
private:
  std::string value;
  CatName(const std::string& n) : value(n) {}

public:
  static CatName of(const std::string& n) {
    if (n.empty() || n.size() > 20) {
      throw std::invalid_argument("Invalid cat name length");
    }
    for (char ch : n) {
      if (!isalnum(ch) && ch != ' ' && ch != '-' && ch != '_') {
	throw std::invalid_argument("Invalid character in cat name");
      }
    }
    return CatName(n);
  }
  
  std::string get() const { return value; }
};

//Cat
class Cat {
private:
  const CatName name;
  const std::string color;

public:
  Cat(const CatName& n, const std::string& c) : name(n), color(c) {
    if (c.empty() || c.size() > 20) {
      throw std::invalid_argument("Invalid cat color");
    }
  }

  const CatName& getName() const { return name; }
  const std::string& getColor() const { return color; }
};

//Owner
class Owner {
private:
  int id;  // unique identifier
  std::string name;
  std::vector<Cat> cats;

public:
  Owner(int ownerId, const std::string& ownerName) : id(ownerId), name(ownerName) {}

  int getId() const { return id; }
  const std::string& getName() const { return name; }

  void addCat(const Cat& cat) { cats.push_back(cat); }

  void showCats() const {
    std::cout << name << "'s Cats:\n";
    for (const auto& c : cats) {
      std::cout << " - " << c.getName().get() << " (" << c.getColor() << ")\n";
    }
  }
};


int main() {
  try {
    // --- Valid Cats ---
    Cat cat1(CatName::of("Whiskers"), "white");
    Cat cat2(CatName::of("Mittens"), "gray");
    Cat cat3(CatName::of("Fluffy"), "tabby");
    Cat cat4(CatName::of("Shadow"), "black");

    std::cout << "Added cat: " << cat1.getName().get() << " (" << cat1.getColor() << ")\n";
    std::cout << "Added cat: " << cat2.getName().get() << " (" << cat2.getColor() << ")\n";

    //Invalid Cat (fail-fast)
    try {
      Cat invalidCat(CatName::of("ThisNameIsWayTooLongToBeValid"), "black");
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error: " << e.what() << "\n";
    }

    //Owners
    Owner alice(1, "Alice");
    Owner bob(2, "Bob");

    // Assign Cats
    alice.addCat(cat1);
    alice.addCat(cat2);
    bob.addCat(cat3);
    bob.addCat(cat4);

    // Show Cats for each Owner
    alice.showCats();
    bob.showCats();

    //Commented so it will compile. Cat is immutable
    // Cat testCat(CatName::of("Test"), "green");
    // testCat.getColor() = "blue";
    
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
