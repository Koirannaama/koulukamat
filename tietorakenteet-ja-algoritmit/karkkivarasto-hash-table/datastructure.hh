// Definition of Datastructure class for UDS/Tiraka homework 2 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
using std::string;

const std::string NOT_AVAILABLE = "Product not in warehouse.";
const std::string NOT_ENOUGH_CANDY = "Not enough candy available.";

class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds candies to the datastructure (command "A")
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);
          
    // Removes candies from the datastructure (command "D")
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status (command "F")
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains (command "C")
    size_t count() const;

    // Empties the datastructure (command "E")
    void empty();
    
    // Copy constructor is forbidden (not important for this assignment)
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden (not important for this assignment)
    Datastructure& operator=(const Datastructure&) = delete;
    
private:
    struct Candy {
        std::string _ID;
        std::string _location;
        std::string _name;
        unsigned int _amount;
        Candy* _nextCandy;
        Candy* _prevCandy;
    };

    size_t _totalCount = 0;
    // Number of slots in the hash table and the divisor for the hash function.
    int const _divider = 1511;
    // A vector that contains doubly linked lists which contain the candy data.
    std::vector<Candy*> _candyData;

    // A function that produces an index for a slot in the hash table.
    int hash(const std::string& ID) const;

    Candy* findCandyByID(const std::string& ID) const;

    void deleteOrSubstract(Candy* c, unsigned int amount);

    void deleteCandy(Candy* c);

    void substractByAmount(Candy* c, unsigned int amount);

    void deleteEveryCandy();
};

#endif
