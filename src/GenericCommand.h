#ifndef COMMANDINTERPRETER_GENERIC_COMMAND_H
#define COMMANDINTERPRETER_GENERIC_COMMAND_H

#include "BaseCommand.h"
#include "CommandUtility.h"

#include <array>
#include <cassert>
#include <string_view>
#include <variant>

#define GENERATE_COMMAND_GENERIC_CASS_TYPE(CommandName, CommandParamNames, ...)                                                                                \
    namespace CmdInt_##CommandName {                                                                                                                           \
        constexpr static const char _commandName[] = #CommandName;                                                                                             \
        constexpr static const char _commandParamNames[] = CommandParamNames;                                                                                  \
        using GenericBaseCommand = CmdInt_GenericCommand<_commandName, _commandParamNames, __VA_ARGS__>;                                                       \
    }

template <const char* _CommandName, const char* _CommandParamNames, typename... _CommandParamTypes> //
class CmdInt_GenericCommand : public CmdInt_BaseCommand {
public:
    using CommandParamsArray = std::array<std::variant<_CommandParamTypes...>, sizeof...(_CommandParamTypes)>;

    static constexpr std::string_view COMMAND_NAME{_CommandName};
    static constexpr std::string_view COMMAND_PARAM_NAMES{_CommandParamNames};

protected:
    CommandParamsArray _commandParams;

    void _parseRawCommandParams(std::string_view rawParams) override;

private:
    [[nodiscard]] std::string_view _getCommandName() const override { return COMMAND_NAME; }
    [[nodiscard]] std::string_view _getCommandParamsName() const override { return COMMAND_PARAM_NAMES; }
};

template <const char* _CommandName, const char* _CommandParamNames, typename... _CommandParamTypes>
void CmdInt_GenericCommand<_CommandName, _CommandParamNames, _CommandParamTypes...>::_parseRawCommandParams(std::string_view rawParams) {
    // Count of params that compose this command (for example "commandName arg0 arg1 arg2" yield a count of 3).
    constexpr auto commandParamTypesCount = sizeof...(_CommandParamTypes);

    if constexpr (commandParamTypesCount != 0) {
        // The number of raw params and type params ust be equal! Otherwise we can't parse them.
        assert(CmdInt_CommandUtility::GetRawCommandParamsCount(rawParams) == commandParamTypesCount);

        // Split param string into an array of string to iterate them.
        const auto rawParamsArray = CmdInt_CommandUtility::SplitRawCommandParams<commandParamTypesCount>(rawParams);

        // Perform a conversion from string param to the actual type and value of the param (es. int 5).
        // The result of this conversion is stored inside _commandParams.
        // The order of the input params is preserved.
        for (size_t i = 0; i < commandParamTypesCount; ++i) {
            CmdInt_CommandUtility::ConvertRawCommandParam(rawParamsArray[i], _commandParams[i]);
        }
    }
}
#endif // COMMANDINTERPRETER_GENERIC_COMMAND_H
