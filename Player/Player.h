#pragma once

#include <iostream>
#include <vector>
#include <memory>

class Player {
public:
    Player(int number, std::string surname, std::string firstName, int height, int weight, int yearOfBirth);

    bool operator>=(const Player& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    // get functions
    int getNumber() const;
    std::string getSurname() const;
    std::string getFirstName() const;
    int getHeight() const;
    int getWeight() const;
    int getPoints() const;
    int getYearOfBirth() const;
    int getFightsWon() const;
    int getFightsTied() const;
    int getFightsLost() const;

    void updatePoints(int result);
    static bool playerExists(const std::vector<std::shared_ptr<Player>>& players, int number);

private:
    int number;
    std::string surname;
    std::string firstName;
    int height;
    int weight;
    int points;
    int yearOfBirth;
    int fightsWon;
    int fightsTied;
    int fightsLost;
};
