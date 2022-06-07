#include "CommandProcessor.h"
#include "Commands/BaseCommand.h"

CmdInt_CommandProcessor::CommandQueue CmdInt_CommandProcessor::_queue;
CmdInt_CommandExecutedFun CmdInt_CommandProcessor::_onCommandProcessedCallback = nullptr;

void CmdInt_CommandProcessor::AddCommand(CommandPointer command) {
    if (command != nullptr) {
        _queue.emplace(command);
    }
}
void CmdInt_CommandProcessor::ProcessCommand() {
    if (_queue.empty()) {
        return;
    }

    const CmdInt_CommandExecutedResult execResult = _queue.front()->ExecuteCommand();

    if (_onCommandProcessedCallback != nullptr && execResult.CommandOutput != nullptr) {
        _onCommandProcessedCallback(execResult.CommandOutput, execResult.UserContextData);
    }

    if (execResult.IsExecutionCompleted) {
        _queue.pop();
    }
}

void CmdInt_CommandProcessor::Clear() {
    while (!_queue.empty()) {
        _queue.pop();
    }

    _onCommandProcessedCallback = nullptr;
}
