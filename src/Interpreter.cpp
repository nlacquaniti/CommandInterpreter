#include "CommandInterpreter/Interpreter.h"
#include "CommandProcessor.h"
#include "CommandUtility.h"
#include "Register.h"

void CmdInt_ProvideCommand(CmdInt_CommandSignature command, CmdInt_UserContextData userContextData) {
    const auto commandName = CmdInt_CommandUtility::RemoveRawCommandParams(command);
    const auto commandRef = CmdInt_Register::GetCommand(commandName);
    if (commandRef != nullptr) {
        commandRef->InitCommand(command, userContextData);
        CmdInt_CommandProcessor::AddCommand(commandRef);
    } else {
        // error.
    }
}

void CmdInt_ProvideCommandExecutedCallback(CmdInt_CommandExecutedFun callbackFun) {
    CmdInt_CommandProcessor::SetOnCommandProcessedCallback(callbackFun);
}