#include "UnrecognisedCommand.h"

bool CmdInt_UnrecognisedCommand::_parseRawCommandParams([[maybe_unused]] std::string_view rawParams) {
    // This command doesn't need to parse the params because the user input is
    // the param itself (es "countdown" output: "Unrecognised command: countdown".
    return true;
}

void CmdInt_UnrecognisedCommand::_execute(CmdInt_CommandExecutedResult& executeResult) {
    _unrecognisedCommandMessage = _unrecognisedCommandMessage + GetRawCommand().data();
    executeResult.CommandOutput = _unrecognisedCommandMessage.c_str();

    executeResult.IsExecutionCompleted = true;
}
