#ifndef COMMANDINTERPRETER_REGISTER_H
#define COMMANDINTERPRETER_REGISTER_H

#include "BaseCommand.h"

#include <functional>
#include <map>
#include <memory>

/**
 * @brief Register of commands supported by the interpreter.
 *
 * Commands must be added with a call to @a AddCommand<CommandType>(),
 * and an instance of a command can be reterieved with a call to
 * @a GetCommand(commandName).
 *
 * If you don't know the command name you can use CommandType::COMMAND_NAME.
 */
class CmdInt_Register {
public:
    using CommandPointer = std::shared_ptr<CmdInt_BaseCommand>;

    /**
     * @brief Adds a permanent command type to the register.
     *
     * _CommandType template param must extend from CmdInt_BaseCommand.
     *
     * If you like to reterive an instance of a command call @a GetCommand(commandName).
     * In case you don't know the name of the command use _CommandType::COMMAND_NAME.
     *
     * @param[in] _CommandType command that that extends CmdInt_BaseCommand to register.
     */
    template <typename _CommandType> //
    static void AddCommand();

    /**
     * @brief Reterives an instance of a command by name.
     *
     * The name can be specified as a string if you know the name,
     * or if you know the type of the command you can use CommandTpe::COMMAND_NAME.
     *
     * @param[in] commanName The name of the command to reterive.
     * @returns A pointer to the command.
     * Nullptr if the command type has not been registered with a call to @a AddCommand
     */
    static CommandPointer GetCommand(std::string_view commandName);

private:
    using CreateCommandFun = std::function<CommandPointer()>;
    using CommandsMap = std::map<std::string_view, CreateCommandFun>;

    static CommandsMap _commandsMap;
};

template <typename _CommandType> void CmdInt_Register::AddCommand() {
    static_assert(std::is_base_of_v<CmdInt_BaseCommand, _CommandType>, //
        "CmdInt_Register::AddCommand() _CommandType must be an extension of CmdInt_BaseCommand");
    _commandsMap.emplace(_CommandType::COMMAND_NAME, []() { return std::make_shared<_CommandType>(); });
}
#endif // COMMANDINTERPRETER_REGISTER_H
