#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include <vector>
#include <string>
#include "Fish.hpp"
#include "Console.hpp"
#include "Aquarium.hpp"
#pragma once
class ResponseHandler {
public:
    ResponseHandler(Console& console,Aquarium * aquarium,ClientController * clientController);

    enum class RESPONSE_TYPE {
        AUTHENTICATION,
        GET_FISHES,
        LS,
        STATUS,
        PONG,
        STARTFISH,
        UNKNOWN
    };

    void processResponse(const std::string& response);

private:
    RESPONSE_TYPE responseType(const std::string& response);
    std::vector<std::vector<Fish>> handleGetFishes(const std::string& response);
    std::vector<std::vector<Fish>> handleLS(const std::string& response);
    std::string handleAuthentication(const std::string& response);
    void handleStatus(const std::string& response);

    FISH_TYPE getFishType(const std::string& str);
    std::vector<Fish> parseFishList(std::istringstream& lineStream);
    Console& console;
    Aquarium * aquarium;
    ClientController * mclientController;
};

#endif // RESPONSE_HANDLER_HPP
