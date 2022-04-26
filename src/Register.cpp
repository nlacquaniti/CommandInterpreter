#include "Register.h"

CmdInt_Register::CommandsMap CmdInt_Register::_commandsMap;

CmdInt_Register::CommandPointer CmdInt_Register::GetCommand(std::string_view commandName) {
    const auto commandIt = _commandsMap.find(commandName);
    if (commandIt != _commandsMap.cend()) {
        return commandIt->second();
    }
    return nullptr;
}
