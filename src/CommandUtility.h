/**
 * @file CommandUtility.h
 * @brief Defines utility function to modify or parse the raw commands.
 */
#ifndef COMMANDINTERPRETER_COMMAND_UTILITY_H
#define COMMANDINTERPRETER_COMMAND_UTILITY_H

#include <algorithm>
#include <array>
#include <cassert>
#include <string>
#include <string_view>
#include <variant>

namespace CmdInt_CommandUtility {

/**
 * @brief Returns a command without the params.
 * (es. input: "countdown 5" output: "countdown").
 *
 * @param[in] command Source command.
 * @returns A string without the params.
 */
std::string_view RemoveRawCommandParams(std::string_view command);

/**
 * @brief Returns a command without the name.
 * (es. input: "countdown 5" output: "5").
 *
 * @param[in] command Source command.
 * @returns A string without the params
 */
std::string_view RemoveRawCommandName(std::string_view command);

/**
 * @brief Returns a count of params within source command.
 * (es. input: "countdown 5" output: "1", input" "command arg0 arg1 arg2" output : 3)
 *
 * @param[in] command Source command
 * @returns Params count as int
 */
size_t GetRawCommandParamsCount(std::string_view command);

/**
 * @brief Returns a count of params within raw params.
 * (es. input: "5" output: "1", input" "arg0 arg1 arg2" output : 3)
 *
 * @param[in] params Source command
 * @returns Params count as int
 */
size_t GetRawParamsCount(std::string_view params);

/**
 * @brief Returns an array of params extracted from the source command
 * (es. input: "countdown 5" output: ["5"], input"
 * "commandName arg0 arg1 arg2" output : ["arg0", "arg1", "arg2"])
 *
 * @param[in] _Size size of the array to return
 * @param[in] command Source command
 * @returns An array of params as string
 */
template <size_t _Size> //
std::array<std::string_view, _Size> SplitRawCommandParams(std::string_view command);

/**
 * @brief Assigns to the dest variant the type and value of the source string.
 * (es. input: <int>("5") output: ["5"], input: [idx:variantIdx, type: int, value: 5])
 *
 * @param[in] _CommandParamTypes types of the dest variant this is easly auto deduced by
 * the compiler, there's no need to specify it.
 * @param[in] source Raw param to convert and assign to dest variant.
 * @param[in] dest Variant to use as destination to the result of the source param conversion.
 */
template <typename... _CommandParamTypes> //
void ConvertRawCommandParam(std::string_view source, std::variant<_CommandParamTypes...>& dest);

/**
 * @brief Converts the source string to the specified type
 * (es. input: <int>"5" output: 5 as int).
 *
 *  N.B. The base version of this template is not implemented!
 *  Each type you like to convert should be implemented with a template
 *  sepecalization.
 *
 * @param[in] _CommandParamTypes destination type.
 * @param[in] source Raw param to convert and assign to dest.
 * @param[in] dest Destination variable for the conversion.
 */

template <typename _CommandParamType> //
static void _convertRawCommandParam_Impl(std::string_view source, _CommandParamType& dest);

template <size_t _Size> //
std::array<std::string_view, _Size> SplitRawCommandParams(std::string_view command) {
    // Init the params array with params count.
    std::array<std::string_view, _Size> params;

    // Assign the params to the output if necessary.
    for (auto& param : params) {
        const auto findResult = command.find(' ');

        // Found the last param.
        if (findResult == std::string_view::npos) {
            param = command;
        }

        // Store found param.
        auto output = command.substr(0, findResult);

        // Remove found param from command string.
        const auto findNextCharIdx = findResult + 1;
        command = command.substr(findNextCharIdx, command.size() - findNextCharIdx);

        param = output;
    }

    return params;
};

template <typename _CommandParamType> //
static void _convertRawCommandParam_Impl(std::string_view source, _CommandParamType& dest) {
    assert(false); // Convert type not implemented.
}

template <> //
void _convertRawCommandParam_Impl(std::string_view source, double& dest) {
    dest = std::atof(source.data());
}

template <> //
void _convertRawCommandParam_Impl(std::string_view source, std::string_view& dest) {
    dest = source;
}

template <typename... _CommandParamTypes> //
void ConvertRawCommandParam(std::string_view source, std::variant<_CommandParamTypes...>& dest) {
    auto convertVariantTypeLambda = [source, &dest](auto&& variant) {
        using _VariantType = std::decay_t<decltype(variant)>;
        _convertRawCommandParam_Impl(source, std::get<_VariantType>(dest));
    };

    std::visit(std::move(convertVariantTypeLambda), dest);
}

} // namespace CmdInt_CommandUtility
#endif // COMMANDINTERPRETER_COMMAND_UTILITY_H