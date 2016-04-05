#include "datastructure.hh"
#include <iostream>

// Empty implementations for public interface, modify and add your own code here

Datastructure::Datastructure()
{
    _candyData.resize(_divider);
}

Datastructure::~Datastructure()
{
    deleteEveryCandy();
}

void Datastructure::add(const string &ID, const string &location,
                        unsigned int amount, const string &name)
{
    int index = hash(ID);
    Candy* c = _candyData[index];

    // Candy is placed in an empty slot.
    if (c == nullptr) {
        _candyData[index] = new Candy{ID, location, name, amount, nullptr, nullptr};
        _totalCount++;
    }
    else {
        while (c->_nextCandy != nullptr && c->_ID != ID) {
            c = c->_nextCandy;
        }
        if (c->_ID == ID) {
            c->_amount += amount;
        }
        // The new candy goes to the back of the linked list.
        else {
            Candy* newCandy = new Candy{ID, location, name, amount, nullptr, c};
            c->_nextCandy = newCandy;
            _totalCount++;
        }
    }
}

int Datastructure::hash(const std::string &ID) const
{
    int sum = 0;
    for (auto c : ID) {
        sum += c;
    }
    int hash = sum % _divider;
    return hash;
}

void Datastructure::substract(const string &ID, unsigned int amount)
{
    Candy* c = findCandyByID(ID);
    if (c) {
        deleteOrSubstract(c, amount);
    }
    else {
        std::cout << NOT_AVAILABLE << std::endl;
    }
}

Datastructure::Candy *Datastructure::findCandyByID(const std::string &ID) const
{
    int index = hash(ID);
    Candy* c = _candyData[index];
    while (c != nullptr && c->_ID != ID) {
        c = c->_nextCandy;
    }
    return c;
}

void Datastructure::deleteOrSubstract(Datastructure::Candy *c, unsigned int amount)
{
    if (c->_amount == amount) {
        deleteCandy(c);
    }
    else {
        substractByAmount(c, amount);
    }
}

void Datastructure::deleteCandy(Datastructure::Candy *c)
{
    std::cout << "Amount: " << 0 << " "
              << "Shelf: " << c->_location << std::endl;

    if (c->_nextCandy) {
        c->_nextCandy->_prevCandy = c->_prevCandy;
    }
    if ((c->_prevCandy)) {
        c->_prevCandy->_nextCandy = c->_nextCandy;
    }
    // We go here if we are removing the first element of the linked list.
    else {
        int index = hash(c->_ID);
        _candyData[index] = c->_nextCandy;
    }
    delete c;
    _totalCount--;
}

void Datastructure::substractByAmount(Datastructure::Candy *c, unsigned int amount)
{
    if (c->_amount > amount) {
        c->_amount -= amount;
    }
    else if (amount > c->_amount) {
        std::cout << NOT_ENOUGH_CANDY << std::endl;
    }
    std::cout << "Amount: " << c->_amount << " "
              << "Shelf: " << c->_location << std::endl;
}

void Datastructure::deleteEveryCandy()
{
    for (auto bucket : _candyData) {
        Candy* c = bucket;
        while (c) {
            Candy* oldCandy = c;
            c = c->_nextCandy;
            delete oldCandy;
        }
    }
}

void Datastructure::find(const string &ID) const
{
    Candy* c = findCandyByID(ID);
    if (c) {
        std::cout << c->_name << " "
                  << c->_amount << " "
                  << c->_location << " "
                  << std::endl;
    }
    else {
        std::cout << NOT_AVAILABLE << std::endl;
    }
}

size_t Datastructure::count() const
{
    return _totalCount;
}

void Datastructure::empty()
{
    _totalCount = 0;
    deleteEveryCandy();
    _candyData.clear();
    _candyData.resize(_divider);
}
