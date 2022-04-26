#ifndef COMMANDINTERPRETER_REGISTER_H
#define COMMANDINTERPRETER_REGISTER_H

#include "BaseCommand.h"

#include <functional>
#include <map>
#include <memory>

class CmdInt_Register {
public:
    using CommandPointer = std::shared_ptr<CmdInt_BaseCommand>;

    template <typename _CommandType> //
    static void AddCommand();

    static CommandPointer GetCommand(std::string_view commandName);

private:
    using CreateCommandFun = std::function<CommandPointer()>;
    using CommandsMap = std::map<std::string_view, CreateCommandFun>;

    static CommandsMap _commandsMap;
};

template <typename _CommandType> void CmdInt_Register::AddCommand() {
    static_assert(std::is_base_of_v<CmdInt_BaseCommand, _CommandType>, //
        "CmdInt_CommandFactory::RegisterCommand() _CommandType must be an extension of CmdInt_BaseCommand");
    _commandsMap.emplace(_CommandType::COMMAND_NAME, []() { return std::make_shared<_CommandType>(); });
}
#endif // COMMANDINTERPRETER_REGISTER_H
