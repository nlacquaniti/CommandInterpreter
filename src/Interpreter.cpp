#include "CommandInterpreter/Interpreter.h"
#include "CommandProcessor.h"
#include "CommandUtility.h"
#include "Register.h"

void CmdInt_ProvideCommand(CmdInt_CommandSignature command, CmdInt_UserContextData userContextData) {
     // Removes the parameter from the input command in order to find the associated command class.
    const auto commandName = CmdInt_CommandUtility::RemoveRawCommandParams(command);

    // Finds the command instance to be processed later.
    const auto commandInstance = CmdInt_Register::GetCommand(commandName);
    if (commandInstance != nullptr) {
        // Initialize the command with the input command and the context injected from the user.
        commandInstance->InitCommand(command, userContextData);

        // Add the command instance to the queue in order to be processed.
        CmdInt_CommandProcessor::AddCommand(commandInstance);
    } else {
        // error.
    }
}

void CmdInt_ProvideCommandExecutedCallback(CmdInt_CommandExecutedFun callbackFun) {
    // Store the callback function injected by the user.
    CmdInt_CommandProcessor::SetOnCommandProcessedCallback(callbackFun);
}