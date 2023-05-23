#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include <vector>
#include <string>
#include "Fish.hpp"
#include "Console.hpp"
#pragma once
class ResponseHandler {
public:
    ResponseHandler(Console& console);

    enum class RESPONSE_TYPE {
        AUTHENTICATION,
        GET_FISHES,
        LS,
        PONG,
        UNKNOWN
    };

    void processResponse(const std::string& response);

private:
    RESPONSE_TYPE responseType(const std::string& response);
    std::vector<std::vector<Fish>> handleGetFishes(const std::string& response);
    std::vector<std::vector<Fish>> handleLS(const std::string& response);
    std::string handleAuthentication(const std::string& response);

    FISH_TYPE getFishType(const std::string& str);
    std::vector<Fish> parseFishList(std::istringstream& lineStream);
    Console& console;
};

#endif // RESPONSE_HANDLER_HPP
