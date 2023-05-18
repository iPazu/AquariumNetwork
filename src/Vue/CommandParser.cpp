#include "include/CommandParser.hpp"
#include "include/Console.hpp"
#include <sstream>

CommandParser::CommandParser(Console& console)
        : mConsole(console) {}

void CommandParser::addCommand(const std::string& commandName, const std::function<void(const std::vector<std::string>&)>& commandFunction) {
    mCommands[commandName] = commandFunction;
}

void CommandParser::parse(const std::string& commandLine) {
    std::vector<std::string> tokens = tokenize(commandLine);

    if (tokens.empty()) {
        return;
    }

    const std::string& commandName = tokens.front();
    auto commandIter = mCommands.find(commandName);

    if (commandIter != mCommands.end()) {
        commandIter->second(std::vector<std::string>(tokens.begin() + 1, tokens.end()));
    } else {
        mConsole.println("Unknown command: " + commandName);
    }
}

std::vector<std::string> CommandParser::tokenize(const std::string& str) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(str);
    bool quotes = false;

    while (stream >> token) {
        if (token[0] == '"') {
            quotes = true;
            token.erase(token.begin());  // remove the first quote
        }
        if (quotes) {
            if (token[token.length()-1] == '"') {
                quotes = false;
                token.erase(token.end()-1);  // remove the last quote
            }
            if (!tokens.empty() && tokens.back()[0] != '"') {
                tokens.back() += " " + token;
            } else {
                tokens.push_back(token);
            }
        } else {
            tokens.push_back(token);
        }
    }

    return tokens;
}

