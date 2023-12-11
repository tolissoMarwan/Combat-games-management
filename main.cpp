#include <algorithm>
#include <vector>
#include <limits>

#include "Player/Player.h"

int getChoice() {
  int choice;
  while (true) {
    std::cout << "Enter your choice: ";
    try {
      std::cin >> choice;

      // Check if the input was successful
      if (std::cin.fail()) {
        // Clear the error flag
        std::cin.clear();

        // Ignore invalid input up to the newline character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw std::runtime_error(
            "Invalid input. Please enter a valid integer.");
      }

      // Check if the entered value is within the expected range
      if (choice < 1 || choice > 5) {
        throw std::out_of_range(
            "Invalid choice. Please enter a number between 1 and 5.");
      }

      break; // Input is valid, exit the loop
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return choice;
}

int getNumber() {
  int number;
  while (true) {
    std::cout << "Enter player number: ";
    try {
      std::cin >> number;

      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error(
            "Invalid input. Please enter a valid integer.");
      }

      break;
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return number;
}

int getHeight() {
  int height;
  while (true) {
    std::cout << "Enter player height (in cm): ";
    try {
      std::cin >> height;

      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error(
            "Invalid input. Please enter a valid integer for height.");
      }

      break;
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return height;
}

int getWeight() {
  int weight;
  while (true) {
    std::cout << "Enter player weight (in kg): ";
    try {
      std::cin >> weight;

      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error(
            "Invalid input. Please enter a valid integer for weight.");
      }

      break;
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return weight;
}

int getYearOfBirth() {
  int yearOfBirth;
  while (true) {
    std::cout << "Enter player year of birth: ";
    try {
      std::cin >> yearOfBirth;

      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error(
            "Invalid input. Please enter a valid integer for year of birth.");
      }

      break;
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return yearOfBirth;
}

int main() {
  std::vector<std::shared_ptr<Player>> players;

  auto createPlayer = [&players]() {
    int number, height, weight, yearOfBirth;
    std::string surname, firstName;

    // Ensure the number is unique
    do {
      number = getNumber();
    } while (Player::playerExists(players, number));

    std::cout << "Enter player surname: ";
    std::cin >> surname;

    std::cout << "Enter player first name: ";
    std::cin >> firstName;

    height = getHeight();

    weight = getWeight();

    yearOfBirth = getYearOfBirth();

    auto player = std::make_shared<Player>(number, surname, firstName, height,
                                           weight, yearOfBirth);

    players.push_back(player);

    std::cout << "Player created successfully.\n";
  };

  auto manageCombatGame = [&players]() {
    int player1Index, player2Index, result;
    std::cout << "Enter the index of the first player: ";
    std::cin >> player1Index;

    std::cout << "Enter the index of the second player: ";
    std::cin >> player2Index;

    std::cout << "Enter the result (0 for lost, 5 for tie, 10 for won): ";
    std::cin >> result;

    if (player1Index < 0 || player1Index >= players.size() ||
        player2Index < 0 || player2Index >= players.size()) {
      std::cout << "Invalid player indices!\n";
      return;
    }

    auto &player1 = players[player1Index];
    auto &player2 = players[player2Index];

    if (result == 10) {
      player1->updatePoints(10);
    } else if (result == 5) {
      player1->updatePoints(5);
      player2->updatePoints(5);
    } else {
      player2->updatePoints(10);
    }

    if (*player1 >= *player2) {
      std::cout << player1->getFirstName() << " " << player1->getSurname()
                << " has won. "
                << "He is " << player1->getHeight() - player2->getHeight()
                << " cm taller and "
                << player1->getWeight() - player2->getWeight()
                << " kg heavier than " << player2->getFirstName() << " "
                << player2->getSurname() << ".\n";
    } else {
      std::cout << player2->getFirstName() << " " << player2->getSurname()
                << " has won. "
                << "He is " << player2->getHeight() - player1->getHeight()
                << " cm taller and "
                << player2->getWeight() - player1->getWeight()
                << " kg heavier than " << player1->getFirstName() << " "
                << player1->getSurname() << ".\n";
    }
  };

  auto outputAllPlayers = [&players]() {
    for (const auto &player : players) {
      std::cout << *player << "\n";
    }
  };

  auto outputWinner = [&players]() {
    if (players.empty()) {
      std::cout << "No players available.\n";
    } else {
      auto winner = std::max_element(players.begin(), players.end(),
                                     [](const std::shared_ptr<Player> &a,
                                        const std::shared_ptr<Player> &b) {
                                       return a->getPoints() < b->getPoints();
                                     });

      std::cout << "Winner: " << *(*winner) << std::endl;
    }
  };

  int choice;

  do {
    std::cout << "\nMENU:\n";
    std::cout << "1. Create player\n";
    std::cout << "2. Manage combat game\n";
    std::cout << "3. Output all players\n";
    std::cout << "4. Output winner\n";
    std::cout << "5. Exit\n";

    choice = getChoice();

    switch (choice) {
    case 1:
      createPlayer();
      break;
    case 2:
      manageCombatGame();
      break;
    case 3:
      outputAllPlayers();
      break;
    case 4:
      outputWinner();
      break;
    case 5:
      return 0;
    default:
      std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
      break;
    }
  } while (5 != choice);

  return 0;
}
