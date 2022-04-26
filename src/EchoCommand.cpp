#include "EchoCommand.h"
#include "Register.h"

void CmdInt_EchoCommand::_execute(CmdInt_InternalCommandExecutedResult& executeResult) {
    const auto commandNameToFind = std::get<std::string_view>(_commandParams[0]);
    const auto commandFound = CmdInt_Register::GetCommand(commandNameToFind);
    if (commandFound != nullptr) {
        executeResult.CommandOutput = commandFound->GetCommandParamNames().data();
    }

    executeResult.IsExecutionCompleted = true;
}
