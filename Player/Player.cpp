#include "Player/Player.h"

Player::Player(int number, std::string surname, std::string firstName, int height, int weight, int yearOfBirth)
    : number(number), surname(surname), firstName(firstName), height(height), weight(weight),
      points(0), yearOfBirth(yearOfBirth), fightsWon(0), fightsTied(0), fightsLost(0) {}

bool Player::operator>=(const Player& other) const {
    return (height >= other.height) && (weight >= other.weight);
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.getFirstName() << " " << player.getSurname() << ", " << player.getYearOfBirth() << ", "
       << player.getHeight() << "cm, " << player.getWeight() << "kg, participated in " << (player.getFightsWon() + player.getFightsTied() + player.getFightsLost())
       << " combat games: " << player.getFightsWon() << " x won, " << player.getFightsTied() << " x tie = " << player.getPoints() << " points";
    return os;
}

int Player::getNumber() const {
    return number;
}

std::string Player::getSurname() const {
    return surname;
}

std::string Player::getFirstName() const {
    return firstName;
}

int Player::getHeight() const {
    return height;
}

int Player::getWeight() const {
    return weight;
}

int Player::getPoints() const {
    return points;
}

int Player::getYearOfBirth() const {
    return yearOfBirth;
}

int Player::getFightsWon() const {
    return fightsWon;
}

int Player::getFightsTied() const {
    return fightsTied;
}

int Player::getFightsLost() const {
    return fightsLost;
}

void Player::updatePoints(int result) {
    points += result;
    if (result == 10) {
        fightsWon++;
    } else if (result == 5) {
        fightsTied++;
    } else {
        fightsLost++;
    }
}

bool Player::playerExists(const std::vector<std::shared_ptr<Player>> &players, int number)
{
    for (const auto& player : players) {
        if (player->getNumber() == number) {
            std::cout << "Player with the same number already exists: " << number << " . Please choose a unique number.\n";
            return true;
        }
    }
    return false;
}
