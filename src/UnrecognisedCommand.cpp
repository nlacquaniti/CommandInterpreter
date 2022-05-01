#include "UnrecognisedCommand.h"

bool CmdInt_UnrecognisedCommand::_parseRawCommandParams(std::string_view rawParams) {
    _rawParams = rawParams;
    return true;
}

void CmdInt_UnrecognisedCommand::_execute(CmdInt_CommandExecutedResult& executeResult) {
    _unrecognisedCommandMessage = _unrecognisedCommandMessage + _rawParams;
    executeResult.CommandOutput = _unrecognisedCommandMessage.c_str();

    executeResult.IsExecutionCompleted = true;
}
