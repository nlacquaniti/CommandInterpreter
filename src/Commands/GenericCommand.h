#ifndef COMMANDINTERPRETER_GENERIC_COMMAND_H
#define COMMANDINTERPRETER_GENERIC_COMMAND_H

#include "BaseCommand.h"
#include "CommandUtility.h"

#include <array>
#include <cassert>
#include <string_view>
#include <variant>

/**
 * @brief Utility macro that creates a command name, command para names
 * and an alias that can be used as template parameters for @a CmdInt_GenericCommand.
 *
 * Usecase:
 *
 * GENERATE_COMMAND_GENERIC_CASS_TYPE(shutdown, "seconds", double);
 *
 * class CmdInt_Shutdown : CmdInt_shutdown::GenericBaseCommand {};
 *
 * @param[in] CommandName Name of the command class that you're creating.
 * DON'T use a string the name should be passed without quotes. (es. shutdown).
 *
 * @param[in] CommandParamNames Name of the params as string.
 * In case of multiple params separate them with a whitespace.
 * (es. "seconds" or "seconds message").
 *
 * @param[in] __VA_ARGS__ Types of the params (es. double, std::string_view).
 */
#define GENERATE_COMMAND_GENERIC_CASS_TYPE(CommandName, CommandParamNames, ...)                                                                                \
    struct CmdInt_##CommandName {                                                                                                                           \
        constexpr static const char _commandName[] = #CommandName;                                                                                             \
        constexpr static const char _commandParamNames[] = CommandParamNames;                                                                                  \
        using GenericBaseCommand = CmdInt_GenericCommand<_commandName, _commandParamNames, __VA_ARGS__>;                                                       \
    };

/**
 * @brief Utility command template parent class.
 *
 * This class automatically generates the raw command name,
 * raw command names and the params array with the actual types.
 *
 * For example CmdInt_GenericCommand<shutdown, seconds, double>
 * generates COMMAND_NAME = "shutdown", COMMAND_PARAMS_NAME = "seconds"
 * CommandParamsArray = {index 0: double}.
 *
 * This class can be generated manually (not suggested) or you can use
 * the utility MACRO @a GENERATE_COMMAND_GENERIC_CASS_TYPE(CommandName, CommandParamsName, __VA_ARGS__).
 * By using the MACRO a new type gets created with this signature: CmdInt_CommandName::GenericBaseCommand.
 * See the MACRO for more informations.
 *
 * @param[in] _CommandName Name of the command as const char*
 * @param[in] _CommandParamNames Param names of the command as const char*
 * separated by a whitespace
 * @param[in] _CommandParamTypes Types of the params
 */
template <const char* _CommandName, const char* _CommandParamNames, typename... _CommandParamTypes> //
class CmdInt_GenericCommand : public CmdInt_BaseCommand {
public:
    using CommandParamsArray = std::array<std::variant<_CommandParamTypes...>, sizeof...(_CommandParamTypes)>;

    static constexpr std::string_view COMMAND_NAME{_CommandName};
    static constexpr std::string_view COMMAND_PARAM_NAMES{_CommandParamNames};

protected:
    CommandParamsArray _commandParams;

    bool _parseRawCommandParams(std::string_view rawParams) override;

private:
    [[nodiscard]] std::string_view _getCommandName() const override { return COMMAND_NAME; }
    [[nodiscard]] std::string_view _getCommandParamsName() const override { return COMMAND_PARAM_NAMES; }
};

template <const char* _CommandName, const char* _CommandParamNames, typename... _CommandParamTypes>
bool CmdInt_GenericCommand<_CommandName, _CommandParamNames, _CommandParamTypes...>::_parseRawCommandParams(std::string_view rawParams) {
    // Count of params that compose this command (for example "commandName arg0 arg1 arg2" yields a count of 3).
    constexpr auto commandParamTypesCount = sizeof...(_CommandParamTypes);
    
    // The number of raw params and type params ust be equal! Otherwise we can't parse them.
    if (CmdInt_CommandUtility::GetRawParamsCount(rawParams) == commandParamTypesCount) {
        // Split param string into an array of string to iterate them.
        const auto rawParamsArray = CmdInt_CommandUtility::SplitRawCommandParams<commandParamTypesCount>(rawParams);

        // Perform a conversion from string param to the actual type and value of the param (es. int 5).
        // The result of this conversion is stored inside _commandParams.
        // The order of the input params is preserved.
        for (size_t i = 0; i < commandParamTypesCount; ++i) {
            CmdInt_CommandUtility::ConvertRawCommandParam(rawParamsArray[i], _commandParams[i]);
        }
        
        return true;
    }

    return false;
}
#endif // COMMANDINTERPRETER_GENERIC_COMMAND_H
