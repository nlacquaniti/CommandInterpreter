#ifndef COMMANDINTERPRETER_UNRECOGNISED_COMMAND_H
#define COMMANDINTERPRETER_UNRECOGNISED_COMMAND_H

#include <GenericCommand.h>

#include <string>
#include <string_view>

GENERATE_COMMAND_GENERIC_CASS_TYPE(unrecognised, "command", std::string_view)
/**
 * @brief Utility command to output "Unrecognised command: <provided command>"
 */
class CmdInt_UnrecognisedCommand final : public CmdInt_unrecognised::GenericBaseCommand {
private:
    bool _parseRawCommandParams(std::string_view rawParams) override;
    void _execute(CmdInt_CommandExecutedResult& executeResult) override;

    std::string _unrecognisedCommandMessage{"Unrecognised command: "};
};
#endif // COMMANDINTERPRETER_UNRECOGNISED_COMMAND_H