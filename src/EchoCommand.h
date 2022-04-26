#ifndef COMMANDINTERPRETER_ECHO_COMMAND_H
#define COMMANDINTERPRETER_ECHO_COMMAND_H

#include "GenericCommand.h"

#include <string_view>

GENERATE_COMMAND_GENERIC_CASS_TYPE(echo, "command", std::string_view);
class CmdInt_EchoCommand final : public CmdInt_echo::GenericBaseCommand {
private:
    void _execute(CmdInt_InternalCommandExecutedResult& executeResult) override;
};
#endif // COMMANDINTERPRETER_ECHO_COMMAND_H