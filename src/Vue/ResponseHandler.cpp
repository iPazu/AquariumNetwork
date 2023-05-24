#include "include/ResponseHandler.hpp"
#include <sstream>
#include <regex>
#include "include/ClientController.hpp"
#include <sstream>

ResponseHandler::ResponseHandler(Console& console,Aquarium * aquarium,ClientController * clientController)
        : console(console),aquarium(aquarium), mclientController(clientController)
{}

ResponseHandler::RESPONSE_TYPE ResponseHandler::responseType(const std::string& response) {
    std::istringstream iss(response);
    std::string word;
    if (iss >> word) {
        if (word == "hello" ) {
            return RESPONSE_TYPE::AUTHENTICATION;
        } else if (word == "list") {
            return RESPONSE_TYPE::GET_FISHES;  // assuming the "ls" command also starts with "list"
        }
        else if (word == "status") {
            return RESPONSE_TYPE::STATUS;  // assuming the "ls" command also starts with "list"
        }
        else if (word == "ls") {
            return RESPONSE_TYPE::LS;  // assuming the "ls" command also starts with "list"
        }
        else if (word == "pong") {
            return RESPONSE_TYPE::PONG;  // assuming the "ls" command also starts with "list"
        }else if (word == "startFish") {
            return RESPONSE_TYPE::STARTFISH;  // assuming the "ls" command also starts with "list"
        }else {
            return RESPONSE_TYPE::UNKNOWN;
        }
    }
    return RESPONSE_TYPE::UNKNOWN;
}


void ResponseHandler::processResponse(const std::string& response) {
    std::cout << "Processing response..." << std::endl;
    console.println("Response received: " + response + "\n");
    switch (responseType(response)) {
        case RESPONSE_TYPE::AUTHENTICATION: {
            handleAuthentication(response);
            //std::cout << "Connected as Client ID: " << clientId << std::endl;
            console.println(response);
            mclientController->has_view = true;
            break;
        }
        case RESPONSE_TYPE::GET_FISHES: {
            std::cout << "GET_FISHES" << std::endl;
            std::vector<std::vector<Fish>> fishListBatch = handleGetFishes(response);

            break;
        }
        case RESPONSE_TYPE::LS: {
            std::vector<std::vector<Fish>> fishListBatch = handleLS(response);
            // TODO: Update your fish list in the display program with fishListBatch
            break;
        }
        case RESPONSE_TYPE::PONG: {
            std::cout << "PONG" << std::endl;
            break;
        }
        case RESPONSE_TYPE::STATUS: {
            std::cout << "STATUS" << std::endl;
            handleStatus(response);
            break;
        }
        case RESPONSE_TYPE::STARTFISH: {
            std::cout << "STARTFISH" << std::endl;
            // handleStatus(response);
            break;
        }
        case RESPONSE_TYPE::DELFISH: {
            std::cout << "DELFISH" << std::endl;
            // handleStatus(response);
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
    printf("handleGreeting\n");

    int viewId, viewX, viewY;
    int scanned = sscanf(response.c_str(), "hello -> OK : greeting %d, %dx%d", &viewId, &viewX, &viewY);

    if(scanned == 3)
    {
        aquarium->setAquariumAt(viewX, viewY);
    }
    return "";
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

        //fishList.push_back(std::move(fish));
    }
    return fishList;
}


void ResponseHandler::handleStatus(const std::string& response) {
    printf("handleStatus\n");

    std::string buffer;
    mclientController->receive(buffer);
    std::cout << "Received: " << buffer << std::endl;

    std::stringstream ss(buffer);
    std::string line;

    std::vector<std::string> fishes {};

    while (std::getline(ss, line)) {
        int posx, posy, sizex, sizey;
        char name[50];
        char status[50];
        int scanned = sscanf(line.c_str(), "Fish %s at %dx%d, %dx%d, %s",
                             name, &posx, &posy, &sizex, &sizey, status);
        if (scanned == 6) {
            if(aquarium->isFishInAquarium(name))
            {
                std::cout << "Updating fish target" << std::endl;
                aquarium->setFishTarget(name, posx, posy, 1.f);
            } else {
                aquarium->addFish(name, getRandomFishType(), posx, posy, sizex, sizey, 0,0,0,FISH_BEHAVIOR::LINEAR);
            }
            std::cout << "Name: " << name
                      << ", Position: " << posx << "x" << posy
                      << ", Size: " << sizex << "x" << sizey
                      << ", Status: " << status << std::endl;
            fishes.push_back(name);
        } else {
            std::cerr << "Failed to parse line: " << line << std::endl;
        }

        for(auto& f: fishes)
        {
            if(!aquarium->isFishInAquarium(f))
            {
                aquarium->removeFish(f);
            }
        }
    }




    /*while (iss >> word) {
    if (word == "Fish") {

        std::string name, at, dimensionPair, status;
        iss >> name >> at >> dimensionPair >> status;

        std::istringstream pairStream(dimensionPair);
        std::string position, size;
        std::getline(pairStream, position, ',');
        std::getline(pairStream, size, ',');

        std::istringstream posStream(position);
        std::string val;
        std::vector<float> positionValues;
        while (std::getline(posStream, val, 'x')) {
            positionValues.push_back(std::stof(val));
        }

        std::istringstream sizeStream(size);
        std::vector<float> sizeValues;
        while (std::getline(sizeStream, val, 'x')) {
            sizeValues.push_back(std::stof(val));
        }

        float posx = positionValues[0], posy = positionValues[1];
        float sizex = sizeValues[0], sizey = sizeValues[1];
        // assuming target values and timeToTarget are fixed for simplicity
        float targetx = 0.0f, targety = 0.0f, timeToTarget = 0.0f;

        printf("Fish %s is %s\n", name.c_str(), status.c_str());
        printf("Position: %f, %f\n", posx, posy);
        printf("Size: %f, %f\n", sizex, sizey);
        printf("Target: %f, %f\n", targetx, targety);
        printf("Time to target: %f\n", timeToTarget);

        std::cout << "Fish " << name << " is " << status << std::endl;
        aquarium->addFish(name,FISH_TYPE::BLUE,posx,posy,sizex,sizey,targetx,targety,timeToTarget,FISH_BEHAVIOR::LINEAR);
    }*/
    //}
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
