#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class CatName {
private:
  std::string value;

  CatName(const std::string& n) : value(n) {}

public:
  static CatName of(const std::string& n) {
    if (n.empty() || n.size() > 20) {
      throw std::invalid_argument("Invalid cat name length");
    }

    for (char ch: n) {
      if (!isalnum(ch) && ch != ' ' && ch != '_' && ch!= '_') {
	throw std::invalid_argument("Invalid character in cat name");
      }
    }
    return CatName(n);
  }

  std::string get() const { return value; }
};



class Cat {
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
      std::cout << " - " << c.name.get() << " (" << c.color << ")\n";
  }
};

    Cat(std::string n, std::string c) : name(n), color(c) {}
};


int main() {
  try {
        // Valid cat
    CatName goodName = CatName::of("Whiskers");
    Cat validCat(goodName, "white");

        // Invalid cat name (too long)
    CatName badName = CatName::of("ThisNameIsWayTooLongToBeValid");  // triggers exception
    Cat invalidCat(badName, "black");

  }
  catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  Owner alice("Alice");
  alice.addCat(Cat(CatName::of("Mittens"), "gray"));
  alice.showCats();
  return 0;
}
