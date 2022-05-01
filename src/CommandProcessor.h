#ifndef COMMANDINTERPRETER_COMMAND_PROCESSOR_H
#define COMMANDINTERPRETER_COMMAND_PROCESSOR_H

#include "CommandInterpreter/Interpreter.h"

#include <memory>
#include <queue>

class CmdInt_BaseCommand;

/**
 * @brief Executes the provided commands in a queue sequence.
 *
 * Once that the command execution is over it calls the provieded
 * callback with the output of the command.
 */
class CmdInt_CommandProcessor {
public:
    using CommandPointer = std::shared_ptr<CmdInt_BaseCommand>;

    /**
     * @brief Add a command to the process list.
     * The provided commands are stored in a queue order.
     *
     * @param[in] command Command to store.
     */
    static void AddCommand(CommandPointer command);

    /**
     * @brief Executes the first command of the queue.
     *
     * Each call to this method calls a command execution,
     * and when the command execution is over it is removed
     * from the queue.
     *
     * If the command outputs a message the callback provided
     * by @a SetOnCommandProcessedCallback is invoked.
     */
    static void ProcessCommand();

    /**
     * @brief Clears the added commands and
     * the command processed callback.
     */
    static void Clear();

    /**
     * @brief Stores a callback to call each time a processed
     * command outputs a message.
     *
     * @param[in] callback Function pointer to invoke.
     */
    static void SetOnCommandProcessedCallback(CmdInt_CommandExecutedFun callback) {
        if (callback != nullptr) {
            _onCommandProcessedCallback = callback;
        }
    }

    /**
     * @brief Returns the command executed callback
     * provided by the user if any.
     *
     * @returns a pointer to the user defined command callback func.
     */
    static CmdInt_CommandExecutedFun GetOnCommandProcessedCallback() { return _onCommandProcessedCallback; }

private:
    using CommandQueue = std::queue<CommandPointer>;

    static CommandQueue _queue;
    static CmdInt_CommandExecutedFun _onCommandProcessedCallback;
};
#endif // COMMANDINTERPRETER_COMMAND_PROCESSOR_H