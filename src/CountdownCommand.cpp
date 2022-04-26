#include "CountdownCommand.h"

#include <iostream>

static bool _timeAlmostEqual(CmdInt_CountdownCommand::Seconds lhs, CmdInt_CountdownCommand::Seconds rhs) {
    auto constexpr epsilon = std::numeric_limits<CmdInt_CountdownCommand::Seconds>::epsilon();
    return abs(lhs - rhs) <= epsilon;
}

void CmdInt_CountdownCommand::_parseRawCommandParams(std::string_view rawParams) {
    CmdInt_countdown::GenericBaseCommand::_parseRawCommandParams(rawParams);
    _secondsRemainingMessageTimer = SECONDS_REMANING_MESSAGE_FREQUENCE;
    _firstExecution = true;
}

void CmdInt_CountdownCommand::_execute(CmdInt_InternalCommandExecutedResult& executeResult) {
    auto& countdown = std::get<Seconds>(_commandParams[0]);

    if (_firstExecution) {
        _firstExecution = false;
        _previousClockTime = Clock::now();

        // Output time not in range when the user has invoked the command
        // with a countdown that doesn't match the range (by design)
        // between 0 and 10 (inclusive).

        if (countdown < 0 || countdown > 10) {
            executeResult.IsExecutionCompleted = true;
            executeResult.CommandOutput = _createTimeNotInValidRangeMessage(GetRawCommandParams()).c_str();
            return;
        }
        // Output countdown complete immediately when the user has invoked
        // the command with a countdown of 0.
        if (_timeAlmostEqual(countdown, 0)) {
            executeResult.IsExecutionCompleted = true;
            executeResult.CommandOutput = _countdownCompleteMessage.data();
            return;
        }

        // Output the original value of countdown (the one set by the user).
        // We don't need to do anything else since this is the first iteration.
        executeResult.IsExecutionCompleted = false;
        executeResult.CommandOutput = _createTimeRemainingMessage(GetRawCommandParams()).c_str();
        return;
    }

    // Get current time.
    const ClockTime currentClockTime = Clock::now();

    // Time passed from one execution to the other.
    const std::chrono::duration<Seconds> timeDelta = currentClockTime - _previousClockTime;

    // Store current time to previous time for the next iteration.
    _previousClockTime = currentClockTime;

    // Decrease the countdown value.
    countdown -= timeDelta.count();

    // std::cout << "countdown value: " << countdown << '\n';

    // Countdown in progress.
    if (countdown > 0) {
        executeResult.IsExecutionCompleted = false;

        // Keep track of how many seconds are passed since the last message.
        _secondsRemainingMessageTimer -= timeDelta.count();

        // Each second we have to output the remaining time of the countdown (by design).
        if (_secondsRemainingMessageTimer <= 0) {
            // Reset the time remaining message timer to the designed frequency.
            _secondsRemainingMessageTimer = SECONDS_REMANING_MESSAGE_FREQUENCE;

            // Output how much this is remaining.
            // Cast to int in order to show only the seconds.
            const double roundCountdown = round(countdown);
            const int secondsRemaining = static_cast<int>(roundCountdown);
            executeResult.CommandOutput = _createTimeRemainingMessage(std::to_string(secondsRemaining)).c_str();
        }
    } else {
        // Countdown over.
        executeResult.IsExecutionCompleted = true;
        executeResult.CommandOutput = _countdownCompleteMessage.data();
    }
}

const std::string& CmdInt_CountdownCommand::_createTimeRemainingMessage(std::string_view countdown) {
    _timeRemainingMessge = countdown;
    _timeRemainingMessge.append(" seconds remaining");
    return _timeRemainingMessge;
}

const std::string& CmdInt_CountdownCommand::_createTimeNotInValidRangeMessage(std::string_view time) {
    _timeNotInValidRangeMessage = "valid countdown period of ";
    _timeNotInValidRangeMessage.append(time);
    _timeNotInValidRangeMessage.append(" seconds");
    return _timeNotInValidRangeMessage;
}