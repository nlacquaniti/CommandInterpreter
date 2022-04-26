#ifndef COMMANDINTERPRETER_BASE_COMMAND_H
#define COMMANDINTERPRETER_BASE_COMMAND_H

#include "CommandInterpreter/Types.h"
#include "CommandUtility.h"

#include <string_view>

struct CmdInt_InternalCommandExecutedResult {
    CmdInt_InternalCommandExecutedResult(CmdInt_UserContextData userContextData)
        : CommandOutput(nullptr)
        , UserContextData(userContextData)
        , IsExecutionCompleted(true) {}

    CmdInt_CommandOutput CommandOutput;
    CmdInt_UserContextData UserContextData;
    bool IsExecutionCompleted;
};

class CmdInt_BaseCommand {
public:
    virtual ~CmdInt_BaseCommand() = default;

    void InitCommand(std::string_view command, CmdInt_UserContextData userContextData) {
        _userContextData = userContextData;
        _commandRawParams = CmdInt_CommandUtility::RemoveRawCommandName(command);
        _parseRawCommandParams(_commandRawParams);
    }

    CmdInt_InternalCommandExecutedResult ExecuteCommand() {
        CmdInt_InternalCommandExecutedResult result(_userContextData);
        _execute(result);
        return result;
    }

    [[nodiscard]] std::string_view GetRawCommandParams() const { return _commandRawParams; }

    [[nodiscard]] std::string_view GetCommandName() const { return _getCommandName(); }
    [[nodiscard]] std::string_view GetCommandParamNames() const { return _getCommandParamsName(); }

private:
    CmdInt_UserContextData _userContextData = nullptr;

    std::string_view _commandRawParams;

    virtual void _parseRawCommandParams(std::string_view rawParams) = 0;
    virtual void _execute(CmdInt_InternalCommandExecutedResult& executeResult) = 0;

    [[nodiscard]] virtual std::string_view _getCommandName() const = 0;
    [[nodiscard]] virtual std::string_view _getCommandParamsName() const = 0;
};
#endif // COMMANDINTERPRETER_BASE_COMMAND_H