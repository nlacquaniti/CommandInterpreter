#ifndef COMMANDINTERPRETER_COUNTDOWN_COMMAND_H
#define COMMANDINTERPRETER_COUNTDOWN_COMMAND_H

#include "GenericCommand.h"

#include <chrono>
#include <string>
#include <string_view>

GENERATE_COMMAND_GENERIC_CASS_TYPE(countdown, "seconds", double);
/**
 * @brief Counts down from the given number of seconds, logging a message each second. The
 * number of seconds is specified by exactly one argument.
 * The valid range for the number of seconds to count down is between 0 and 10 inclusive.
 *
 * When the command is first processed, "<n> seconds remaining" is returned.
 * The same message is returned each seconds while the number of seconds remaining is greater than zero,
 * and is also logged on console.
 *
 * Once <n> reaches zero, "Countdown complete" is returned. If the number of seconds
 * originally provided to the command is zero, this message is returned immediately.
 */
class CmdInt_CountdownCommand final : public CmdInt_countdown::GenericBaseCommand {
public:
    using Clock = std::chrono::high_resolution_clock;
    using ClockTime = Clock::time_point;
    using Seconds = double;

private:
    bool _parseRawCommandParams(std::string_view rawParams) override;
    void _execute(CmdInt_CommandExecutedResult& executeResult) override;

    const std::string& _createTimeRemainingMessage(std::string_view countdown);
    const std::string& _createTimeNotInValidRangeMessage(std::string_view time);

    static constexpr Seconds SECONDS_REMANING_MESSAGE_FREQUENCE = 1;
    Seconds _secondsRemainingMessageTimer = SECONDS_REMANING_MESSAGE_FREQUENCE;
    ClockTime _previousClockTime;

    std::string _timeRemainingMessge;
    std::string _timeNotInValidRangeMessage;
    std::string_view _countdownCompleteMessage{"Countdown complete"};

    bool _isFirstExecution = true;
    bool _bParsingSuccessful = true;
};
#endif // COMMANDINTERPRETER_COUNTDOWN_COMMAND_H