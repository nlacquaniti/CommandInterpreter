#include "CommandInterpreter/Interpreter.h"
#include "CommandProcessor.h"
#include "CommandUtility.h"
#include "Register.h"
#include "UnrecognisedCommand.h"

#include <string>

void CmdInt_ProvideCommand(CmdInt_CommandSignature command, CmdInt_UserContextData userContextData) {
    std::string_view commandName = command;

    // Removes the parameter from the input command in order to find the associated command class.
    if (CmdInt_CommandUtility::GetRawCommandParamsCount(command) > 0) {
        commandName = CmdInt_CommandUtility::RemoveRawCommandParams(command);
    }

    // Finds the command instance to be processed later.
    auto commandInstance = CmdInt_Register::GetCommand(commandName);

    // Initialize the command with the input command and the context injected from the user.
    // The command init can fail if the params passed by the user are invalid.
    // (es giving a command without parameters even if they're needed).
    // If the command fails we provide a fallback called unrecognised command
    // that outputs to the user "Unrecognised command: <x>"
    if (commandInstance == nullptr || !commandInstance->InitCommand(command, userContextData)) {
        // Fallback to safe command.
        commandInstance = CmdInt_Register::GetCommand(CmdInt_UnrecognisedCommand::COMMAND_NAME);
        assert(commandInstance != nullptr);
        const std::string unrecognisedCommand(std::string(CmdInt_UnrecognisedCommand::COMMAND_NAME) + ' ' + command);
        const bool bUnrecognisedInit = commandInstance->InitCommand(unrecognisedCommand, userContextData);
        assert(bUnrecognisedInit);
    }

    CmdInt_CommandProcessor::AddCommand(commandInstance);
}

void CmdInt_ProvideCommandExecutedCallback(CmdInt_CommandExecutedFun callbackFun) {
    // Store the callback function injected by the user.
    CmdInt_CommandProcessor::SetOnCommandProcessedCallback(callbackFun);
}