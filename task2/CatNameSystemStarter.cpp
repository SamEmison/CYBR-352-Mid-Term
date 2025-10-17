//Sam Emison
//10/17/2025
//Code imported from demo files

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Cat {
public:
    std::string name;
    std::string color;

    Cat(std::string n, std::string c) : name(n), color(c) {
      if (n.empty() || n.size() > 20) {
	throw std::invalid_argument("Invalid cat name length");
      }
      for (char ch : n) {
	if (!isalnum(ch) && ch != ' ' && ch != '-' && ch != '_') {
	  throw std::invalid_argument("Invalid character in cat name");
	}
      }
      if (c.empty() || c.size() > 20) {
	throw std::invalid_argument("Invalid cat color");
      }

      name = n;
      color = c;
    }
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
  try {
    //Valid cat test
    Cat validCat("Whiskers", "White");
    std::cout << "Added cat: " << validCat.name << " (" << validCat.color << ")\n";

    //Invalid cat test
    Cat invalidCat("ThisNameIsWayTooLongToBeValid", "");
    std::cout << "Added cat: " << invalidCat.name << " (" << invalidCat.color << ")\n";

  }
  catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
    
    Owner alice("Alice");
    alice.addCat(Cat("Mittens", "gray"));
    alice.showCats();
    return 0;
}
