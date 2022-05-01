#include "EchoCommand.h"
#include "Register.h"

void CmdInt_EchoCommand::_execute(CmdInt_CommandExecutedResult& executeResult) {
    const auto commandNameToFind = std::get<std::string_view>(_commandParams[0]);

    // If the command has been found the output is the raw command names of it,
    // otherwise the output is an empty string.
    const auto commandFound = CmdInt_Register::GetCommand(commandNameToFind);
    if (commandFound != nullptr) {
        executeResult.CommandOutput = commandFound->GetCommandParamNames().data();
    } else {
        // Base output.
        executeResult.CommandOutput = "";
    }

    executeResult.IsExecutionCompleted = true;
}
