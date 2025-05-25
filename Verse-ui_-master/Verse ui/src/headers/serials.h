#include <windows.h>
#include <string>
#include <iostream>

std::string GetBiosSerialNumber() {
    std::string serialNumber;
    std::string command = "wmic bios get serialnumber";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        serialNumber += buffer;
    }
    _pclose(pipe);

    serialNumber.erase(0, serialNumber.find_first_not_of(" \t\r\n"));
    serialNumber.erase(serialNumber.find_last_not_of(" \t\r\n") + 1);

    return serialNumber;
}

std::string GetChassisSerialNumber() {
    std::string serialNumber;
    std::string command = "wmic baseboard get serialnumber";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        serialNumber += buffer;
    }
    _pclose(pipe);

    serialNumber.erase(0, serialNumber.find_first_not_of(" \t\r\n"));
    serialNumber.erase(serialNumber.find_last_not_of(" \t\r\n") + 1);

    return serialNumber;
}

std::string GetBaseboardModel() {
    std::string model;
    std::string command = "wmic baseboard get Product";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        model += buffer;
    }
    _pclose(pipe);

    model.erase(0, model.find_first_not_of(" \t\r\n"));
    model.erase(model.find_last_not_of(" \t\r\n") + 1);

    return model;
}

std::string GetCpuModel() {
    std::string model;
    std::string command = "wmic cpu get Name";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        model += buffer;
    }
    _pclose(pipe);

    model.erase(0, model.find_first_not_of(" \t\r\n"));
    model.erase(model.find_last_not_of(" \t\r\n") + 1);

    return model;
}

bool IsTpmEnabled() {
    std::string command = "powershell -Command \"Get-TPM | Select-Object -Property TpmEnabled\"";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return false;
    }

    char buffer[256];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    _pclose(pipe);

    return result.find("True") != std::string::npos;
}

bool IsWiFiEnabled() {
    std::string command = "powershell -Command \"Get-NetAdapter | Where-Object { $_.InterfaceDescription -match '802.11n' } | Select-Object -Property Name, Status\"";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return false;
    }

    char buffer[256];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    _pclose(pipe);

    return result.find("Up") != std::string::npos;
}

bool IsBluetoothEnabled() {
    std::string command = "powershell -Command \"Get-PnpDevice -Class Bluetooth | Select-Object -Property Name, Status\"";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return false;
    }

    char buffer[256];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    _pclose(pipe);

    return result.find("OK") != std::string::npos;
}

std::string GetDisks() {
    std::string command = "wmic diskdrive get InterfaceType";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "Error executing the WMIC command";
    }

    char buffer[128];
    std::map<std::string, int> interfaceCount;
    bool isFirstLine = true;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        std::string line(buffer);
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (!line.empty()) {
            interfaceCount[line]++;
        }
    }
    _pclose(pipe);

    std::string result;
    for (const auto& pair : interfaceCount) {
        if (!result.empty()) {
            result += ", ";
        }
        result += std::to_string(pair.second) + " " + pair.first + " Disks";
    }

    return result.empty() ? "No disk drives found" : result;
}


std::string GetNetworkAdapter() {
    std::vector<std::string> keywords = { "Realtek", "Another" };

    std::string adapterName;
    std::string command = "wmic nic get Name";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        std::string line = buffer;
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        std::string lineLower = line;
        std::transform(lineLower.begin(), lineLower.end(), lineLower.begin(), ::tolower);

        bool found = false;
        for (const auto& keyword : keywords) {
            std::string keywordLower = keyword;
            std::transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

            if (lineLower.find(keywordLower) != std::string::npos) {
                found = true;
                break;
            }
        }

        if (found) {
            adapterName = line;
            break;
        }
    }
    _pclose(pipe);

    return adapterName;
}


std::string GetBaseboardManufacturer() {
    std::string manufacturer;
    std::string command = "wmic baseboard get Manufacturer";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        manufacturer += buffer;
    }
    _pclose(pipe);

    manufacturer.erase(0, manufacturer.find_first_not_of(" \t\r\n"));
    manufacturer.erase(manufacturer.find_last_not_of(" \t\r\n") + 1);

    return manufacturer;
}

std::string GetCpuSerialNumber() {
    std::string serialNumber;
    std::string command = "wmic cpu get ProcessorId";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        serialNumber += buffer;
    }
    _pclose(pipe);

    serialNumber.erase(0, serialNumber.find_first_not_of(" \t\r\n"));
    serialNumber.erase(serialNumber.find_last_not_of(" \t\r\n") + 1);

    return serialNumber;
}

std::string GetMacAddress() {
    std::string macAddress;
    std::string command = "getmac";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool found = false;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        std::string line(buffer);
        std::size_t pos = line.find('-');
        if (pos != std::string::npos) {
            macAddress = line.substr(0, 17);
            found = true;
            break;
        }
    }
    _pclose(pipe);

    if (!found) {
        return "";
    }

    macAddress.erase(0, macAddress.find_first_not_of(" \t\r\n"));
    macAddress.erase(macAddress.find_last_not_of(" \t\r\n") + 1);

    return macAddress;
}

std::string GetMoboSerialNumber() {
    std::string serialNumber;
    std::string command = "wmic baseboard get serialnumber";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        serialNumber += buffer;
    }
    _pclose(pipe);

    serialNumber.erase(0, serialNumber.find_first_not_of(" \t\r\n"));
    serialNumber.erase(serialNumber.find_last_not_of(" \t\r\n") + 1);

    return serialNumber;
}

std::string GetSystemUUID() {
    std::string uuid;
    std::string command = "wmic csproduct get UUID";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    char buffer[128];
    bool isFirstLine = true;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        uuid += buffer;
    }
    _pclose(pipe);

    uuid.erase(0, uuid.find_first_not_of(" \t\r\n"));
    uuid.erase(uuid.find_last_not_of(" \t\r\n") + 1);

    return uuid;
}