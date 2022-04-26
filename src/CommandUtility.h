#ifndef COMMANDINTERPRETER_COMMAND_UTILITY_H
#define COMMANDINTERPRETER_COMMAND_UTILITY_H

#include <algorithm>
#include <array>
#include <cassert>
#include <string_view>
#include <variant>

namespace CmdInt_CommandUtility {
std::string_view RemoveRawCommandParams(std::string_view command);

std::string_view RemoveRawCommandName(std::string_view command);

size_t GetRawCommandParamsCount(std::string_view params);

template <size_t _Size> //
std::array<std::string_view, _Size> SplitRawCommandParams(std::string_view command);

template <typename... _CommandParamTypes> //
void ConvertRawCommandParam(std::string_view source, std::variant<_CommandParamTypes...>& dest);

template <typename _CommandParamType> //
static void _convertRawCommandParam_Impl(std::string_view source, _CommandParamType& dest);

template <size_t _Size> //
std::array<std::string_view, _Size> SplitRawCommandParams(std::string_view command) {
    // Init the params array with params count.
    std::array<std::string_view, _Size> params;

    // Assign the params to the output if necessary.
    std::transform(params.cbegin(), params.cend(), params.begin(), [&command](auto& param) {
        const auto findResult = command.find(' ');

        // Found the last param.
        if (findResult == std::string_view::npos) {
            return command;
        }

        // Store found param.
        auto output = command.substr(0, findResult);

        // Remove found param from command string.
        const auto findNextCharIdx = findResult + 1;
        command = command.substr(findNextCharIdx, command.size() - findNextCharIdx);

        return output;
    });

    return params;
};

template <typename _CommandParamType> //
static void _convertRawCommandParam_Impl(std::string_view source, _CommandParamType& dest) {
    assert(false); // Convert type not implemented.
}

template <> //
void _convertRawCommandParam_Impl(std::string_view source, int& dest) {
    dest = std::atoi(source.data());
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