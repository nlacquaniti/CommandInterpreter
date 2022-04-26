#ifndef COMMANDINTERPRETER_COUNTDOWN_COMMAND_H
#define COMMANDINTERPRETER_COUNTDOWN_COMMAND_H

#include "GenericCommand.h"

#include <chrono>
#include <string>
#include <string_view>

GENERATE_COMMAND_GENERIC_CASS_TYPE(countdown, "seconds", double);
class CmdInt_CountdownCommand final : public CmdInt_countdown::GenericBaseCommand {
public:
    using Clock = std::chrono::high_resolution_clock;
    using ClockTime = Clock::time_point;
    using Seconds = double;

private:
    void _parseRawCommandParams(std::string_view rawParams) override;
    void _execute(CmdInt_InternalCommandExecutedResult& executeResult) override;

    const std::string& _createTimeRemainingMessage(std::string_view countdown);
    const std::string& _createTimeNotInValidRangeMessage(std::string_view time);

    static constexpr Seconds SECONDS_REMANING_MESSAGE_FREQUENCE = 1;
    Seconds _secondsRemainingMessageTimer = SECONDS_REMANING_MESSAGE_FREQUENCE;
    ClockTime _previousClockTime;

    std::string _timeRemainingMessge;
    std::string _timeNotInValidRangeMessage;
    std::string_view _countdownCompleteMessage{"Countdown completed"};

    bool _firstExecution = true;
};
#endif // COMMANDINTERPRETER_COUNTDOWN_COMMAND_H