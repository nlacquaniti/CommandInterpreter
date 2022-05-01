#ifndef COMMANDINTERPRETER_UNRECOGNISED_COMMAND_H
#define COMMANDINTERPRETER_UNRECOGNISED_COMMAND_H

#include "BaseCommand.h"

#include <string>
#include <string_view>

/**
 * @brief Utility command to output "Unrecognised command: <provided command>"
 */
class CmdInt_UnrecognisedCommand final : public CmdInt_BaseCommand {
public:
    static constexpr std::string_view COMMAND_NAME{"unrecognised"};
    static constexpr std::string_view COMMAND_PARAM_NAMES{"..."};

private:
    bool _parseRawCommandParams(std::string_view rawParams) override;
    void _execute(CmdInt_CommandExecutedResult& executeResult) override;

    std::string_view _getCommandName() const { return COMMAND_NAME; }
    std::string_view _getCommandParamsName() const { return COMMAND_PARAM_NAMES; }

    std::string _unrecognisedCommandMessage{"Unrecognised command: "};
    std::string _rawParams;
};
#endif // COMMANDINTERPRETER_UNRECOGNISED_COMMAND_H