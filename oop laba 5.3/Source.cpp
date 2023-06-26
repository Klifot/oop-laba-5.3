#include <iostream>
#include <string>

class Furniture {
protected:
    std::string material;

public:
    Furniture(const std::string& material) : material(material) {
    }

    Furniture(const Furniture& other) : material(other.material) {
    }

    virtual ~Furniture() {
    }

    Furniture& operator=(const Furniture& other) {
        if (this != &other) {
            material = other.material;
        }
        return *this;
    }

    virtual void print() const {
        std::cout << "Material: " << material << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Furniture& furniture) {
        os << "Material: " << furniture.material;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Furniture& furniture) {
        is >> furniture.material;
        return is;
    }
};

class Table : public Furniture {
private:
    int numOfLegs;

public:
    Table(const std::string& material, int numOfLegs) : Furniture(material), numOfLegs(numOfLegs) {
    }

    Table(const Table& other) : Furniture(other), numOfLegs(other.numOfLegs) {
    }

    Table& operator=(const Table& other) {
        if (this != &other) {
            Furniture::operator=(other);
            numOfLegs = other.numOfLegs;
        }
        return *this;
    }

    void print() const override {
        Furniture::print();
        std::cout << "Number of Legs: " << numOfLegs << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Table& table) {
        os << static_cast<const Furniture&>(table);
        os << ", Number of Legs: " << table.numOfLegs;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Table& table) {
        is >> static_cast<Furniture&>(table);
        is >> table.numOfLegs;
        return is;
    }
};

int main() {
    Table table("Wood", 4);
    table.print();

    std::cout << std::endl;

    Table copiedTable = table;
    copiedTable.print();

    std::cout << std::endl;

    Table assignedTable("Plastic", 3);
    std::cout << "Before assignment: " << assignedTable << std::endl;
    assignedTable = table;
    std::cout << "After assignment: " << assignedTable << std::endl;

    std::cout << std::endl;

    std::cout << "Enter table details: ";
    std::cin >> table;
    std::cout << "Entered table details: " << table << std::endl;

    return 0;
}