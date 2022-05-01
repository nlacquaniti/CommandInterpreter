#include "Register.h"

#include "UnrecognisedCommand.h"

CmdInt_Register::CommandsMap CmdInt_Register::_commandsMap{{
    // Add fallback command.
    CmdInt_UnrecognisedCommand::COMMAND_NAME,                     //
    [] { return std::make_shared<CmdInt_UnrecognisedCommand>(); } //
}};

CmdInt_Register::CommandPointer CmdInt_Register::GetCommand(std::string_view commandName) {
    const auto commandIt = _commandsMap.find(commandName);
    if (commandIt != _commandsMap.cend()) {
        return commandIt->second();
    }
    return nullptr;
}
