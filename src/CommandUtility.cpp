#include "CommandUtility.h"

#include <BaseCommand.h>
#include <iostream>

namespace CmdInt_CommandUtility {
std::string_view RemoveRawCommandParams(std::string_view command) {
    const auto whiteSpaceIdx = command.find_first_of(' ');
    if (whiteSpaceIdx != std::string_view::npos) {
        return command.substr(0, whiteSpaceIdx);
    }

    return {};
}

std::string_view RemoveRawCommandName(std::string_view command) {
    const auto whiteSpaceIdx = command.find_first_of(' ');
    if (whiteSpaceIdx != std::string_view::npos) {
        const auto nextCharFromWhiteSpace = whiteSpaceIdx + 1;
        return command.substr(nextCharFromWhiteSpace, command.size() - nextCharFromWhiteSpace);
    }
    return {};
}

size_t GetRawCommandParamsCount(std::string_view params) {
    if (params.empty()) {
        return 0;
    }

    return std::count_if(params.cbegin(), params.cend(), [](const auto element) {
        return element == ' '; //
    }) + 1;
}
} // namespace CmdInt_CommandUtility