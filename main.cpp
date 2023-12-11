#include <iostream>
#include <vector>
#include <algorithm>

class Player {
public:
    Player(int number, std::string surname, std::string firstName, int height, int weight, int yearOfBirth)
        : number(number), surname(surname), firstName(firstName), height(height), weight(weight),
          points(0), yearOfBirth(yearOfBirth), fightsWon(0), fightsTied(0), fightsLost(0) {}

    bool operator>=(const Player& other) const {
        return (height >= other.height) && (weight >= other.weight);
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    int getNumber() const {
        return number;
    }

    std::string getSurname() const {
        return surname;
    }

    std::string getFirstName() const {
        return firstName;
    }

    int getHeight() const {
        return height;
    }

    int getWeight() const {
        return weight;
    }

    int getPoints() const {
        return points;
    }

    int getYearOfBirth() const {
        return yearOfBirth;
    }

    int getFightsWon() const {
        return fightsWon;
    }

    int getFightsTied() const {
        return fightsTied;
    }

    int getFightsLost() const {
        return fightsLost;
    }

    void updatePoints(int result) {
        points += result;
        if (result == 10) {
            fightsWon++;
        } else if (result == 5) {
            fightsTied++;
        } else {
            fightsLost++;
        }
    }

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

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.getFirstName() << " " << player.getSurname() << ", " << player.getYearOfBirth() << ", "
       << player.getHeight() << "cm, " << player.getWeight() << "kg, participated in " << (player.getFightsWon() + player.getFightsTied() + player.getFightsLost())
       << " combat games: " << player.getFightsWon() << " x won, " << player.getFightsTied() << " x tie = " << player.getPoints() << " points";
    return os;
}

void manageCombatGame(std::vector<Player*>& players) {
    int player1Index, player2Index, result;
    std::cout << "Enter the index of the first player: ";
    std::cin >> player1Index;

    std::cout << "Enter the index of the second player: ";
    std::cin >> player2Index;

    std::cout << "Enter the result (0 for lost, 5 for tie, 10 for won): ";
    std::cin >> result;

    if (player1Index < 0 || player1Index >= players.size() || player2Index < 0 || player2Index >= players.size()) {
        std::cout << "Invalid player indices!" << std::endl;
        return;
    }

    Player* player1 = players[player1Index];
    Player* player2 = players[player2Index];

    if (result == 10) {
        player1->updatePoints(10);
    } else if (result == 5) {
        player1->updatePoints(5);
        player2->updatePoints(5);
    } else {
        player2->updatePoints(10);
    }

    if (*player1 >= *player2) {
        std::cout << player1->getFirstName() << " " << player1->getSurname() << " has won. "
                  << "He is " << player1->getHeight() - player2->getHeight() << " cm taller and "
                  << player1->getWeight() - player2->getWeight() << " kg heavier than "
                  << player2->getFirstName() << " " << player2->getSurname() << "." << std::endl;
    } else {
        std::cout << player2->getFirstName() << " " << player2->getSurname() << " has won. "
                  << "He is " << player2->getHeight() - player1->getHeight() << " cm taller and "
                  << player2->getWeight() - player1->getWeight() << " kg heavier than "
                  << player1->getFirstName() << " " << player1->getSurname() << "." << std::endl;
    }
}

int main() {
    std::vector<Player*> players;

    while (true) {
        std::cout << "\nMENU:" << std::endl;
        std::cout << "1. Create player" << std::endl;
        std::cout << "2. Manage combat game" << std::endl;
        std::cout << "3. Output all players" << std::endl;
        std::cout << "4. Output winner" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int number, height, weight, yearOfBirth;
                std::string surname, firstName;

                std::cout << "Enter player number: ";
                std::cin >> number;

                std::cout << "Enter player surname: ";
                std::cin >> surname;

                std::cout << "Enter player first name: ";
                std::cin >> firstName;

                std::cout << "Enter player height (in cm): ";
                std::cin >> height;

                std::cout << "Enter player weight (in kg): ";
                std::cin >> weight;

                std::cout << "Enter player year of birth: ";
                std::cin >> yearOfBirth;

                players.push_back(new Player(number, surname, firstName, height, weight, yearOfBirth));

                std::cout << "Player created successfully." << std::endl;
                break;
            }
            case 2:
                manageCombatGame(players);
                break;
            case 3:
                for (const auto& player : players) {
                    std::cout << *player << std::endl;
                }
                break;
            case 4: {
                if (players.empty()) {
                    std::cout << "No players available." << std::endl;
                } else {
                    auto winner = std::max_element(players.begin(), players.end(),
                        [](const Player* a, const Player* b) { return a->getPoints() < b->getPoints(); });

                    std::cout << "Winner: " << *(*winner) << std::endl;
                }
                break;
            }
            case 5:
                for (auto player : players) {
                    delete player;
                }
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
