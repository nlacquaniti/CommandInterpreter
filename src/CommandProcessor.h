#ifndef COMMANDINTERPRETER_COMMAND_PROCESSOR_H
#define COMMANDINTERPRETER_COMMAND_PROCESSOR_H

#include "CommandInterpreter/Interpreter.h"

#include <memory>
#include <queue>

class CmdInt_BaseCommand;

class CmdInt_CommandProcessor {
public:
    using CommandPointer = std::shared_ptr<CmdInt_BaseCommand>;

    static void AddCommand(CommandPointer command);
    static void ProcessCommand();

    static void SetOnCommandProcessedCallback(CmdInt_CommandExecutedFun callback) {
        if (callback != nullptr) {
            _onCommandProcessedCallback = callback;
        }
    }

private:
    using CommandQueue = std::queue<CommandPointer>;

    static CommandQueue _queue;
    static CmdInt_CommandExecutedFun _onCommandProcessedCallback;
};
#endif // COMMANDINTERPRETER_COMMAND_PROCESSOR_H