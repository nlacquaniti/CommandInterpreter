/**
 * @file Interpreter.h
 * @brief Defines functions used to process the commands provided to the
 * library.
 */
#ifndef COMMANDINTERPRETER_INTERPRETER_H
#define COMMANDINTERPRETER_INTERPRETER_H

#include "LibExport.h"
#include "Types.h"

/**
 * @brief The function pointer type for command executed callbacks.
 *
 * A command executed callback function has the following signature:
 * @code
 * void FunctionName(const char* commandOutput, void* userContextData).
 * @endcode
 *
 * @param[in] commandOutput The output of the executed command.\n
 *
 * @param[in] userContextData The context data provided by the user when
 * the command has been provided with this call.
 * @code
 * CmdInt_ProvideCommand(CmdInt_CommandOutput command, CmdInt_UserContextData userContextData).
 * @endcode
 */
CMDINT_API typedef void (*CmdInt_CommandExecutedFun)(CmdInt_CommandOutput commandOutput, CmdInt_UserContextData serContextData);

/**
 * @brief Takes over the command provided.
 *
 * Commands provided to this function are stored
 * like a queue (First In First Out).
 *
 * Provided commands can be execute with a call to
 * @code
 * CmdInt_Poll().
 * @endcode
 *
 * The user can be informed when a command has been
 * executed by providing a CmdInt_CommandExecutedFun callback here
 * @code
 * CmdInt_ProvideCommandExecutedCallback(CmdInt_CommandExecutedFun func)
 * @endcode
 *
 * @param[in] command To provide as a string.\n
 * Command requirements to be interpreted correctly:\n
 * 1) Format of the string: "command arg1 arg2".\n
 * 2) Command name and arguments must be delimited by whitespace.
 *    Quoted arguments and newlines are not supported.
 *
 * @param[in] userContextData This data is stored internally and
 * returned to the user via @a CmdInt_CommandExecutedFun callback.
 * The callback can be provided with a call to
 * @code
 * CmdInt_ProvideCommandExecutedCallback(CmdInt_CommandExecutedFun func)
 * @endcode
 */
CMDINT_API void CmdInt_ProvideCommand(CmdInt_CommandSignature command, CmdInt_UserContextData userContextData);

/**
 * @brief Takes over a provided user callback to be called
 * when any command has been executed.
 *
 * @param[in] callbackFun User defined function to call.\n
 * Signature:
 * @code
 * void FunctionName(CmdInt_CommandExecutedFun result).
 * @endcode
 * For more information about parameters see @a CmdInt_CommandExecutedFun.
 */
CMDINT_API void CmdInt_ProvideCommandExecutedCallback(CmdInt_CommandExecutedFun callbackFun);

#endif // COMMANDINTERPRETER_INTERPRETER_H
