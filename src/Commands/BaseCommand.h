#ifndef COMMANDINTERPRETER_BASE_COMMAND_H
#define COMMANDINTERPRETER_BASE_COMMAND_H

#include "CommandInterpreter/Types.h"
#include "CommandUtility.h"

#include <string_view>

/**
 * @brief Contains the result data of a command that has been executed.
 *
 * N.B. in order to yield a complete result, some commands requires to be executed
 * multiple time (es. if the command is a timer).
 *
 * That's why you should keep an eye to the result of @a IsExecutionCompleted.
 *
 * When a command has multiple steps it can yield a result with a nullptr to @a CommandOutput.
 */
struct CmdInt_CommandExecutedResult {
    CmdInt_CommandExecutedResult(CmdInt_UserContextData userContextData)
        : CommandOutput(nullptr)
        , UserContextData(userContextData)
        , IsExecutionCompleted(true) {}

    /**
     * @brief Result message of the executed command.
     */
    CmdInt_CommandOutput CommandOutput;

    /**
     * @brief Generic data injected by the user.
     * This data isn't modified by the command.
     */
    CmdInt_UserContextData UserContextData;

    /**
     * @brief Some commands requires to be executed
     * multiple time (es. if the command is a timer).
     *
     * Keep an eye to this flag to know if the command
     * execution is completed.
     */
    bool IsExecutionCompleted;
};

/**
 * @brief Base interface for every command.
 *
 * Contains baisc data that all commands must have,
 * like the command name and params (es. countdown seconds).
 *
 * It also contains the command raw params (the input string from the user)
 * (es. countdown 5).
 *
 * N.B. even if this class implements some basic logic it contains some
 * pure virtual methods so it can't be instantiated directly.
 */
class CmdInt_BaseCommand {
public:
    virtual ~CmdInt_BaseCommand() = default;

    /**
     * @brief Initialise all the mandatory data.
     *
     * This method should be always called before executing the command
     * otherwhise its result is unpredictable.
     *
     * @param[in] command Raw command as a string to execute.\n
     * This string is parsed and the params (if any) are extracted\n
     * and converted to the respective type.
     *
     * @param[in] userContextData Generic user defined data.\n
     * Its stored and returned without alteration everytime the command is executed.
     *
     * @returns bool that rapresent the success or not of initialisation.
     */
    bool InitCommand(std::string_view command, CmdInt_UserContextData userContextData) {
        _rawCommand = command;
        _userContextData = userContextData;
        _commandRawParams = CmdInt_CommandUtility::RemoveRawCommandName(command);
        return _parseRawCommandParams(_commandRawParams);
    }

    /**
     * @brief Executes the internal logic of the command.
     *
     * Everytime its called returns an instance of @a CmdInt_CommandExecutedResult
     * form which the user can inspects the result yields from the previous call.
     *
     * N.B. in order to yield a complete result, some commands requires to be executed
     * multiple time (es. if the command is a timer).
     *
     * That's why you should keep an eye to the result of @a IsExecutionCompleted.
     *
     * When a command has multiple steps it can yield a result with a nullptr to @a CommandOutput.
     *
     * @return an instance of CmdInt_CommandExecutedResult from which is stored the
     * output of the execution.
     */
    CmdInt_CommandExecutedResult ExecuteCommand() {
        CmdInt_CommandExecutedResult result(_userContextData);
        _execute(result);
        return result;
    }

    /**
     * @brief Getter to the raw command provided by the user
     * (es. "echo countdown", "countdown 5").
     *
     * @returns A string of the raw command provided by the user.
     */
    [[nodiscard]] std::string_view GetRawCommand() const { return _rawCommand; }

    /**
     * @brief Getter to the raw params (as a string) of the command
     * (es. "5", "20 60 30", "pull", "exit build").
     *
     * Each command is sepatated by a whitespace.
     *
     * @returns A string of params separated by a whitespace.
     */
    [[nodiscard]] std::string_view GetRawCommandParams() const { return _commandRawParams; }

    /**
     * @brief Getter of the raw name (as a string) of the command.
     * @return A string of the name of the command
     */
    [[nodiscard]] std::string_view GetCommandName() const { return _getCommandName(); }

    /**
     * @brief Getter of the param names (as a string) of the command
     * separated by a whitespace (es. "arg0 arg1 arg2").
     *
     * @return A string param names separated by a whitespace.
     */
    [[nodiscard]] std::string_view GetCommandParamNames() const { return _getCommandParamsName(); }

private:
    /**
     * @brief Parses the input raw params string and converts
     * each param to the associated type.
     *
     * However since the implementation is up the the user the functionality
     * is up to the user.
     *
     * This method is called by @a InitCommand
     *
     * @param[in] rawParams String of params separated by a whitespace.
     *
     * @returns a bool that rapresent the success or not of the parse.
     */
    virtual bool _parseRawCommandParams(std::string_view rawParams) = 0;

    /**
     * @brief Executes the functionality of the command.
     *
     * Write the execution result of the command inside @executeResult
     * in order to be visible outside the command itself.
     *
     * The implementation is up to the user.
     *
     * This method is called by @a Execute().
     */
    virtual void _execute(CmdInt_CommandExecutedResult& executeResult) = 0;

    /**
     * @brief See GetCommandName()
     */
    [[nodiscard]] virtual std::string_view _getCommandName() const = 0;

    /**
     * @brief See GetCommandParamsName()
     */
    [[nodiscard]] virtual std::string_view _getCommandParamsName() const = 0;

    CmdInt_UserContextData _userContextData = nullptr;

    std::string_view _rawCommand;
    std::string_view _commandRawParams;
};
#endif // COMMANDINTERPRETER_BASE_COMMAND_H