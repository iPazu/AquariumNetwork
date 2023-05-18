#include "include/ResponseHandler.hpp"
#include <sstream>

ResponseHandler::ResponseHandler(Console& console)
        : console(console)
{}

ResponseHandler::RESPONSE_TYPE ResponseHandler::responseType(const std::string& response) {
    std::istringstream iss(response);
    std::string word;
    if (iss >> word) {
        if (word == "greeting" || word == "no") {
            return RESPONSE_TYPE::AUTHENTICATION;
        } else if (word == "list") {
            return RESPONSE_TYPE::GET_FISHES;  // assuming the "ls" command also starts with "list"
        } else {
            return RESPONSE_TYPE::UNKNOWN;
        }
    }
    return RESPONSE_TYPE::UNKNOWN;
}
void ResponseHandler::processResponse(const std::string& response) {
    std::cout << response << std::endl;
    console.println("Recieved:");
    console.println(response);
    switch (responseType(response)) {
        case RESPONSE_TYPE::AUTHENTICATION: {
            std::string clientId = handleAuthentication(response);
            std::cout << "Client ID: " << clientId << std::endl;
            console.println("Client ID: " + clientId);

            break;
        }
        case RESPONSE_TYPE::GET_FISHES: {
            std::cout << "GET_FISHES" << std::endl;
            console.println("GET_FISHES");
            // TODO: You may want to do something else here.
            break;
        }
        case RESPONSE_TYPE::LS: {
            std::vector<std::vector<Fish>> fishListBatch = handleLS(response);
            // TODO: Update your fish list in the display program with fishListBatch
            break;
        }
        default: {
            std::cerr << "Unknown response type.\n";
            break;
        }
    }
}

std::vector<std::vector<Fish>> ResponseHandler::handleGetFishes(const std::string& response) {
    return handleLS(response);  // getFishes and ls have the same response format
}

std::vector<std::vector<Fish>> ResponseHandler::handleLS(const std::string& response) {
    std::vector<std::vector<Fish>> fishListBatch;
    std::istringstream iss(response);
    std::string line;

    while (std::getline(iss, line)) {
        std::vector<Fish> fishList;
        std::istringstream lineStream(line);
        std::string word;

        while (lineStream >> word) {
            if (word == "list") {
                fishList = parseFishList(lineStream);
            }
        }
        fishListBatch.push_back(std::move(fishList));
    }

    return fishListBatch;
}

std::string ResponseHandler::handleAuthentication(const std::string& response) {
    std::istringstream iss(response);
    std::string word;
    iss >> word;  // "greeting" or "no"
    if (word == "greeting") {
        iss >> word;  // client ID
        return word;
    } else {
        return "Error: No greeting";
    }
}

std::vector<Fish> ResponseHandler::parseFishList(std::istringstream& lineStream) {
    std::vector<Fish> fishList;
    std::string word;
    while (lineStream >> word) {
        // Assuming fish type is the first word and position is next
        FISH_TYPE type = getFishType(word);
        sf::Vector2f initialPosition, targetPosition;
        float timeToTarget;

        lineStream >> word; // Get the word "at"

        // Get the positions and time
        lineStream >> initialPosition.x >> initialPosition.y >> targetPosition.x >> targetPosition.y >> timeToTarget;

        // Create new fish and add to list
        Fish fish(initialPosition.x, initialPosition.y, targetPosition.x, targetPosition.y, timeToTarget, type, FISH_BEHAVIOR::LINEAR);
        //fishList.push_back(std::move(fish));
    }
    return fishList;
}

FISH_TYPE ResponseHandler::getFishType(const std::string& str) {
    // Assume two types of fish: PoissonRouge and PoissonClown
    if (str == "PoissonRouge") {
        return FISH_TYPE::BLUE;
    } else if (str == "PoissonClown") {
        return FISH_TYPE::SHARK;
    } else {
        // Default case
        return FISH_TYPE::BLUE;
    }
}
