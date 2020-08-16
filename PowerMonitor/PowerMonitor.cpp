#include "pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;

[StructLayoutAttribute(LayoutKind::Sequential)]
ref class PStat {
public:
    System::Byte ACLineStatus;
    System::Byte BatteryFlag;
    System::Byte BatteryLifePercent;
    System::Byte Reserved1;
    System::UInt32 BatteryLifeTime;
    System::UInt32 BatteryFullLifeTime;
};

// Define the BOOL type
typedef int BOOL;

// Prototype for the function
[DllImport("Kernel32.dll", CharSet = CharSet::Auto)] BOOL GetSystemPowerStatus(PStat^ ps);


int main(array<System::String ^> ^args)
{
    Console::WriteLine("Power Status Test");
    PStat^ ps = gcnew PStat();

    BOOL b = GetSystemPowerStatus(ps);
    Console::WriteLine("Got status, return was {0}", b);

    // Report on the AC line status
    Console::Write("AC line power status is ");
    switch (ps->ACLineStatus) {
    case 0:
        Console::WriteLine("'off'");
        break;
    case 1:
        Console::WriteLine("'on'");
        break;
    case 255:
        Console::WriteLine("'unknown'");
        break;
    }

    // Report on the battery status
    Console::Write("Battery charge status is ({0})", ps->BatteryFlag);
    if (ps->BatteryFlag & 1)
        Console::Write(" 'high'");
    if (ps->BatteryFlag & 2)
        Console::Write(" 'low'");
    if (ps->BatteryFlag & 4)
        Console::Write(" 'critical'");
    if (ps->BatteryFlag & 8)
        Console::Write(" 'charging'");
    if (ps->BatteryFlag & 128)
        Console::Write(" 'no system battery'");
    Console::WriteLine();

    // What's the percentage charge left in the battery?
    // A value of 255 means unknown
    if (ps->BatteryLifePercent = 255)
        Console::WriteLine("Battery Life is unknown");
    else
        Console::WriteLine("Battery life is {0}%", ps->BatteryLifePercent);

    // How many seconds battery life is left?
    if (ps->BatteryLifeTime == -1)
        Console::WriteLine("Battery life in seconds: Unkown");
    else
        Console::WriteLine("Battery seconds remaining: {0} secs", ps->BatteryLifeTime);


    return 0;
}
