#include "CommandInterpreter/Control.h"
#include "CommandProcessor.h"
#include "CountdownCommand.h"
#include "EchoCommand.h"
#include "Register.h"

void CmdInt_Initialise() {
    // Initialise your resources here.
    CmdInt_Register::AddCommand<CmdInt_EchoCommand>();
    CmdInt_Register::AddCommand<CmdInt_CountdownCommand>();
}

void CmdInt_ShutDown() {
    // Clean up your resources here.
    CmdInt_CommandProcessor::Clear();
}

void CmdInt_Poll() {
    // Perform any processing here
    CmdInt_CommandProcessor::ProcessCommand();
}
