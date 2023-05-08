#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <string>
#include <map>
#include <functional>
#include <vector>
#include "Console.hpp"

class Console;

class CommandParser {
public:
    CommandParser(Console& console);
    void addCommand(const std::string& commandName, const std::function<void(const std::vector<std::string>&)>& commandFunction);
    void parse(const std::string& commandLine);

private:
    Console& mConsole;
    std::map<std::string, std::function<void(const std::vector<std::string>&)>> mCommands;
    std::vector<std::string> tokenize(const std::string& str);
};

#endif // COMMAND_PARSER_HPP
