//######## ########  ########  ##    ##  ########  ########  ###     ##  ########        ######## ########  ########            ##      ##        ##              ########  ##    ##  ########        #######   ########      ##      ##    ##  ########  ##    ##        ########  ###     ##        ########  ###     ##  ########        ##  ##  ##  ########  ########  ##        #######           
//##          ##     ##        ##    ##     ##        ##     ####    ##  ##              ##       ##    ##  ##    ##           ####     ##        ##                 ##     ##    ##  ##              ##    ##  ##           ####     ##    ##     ##     ##    ##           ##     ####    ##           ##     ####    ##  ##              ##  ##  ##  ##    ##  ##    ##  ##        ##    ##      
//#####       ##     ##  ####  ########     ##        ##     ## ##   ##  ##  ####        #####    ##    ##  #######           ##  ##    ##        ##                 ##     ########  #######         #######   #######     ##  ##    ##    ##     ##      ##  ##            ##     ## ##   ##           ##     ## ##   ##  #######         ##  ##  ##  ##    ##  #######   ##        ##    ##      
//##          ##     ##    ##  ##    ##     ##        ##     ##  ##  ##  ##    ##        ##       ##    ##  ##  ##           ##    ##   ##        ##                 ##     ##    ##  ##              ##    ##  ##         ##    ##   ##    ##     ##       ####             ##     ##   ## ##           ##     ##  ##  ##  ##              ##  ##  ##  ##    ##  ##  ##    ##        ##    ## 
//##          ##     ##    ##  ##    ##     ##        ##     ##   ## ##  ##    ##        ##       ##    ##  ##   ##         ##########  ##        ##                 ##     ##    ##  ##              ##    ##  ##        ##########  ##    ##     ##        ##              ##     ##   ## ##           ##     ##   ## ##  ##               ########   ##    ##  ##   ##   ##        ##    ##
//##       ########  ########  ##    ##     ##     ########  ##    ####  ########        ##       ########  ##    ##        ##      ##  ########  ########           ##     ##    ##  ########        #######   ########  ##      ##  ########     ##        ##           ########  ##    ####           ##     ##    ####  ########          ##  ##    ########  ##    ##  ########  #######                                                                            
#include <windows.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>
#include <shellapi.h>
#include <aclapi.h>
#include <winreg.h>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <cstdlib> 
#include <fstream>
#include <shlobj.h>
#include <numeric>
#include "resource.h"
#include <tchar.h>
#include <shlobj.h>
#include <algorithm>
#include <sddl.h>
#include <sstream>
#include <cstdint> 

// 同步互斥量
std::mutex consoleMutex;
// 统计变量
std::atomic<int> totalCount(0);
std::atomic<int> successCount(0);
std::atomic<int> failureCount(0);

// 声明一大堆函数
void reg1();
void reg2();
void reg3();
void reg4();
void reg5();
void reg6();
void reg7();
void reg8();
void reg9();
void reg10();
void reg11();
void reg12();
void reg13();
void reg14();
void reg15();
void reg16();
void reg17();
void reg18();
void reg19();
void reg20();
void reg21();
void reg22();
void reg23();
void reg24();
void reg25();
void reg26();
void reg27();
void reg28();
void reg29();
void reg30();
void reg31();
void reg32();
void reg33();
void reg34();
void reg35();
void InstallFontForAllUsers(const std::wstring& fontFilePath);
void SetConsoleFont();
void AdjustFontSize(int fontsize111);
void font111();
bool admin();
bool isTrustedInstaller();
bool isSystemUser();
void reboot_admin();
void TrustedInstaller();

void SetConsoleWindowSize() {
    // 句柄
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        // 当前窗口的样式
    LONG originalStyle = GetWindowLong(hwnd, GWL_STYLE);
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    // 修改窗口样式，全屏模式
    SetWindowLong(hwnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwnd, SW_MAXIMIZE);
    // 恢复窗口化
    SetWindowLong(hwnd, GWL_STYLE, originalStyle);
    ShowWindow(hwnd, SW_RESTORE);
    // 再次全屏
    SetWindowLong(hwnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwnd, SW_MAXIMIZE);
    }
}

namespace fs = std::filesystem;

// 全局调试开关，设置为 true 以启用全局调试输出，设置为 false 以禁用全局调试输出。
bool debugMode = false;
// 全局终焉之律者权限模式开关， (带有TrustedInstaller令牌的SYSTEM用户组), 设置为 true 以启用终焉之律者权限模式，设置为 false 以使用普通天命账户运行。
bool TrustedInstallerMode = false;

// 调试输出宏定义
#define DEBUG_PRINT(msg) if (debugMode) { std::wcout << msg << std::endl; }
#define DEBUG_OUT(msg) if (debugMode) { std::wcout << msg; }
#define DEBUG_ERROR(msg) if (debugMode) { std::wcerr << msg << std::endl; }

// 权限提升程序相关
const std::wstring RT_DATA000;
int RT_DATA111;
HMODULE g_hModule = 0;
HRSRC g_hResource = 0;
HGLOBAL g_hGlobal =0;
DWORD g_resourceSize =0;
WORD g_resID =0;
std::wstring DEVICE;


// 确保目录存在
bool EnsureDirectoryExists(const std::wstring& directoryPath) {
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
        return true;
    }
    return fs::create_directories(directoryPath);
}

// 提取RT_RCDATA
bool ExtractRCDATAResourceToFile(HMODULE hModule, const std::wstring& filePath, WORD resID) {
    // 确保目录存在
    if (!EnsureDirectoryExists(filePath.substr(0, filePath.find_last_of(L'\\')))) {
    }

    // 创建文件
    HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to create file: " << filePath);
    }

    // 查找资源
    HRSRC hResource = FindResourceW(hModule, MAKEINTRESOURCEW(resID), L"RT_RCDATA");
    if (!hResource) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to find resource with ID: " << resID);
        CloseHandle(hFile);
    }

    // 加载资源
    HGLOBAL hGlobal = LoadResource(hModule, hResource);
    if (!hGlobal) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to load resource with ID: " << resID);
        CloseHandle(hFile);
    } else {

    }

    // 锁定资源
    void* pResourceData = LockResource(hGlobal);
    if (!pResourceData) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to lock resource with ID: " << resID);
        CloseHandle(hFile);;
    } else {
        
    }

    // 获取资源大小
    DWORD resourceSize = SizeofResource(hModule, hResource);

    // 写入文件
    DWORD dwWritten = 0;
    BOOL result = WriteFile(hFile, pResourceData, resourceSize, &dwWritten, NULL);
    if (!result || dwWritten != resourceSize) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to write resource to file: " << filePath);
        CloseHandle(hFile);
    } else {
        
    }

    HMODULE g_hModule = hModule;
    WORD g_resID = resID;
    HRSRC g_hResource = hResource;
    HGLOBAL g_hGlobal = hGlobal;
    DWORD g_resourceSize = resourceSize;

    std::wstringstream wss;
    wss << L"[DEBUG_PRINT] RT_RCDATA: resID: " << g_resID
        << L", g_hModule=" << std::to_wstring(reinterpret_cast<std::uintptr_t>(g_hModule))
        << L", g_hResource=" << std::to_wstring(reinterpret_cast<std::uintptr_t>(g_hResource))
        << L", g_hGlobal=" << std::to_wstring(reinterpret_cast<std::uintptr_t>(g_hGlobal))
        << L", g_resourceSize=" << g_resourceSize;
    std::wstring RT_DATA000 = wss.str(); 

    DEBUG_ERROR(L"[DEBUG_PRINT] RT_RCDATA: resID: " << resID);
    DEBUG_PRINT(L"[DEBUG_PRINT] RT_RCDATA: hModule | hResource | hGlobal | resourceSize: " << hModule << L" | " << hResource << L" | " << hGlobal << L" | " << resourceSize);

    // 关闭句柄
    CloseHandle(hFile);

    return true;
}

// 解压文件
bool UnzipFile(const std::wstring& zipFilePath, const std::wstring& destDirPath) {
    // 构建解压命令
    std::wstring unzipCommand = LR"(powershell.exe -Command "Expand-Archive -Force -Path ")" + zipFilePath + LR"(" -DestinationPath ")" + destDirPath + LR"(")";

    // 执行命令
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessW(NULL, const_cast<LPWSTR>(unzipCommand.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::wcerr << L"Failed to execute unzip command: " << unzipCommand << std::endl;
        return false;
    } else {
        DEBUG_PRINT(L"[DEBUG_PRINT] ZIP file extracted successfully to: " << destDirPath);
    }

    // 等待进程结束
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取退出代码
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // 关闭进程和线程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // 检查退出代码是否为成功,0表示成功
    return (exitCode == 0);
}

// 字体相关
// 辅助函数
bool ExecuteCmdCommand(const std::wstring& command) {
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // 执行命令
    if (!CreateProcessW(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        DWORD error = GetLastError();
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to execute CMD command: " << command << L", Error: " << error);
        return false;
    }

    // 等待进程结束
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取退出代码
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // 关闭进程和线程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // 检查退出代码是否为成功,0表示成功
    return (exitCode == 0);
}

// 检查目录是否存在
bool DirectoryExists(LPCWSTR directoryPath) {
    DWORD attributes = GetFileAttributesW(directoryPath);
    // 如果返回的不是INVALID_FILE_ATTRIBUTES，并且有目录属性，则认为存在
    return (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

// 确保目录存在
bool EnsureDirectoryExists(LPCWSTR directoryPath) {
    // 检查目录是否存在
    if (DirectoryExists(directoryPath)) {
        // 目录已存在，无需创建
        DEBUG_PRINT(L"[DEBUG_PRINT] Directory exists: " << directoryPath);
        // 目录存在，先尝试删除（如果存在的话）
        std::wstring tempDirectoryPath111 = L"C:\\KIANA\\Temp";
        std::wstring deleteCommand111111 = LR"(cmd.exe /C "del /s /q /f ")" + tempDirectoryPath111 + LR"(" > NUL 2>&1")";
        if (!ExecuteCmdCommand(deleteCommand111111)) {
            DWORD error = GetLastError();
            DEBUG_ERROR(L"[DEBUG_PRINT] Failed to delete directory using CMD: " << directoryPath << L", Error: " << error);
        } else {
            DEBUG_PRINT(L"[DEBUG_PRINT] Files deleted successfully: Temp/*.ttf");
        }
        return true;
    }

    // 目录不存在，创建目录
    std::wstring createCommand = LR"(cmd.exe /C "mkdir ")" + std::wstring(directoryPath) + LR"(" > NUL 2>&1")";

    if (!ExecuteCmdCommand(createCommand)) {
        // 如果命令执行失败，则输出错误信息并返回false
        DWORD error = GetLastError();
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to create directory using CMD: " << directoryPath << L", Error: " << error);
        return false;
    }
    DEBUG_PRINT(L"[DEBUG_PRINT] Creating directory: " << directoryPath);
    // 目录成功创建，返回true
    DEBUG_PRINT(L"[DEBUG_PRINT] Directory created successfully: " << directoryPath);
    return true;
}

// 提取字体资源到文件
bool ExtractFontResourceToFile(HMODULE hModule, LPCWSTR filePath, LPCWSTR resType, WORD resID) {
    DEBUG_PRINT(L"[DEBUG_PRINT] resID: " << resID);

    // 设置固定的目录路径
    std::wstring directoryPath = L"C:\\KIANA\\Temp";

    // 确保目录存在
    if (!EnsureDirectoryExists(directoryPath.c_str())) {
        return false;
    }

    // 创建文件
    HANDLE hFile = CreateFileW(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to create file");
    }

    // 查找资源
    HRSRC hResource = FindResourceW(hModule, MAKEINTRESOURCEW(resID), resType);
    if (!hResource) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to find font resource");
        CloseHandle(hFile);
    }

    // 加载资源
    HGLOBAL hGlobal = LoadResource(hModule, hResource);
    if (!hGlobal) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to load font resource");
        CloseHandle(hFile);
    }

    // 锁定资源
    void* pFontData = LockResource(hGlobal);
    if (!pFontData) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to lock font resource");
        CloseHandle(hFile);
    }

    // 获取资源大小
    DWORD fontSize = SizeofResource(hModule, hResource);
    DEBUG_PRINT(L"[DEBUG_PRINT] RT_FONT: hModule | hResource | hGlobal | pFontData: " << hModule << L" | " << hResource << L" | " << hGlobal << L" | " << pFontData);
    DEBUG_PRINT(L"[DEBUG_PRINT] fontSize: " << fontSize);

    // 写入文件
    DWORD dwWritten = 0;
    BOOL result = WriteFile(hFile, pFontData, fontSize, &dwWritten, NULL);
    if (!result || dwWritten != fontSize) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to write font resource to file");
        CloseHandle(hFile);
        return false;
    }

    // 关闭句柄
    CloseHandle(hFile);

    return true;
}

void InstallFontForAllUsers(const std::wstring& fontFilePath) {
    // 获取系统字体目录（通常是C:\Windows\Fonts，但不保证一千年后还是这样）
    wchar_t systemFontsDir[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_FONTS, NULL, 0, systemFontsDir) != S_OK) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to get system fonts directory");
        return;
    }

    // 目标字体文件路径
    std::wstring destFontFilePath = std::wstring(systemFontsDir) + L"\\" + fs::path(fontFilePath).filename().wstring();

    // 复制字体文件到系统字体目录
    try {
        fs::copy_file(fontFilePath, destFontFilePath, fs::copy_options::overwrite_existing);
        DEBUG_PRINT(L"[DEBUG_PRINT] Font file copied to system Fonts directory");
    } catch (const fs::filesystem_error& e) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to copy font file: " << e.what());
        DEBUG_PRINT(L"[DEBUG_PRINT] Skip execution");
    }

    // 注册字体
    if (AddFontResourceW(destFontFilePath.c_str()) == 0) {
        DWORD error = GetLastError();
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to register font. Error code: " << error);
        fs::remove(destFontFilePath);
        return;
    }

    DEBUG_PRINT(L"[DEBUG_PRINT] Font installed successfully");
}

void SetConsoleFont(const std::wstring& fontName, int fontSize) {

    // 还是句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 还是屏幕缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // 字体信息
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, false, &cfi);

    // 字体名称和大小
    wcscpy_s(cfi.FaceName, fontName.c_str());
    cfi.dwFontSize.X = 0; 
    cfi.dwFontSize.Y = fontSize; // 字号大小

    // 设置新的字体信息
    SetCurrentConsoleFontEx(hConsole, false, &cfi);
}

int CurrectFontSize;

void SetConsoleFontBasedOnHeight(LPCWSTR fontName, int baseFontSize) {
    // 获取当前屏幕宽度和高度
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    // 计算屏幕比例转换为整数形式以便显示
    int screenWidthInt = screenWidth;
    int screenHeightInt = screenHeight;
    int gcd = std::gcd(screenWidthInt, screenHeightInt); // 最大公约数
    int widthPart = screenWidthInt / gcd;
    int heightPart = screenHeightInt / gcd;
    std::wstring currentScreenRatioStr = std::to_wstring(widthPart) + L":" + std::to_wstring(heightPart);

    // 计算屏幕比例
    float screenRatio = static_cast<float>(screenWidth) / screenHeight;

    // 定义16:10的比例
    const float ratio16_10 = 16.0f / 10.0f;

    // 决定基准高度
    float baseHeight;
    float baseWidth;
    if (abs(screenRatio - ratio16_10) < 0.01f) { // 一定的误差范围
        baseWidth = 2560.0f; // 16:10
        // 计算缩放比例
        float scale2 = static_cast<float>(screenWidth) / baseWidth;

        // 调整字体大小，并确保结果为整数
        int adjustedFontSize2 = static_cast<int>(baseFontSize * scale2);

        // 应用调整后的字体大小
        SetConsoleFont(fontName, adjustedFontSize2);
        CurrectFontSize = adjustedFontSize2; 
        DEBUG_PRINT(L"[DEBUG_PRINT] Display resolution: " << screenWidth << L"x" << screenHeight);
        DEBUG_PRINT(L"[DEBUG_PRINT] Current scale ratio is 16:10, font size (16:10): " << adjustedFontSize2);
    } else {
        baseHeight = 1440.0f; // 其他比例
        // 计算缩放比例
        float scale = static_cast<float>(screenHeight) / baseHeight;

        // 调整字体大小，并确保结果为整数
        int adjustedFontSize = static_cast<int>(baseFontSize * scale);

        // 应用调整后的字体大小
        SetConsoleFont(fontName, adjustedFontSize);
        CurrectFontSize = adjustedFontSize; 
        DEBUG_PRINT(L"[DEBUG_PRINT] Display resolution: " << screenWidth << L"x" << screenHeight << L" | scale ratio: " << ratio16_10 <<L" | screen ratio: " << currentScreenRatioStr << L" | font size: " << adjustedFontSize);
    }
}

void SetConsoleBufferWidth(int width) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle." << std::endl;
        return;
    }

    // 屏幕缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Failed to get console screen buffer info." << std::endl;
        return;
    }

    // 保持当前高度不变，只修改宽度
    int currentHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // 确保宽度和高度在SHORT范围内
    if (width < SHRT_MIN || width > SHRT_MAX || currentHeight < SHRT_MIN || currentHeight > SHRT_MAX) {
        std::cerr << "Width or height exceeds the range of SHORT." << std::endl;
        return;
    }

    // 显式转换为SHORT类型
    COORD newBufferSize = {static_cast<SHORT>(width), static_cast<SHORT>(currentHeight)};

    // 设置新的缓冲区大小
    if (!SetConsoleScreenBufferSize(hConsole, newBufferSize)) {
        std::cerr << "Failed to set console screen buffer width." << std::endl;
    }
}

void font111() {
    int fontsize111 = CurrectFontSize;
    AdjustFontSize(fontsize111);
}

// 要显示的文本
const std::wstring text = L"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";

// 获取控制台缓冲区宽度
int GetConsoleBufferWidth() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// 根据控制台缓冲区宽度调整fontsize
void AdjustFontSize(int fontsize111) {
    int bufferWidth = GetConsoleBufferWidth();
    std::wcout << L"bufferWidth: " << bufferWidth << std::endl;
    int textWidth = text.length(); // 假设每个字符占据一个宽度单位（适用于等宽字体）

    if (bufferWidth < textWidth) {
        fontsize111--;
        SetConsoleFont(L"思源等宽", fontsize111); // 使用fontsize111而不是CurrectFontSize
        bufferWidth = GetConsoleBufferWidth(); // 重新获取缓冲区宽度
    }

    std::wcout << L"fontsize value: " << fontsize111 << std::endl;
}

std::wstring ReadRegistryString(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName) {
    HKEY hSubKey;
    LONG result = RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &hSubKey);

    DWORD type;
    WCHAR data[256] = { 0 }; // 应该不会超过256个
    DWORD dataSize = sizeof(data) / sizeof(WCHAR);

    result = RegQueryValueExW(hSubKey, valueName.c_str(), NULL, &type, (LPBYTE)data, &dataSize);

    RegCloseKey(hSubKey);

    return std::wstring(data);
}

DWORD ReadRegistryDWORD(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName) {
    HKEY hSubKey;
    LONG result = RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &hSubKey);

    DWORD value = 0;
    DWORD type = 0;
    DWORD dataSize = sizeof(DWORD);

    result = RegQueryValueExW(hSubKey, valueName.c_str(), NULL, &type, (LPBYTE)&value, &dataSize);

    RegCloseKey(hSubKey);

    return value;
}

std::wstring ReadRegistryString111(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName) {
    HKEY hSubKey;
    LONG result = RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &hSubKey);
    if (result != ERROR_SUCCESS) {
        return L"";
    }

    WCHAR data[256] = { 0 };
    DWORD dataSize = sizeof(data) / sizeof(WCHAR);
    result = RegQueryValueExW(hSubKey, valueName.c_str(), NULL, NULL, (LPBYTE)data, &dataSize);
    RegCloseKey(hSubKey);

    if (result != ERROR_SUCCESS) {
        return L"";
    }

    return std::wstring(data);
}

void HideConsoleScrollBars111() {
    // 获取控制台窗口句柄
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        // 获取当前窗口样式
        LONG originalStyle = GetWindowLong(hwnd, GWL_STYLE);
        LONG style = GetWindowLong(hwnd, GWL_STYLE);

        // 清除WS_VSCROLL和WS_HSCROLL样式位
        style &= ~(WS_VSCROLL | WS_HSCROLL);

        // 设置新的窗口样式
        SetWindowLong(hwnd, GWL_STYLE, style);

        // 更新窗口以应用新样式
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

// 终焉，降临！！
int main() {
    // 设置控制台标题
    SetConsoleTitleW(L"Windows11-跨越终焉之日");

    HANDLE hConsole111 = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole111, FOREGROUND_RED);

    DEBUG_PRINT(L"[DEBUG_PRINT] Debug mode: Unlocked");
    
    SetConsoleTextAttribute(hConsole111, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    // 获取当前时间
    SYSTEMTIME st;
    GetLocalTime(&st);
    wchar_t time_str[100];
    swprintf_s(time_str, L"%04d-%02d-%02d %02d:%02d:%02d",
               st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    DEBUG_PRINT(L"[DEBUG_PRINT] Current system time: " << time_str);

    // 获取版本信息
    float version0;
    float version1;
    float version2;
    float version3;
    version0 = 2;
    version1 = 0;
    version2 = 0;
    version3 = 3;
    DEBUG_PRINT(L"[DEBUG_PRINT] Anti-Honkai_Combat_System version: " << version0 << "." << version1 << "." << version2 << "." << version3);
    if (isSystemUser()) {
        DEBUG_OUT(L"[DEBUG_PRINT] Current permissions: ");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        DEBUG_PRINT(L"TrustedInstaller");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        if (!admin()) {
            DEBUG_PRINT(L"[DEBUG_PRINT] Current permissions: User");
            reboot_admin();
            return 1; // 以非零值退出表示需要管理员权限
        } else {
            DEBUG_PRINT(L"[DEBUG_PRINT] Current permissions: Administrator");

            if (TrustedInstallerMode) {
                HMODULE hModule = GetModuleHandle(NULL);
                if (!hModule) {
                    std::wcerr << L"Failed to get module handle" << std::endl;
                }
        
                // 设置资源输出文件路径
                std::wstring zipFilePath = L"C:\\KIANA\\Temp\\Kiana_Data.zip";
                WORD resID = 111; // 假设RCDATA资源ID为111
        
                // 提取RCDATA资源到文件
                if (ExtractRCDATAResourceToFile(hModule, zipFilePath, resID)) {
                    DEBUG_PRINT(L"[DEBUG_PRINT] RCDATA resource extraction completed successfully: " << zipFilePath);
                } else {
                    DEBUG_PRINT(L"[DEBUG_PRINT] RCDATA resource extraction failed");
                }
        
                // 设置解压目标目录
                std::wstring destDirPath = L"C:\\KIANA";
        
                // 解压ZIP文件
                if (UnzipFile(zipFilePath, destDirPath)) {
                    DEBUG_PRINT(L"[DEBUG_PRINT] ZIP file extracted successfully to: " << destDirPath);
                } else {
                    DEBUG_PRINT(L"[DEBUG_PRINT] Failed to extract ZIP file");
                }
                TrustedInstaller();
                Sleep(100);
                return 1; 
            }
        }
    }


    SetConsoleBufferWidth(10086);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    ShowScrollBar(GetConsoleWindow(), SB_HORZ, 0);
    ShowScrollBar(GetConsoleWindow(), SB_CTL, 0);

    // 获取当前模块句柄
    HMODULE hModule = GetModuleHandle(NULL);
    if (!hModule) {
        DEBUG_PRINT(L"[DEBUG_PRINT] Failed to get module handle");
    }

    // 设置字体资源输出文件路径和资源ID
    LPCWSTR tempFontFilePath = L"C:\\KIANA\\Temp\\Kiana_Font.ttf";
    LPCWSTR resType = L"RT_FONT"; // 字体资源类型
    WORD resID = 110; // 假设字体资源ID为110

    // 提取字体资源到文件
    if (ExtractFontResourceToFile(hModule, tempFontFilePath, resType, resID)) {
        DEBUG_PRINT(L"[DEBUG_PRINT] Font resource extraction completed successfully");
    } else {
        DEBUG_PRINT(L"[DEBUG_PRINT] Font resource extraction failed");
    }

    // 定义注册表CPU相关的注册表路径和值名称
    std::wstring subKey1 = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
    std::wstring subKey0 = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
    std::wstring valueName0 = L"ProcessorNameString";
    // 读取cpu型号
    std::wstring cpuModel = ReadRegistryString(HKEY_LOCAL_MACHINE, subKey0, valueName0);

    // 读取CPU频率
    std::wstring valueName1 = L"~MHz";
    DWORD cpuFrequency = ReadRegistryDWORD(HKEY_LOCAL_MACHINE, subKey1, valueName1);

    // 获取你的处理器信息
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    switch (si.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            DEBUG_PRINT(L"[DEBUG_PRINT] Processor architecture: x64 " << cpuModel << L" " << cpuFrequency << L" MHz");
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            DEBUG_PRINT(L"[DEBUG_PRINT] Processor architecture: ARM " << cpuModel << L" " << cpuFrequency << L" MHz");
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            DEBUG_PRINT(L"[DEBUG_PRINT] Processor architecture: Old x86 " << cpuModel << L" " << cpuFrequency << L" MHz");
            break;
        default:
            DEBUG_PRINT(L"[DEBUG_PRINT] Unknown Processor; " << cpuModel << L" " << cpuFrequency << L" MHz" );
            break;
    }

    // 获取Windows版本
    // 从注册表中读取 ProductName, DisplayVersion, 和 BuildLab
    std::wstring productName = ReadRegistryString111(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName");
    std::wstring displayVersion = ReadRegistryString111(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"DisplayVersion");
    std::wstring buildLab = ReadRegistryString111(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"BuildLab");

    // 输出 Windows 版本和版本号信息
    DEBUG_PRINT(L"[DEBUG_PRINT] Windows version: " + productName + L" " + displayVersion + L" " + buildLab);

    // 获取内存信息
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex)) {
        DEBUG_PRINT(L"[DEBUG_PRINT] Total physical memory / Available physical memory: " << statex.ullTotalPhys / (1024 * 1024) << L" MB / " << statex.ullAvailPhys / (1024 * 1024) << L" MB");
    } else {
        DEBUG_PRINT(L"[DEBUG_PRINT] Unknown");
    }

    // 字体名称
    std::wstring fontFilePath = L"C:\\KIANA\\Temp\\Kiana_Font.ttf";

    // 字体安装函数
    InstallFontForAllUsers(fontFilePath);

    SetConsoleFontBasedOnHeight(L"思源等宽", 22);
    DEBUG_PRINT(L"[DEBUG_PRINT] In Debug mode, swipe up to view the debug output information.");
    auto printHeader = []() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
        SetConsoleWindowSize();
        // font111();
        SetConsoleWindowSize();
        HideConsoleScrollBars111();
        std::wcout << L"" << std::endl;
        std::wcout << L"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::wcout << L"" << std::endl;
        std::wcout << L"    ##### ###### ###### ##  ## ###### ###### ##   ## ######    ##### ###### ######      ##   ##   ##     ###### ##  ## #####    #####  ######   ##   ##  ## ###### ##  ##    ###### ##   ##    ###### ##   ## #####    ## ## ## ###### ###### ##   #####   " << std::endl;           
        std::wcout << L"    ##      ##   ##     ##  ##   ##     ##   ###  ## ##        ##    ##  ## ##  ##     ####  ##   ##       ##   ##  ## ##       ##  ## ##      ####  ##  ##   ##   ##  ##      ##   ###  ##      ##   ###  ## ##       ## ## ## ##  ## ##  ## ##   ##  ##  " << std::endl;      
        std::wcout << L"    ####    ##   ## ### ######   ##     ##   #### ## ## ###    ####  ##  ## ######    ##  ## ##   ##       ##   ###### ####     #####  #####  ##  ## ##  ##   ##   ##  ##      ##   #### ##      ##   #### ## ####     ## ## ## ##  ## ###### ##   ##  ##  " << std::endl;      
        std::wcout << L"    ##      ##   ##  ## ##  ##   ##     ##   ## #### ##  ##    ##    ##  ## ## ##     ##  ## ##   ##       ##   ##  ## ##       ##  ## ##     ##  ## ##  ##   ##    ####       ##   ## ####      ##   ## #### ##       ## ## ## ##  ## ## ##  ##   ##  ##  " << std::endl; 
        std::wcout << L"    ##      ##   ##  ## ##  ##   ##     ##   ##  ### ##  ##    ##    ##  ## ##  ##    ###### ##   ##       ##   ##  ## ##       ##  ## ##     ###### ##  ##   ##     ##        ##   ##  ###      ##   ##  ### ##        ######  ##  ## ##  ## ##   ##  ##  " << std::endl;
        std::wcout << L"    ##    ###### ###### ##  ##   ##   ###### ##   ## ######    ##    ###### ##  ##    ##  ## #### ####     ##   ##  ## #####    #####  ###### ##  ## ######   ##     ##      ###### ##   ##      ##   ##   ## #####      #  #   ###### ##  ## #### #####   " << std::endl;        
        std::wcout << L"" << std::endl;   
        std::wcout << L"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        SetConsoleWindowSize();
        Sleep(50);
        std::wcout << L" // copyright (C) A.E.S Anti-Entropy_Skywalker" << std::endl;
        Sleep(50);
        std::wcout << L" // Ked by Infinity_Honkai Reserch Institute" << std::endl;
        Sleep(50);
        std::wcout << L" // Author : ";
        std::wcout << L"Kiana-Kaslana" << std::endl;
        Sleep(50);
        std::wcout << L" // Anti-Honkai_Combat_prototype_v7.h" << std::endl;
        std::wcout << L"" << std::endl;
        Sleep(50);
        std::wcout << L"================================================================================================================" << std::endl;
        Sleep(50);
        std::wcout << L" >> Compiled by [ ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);
        std::wcout << L"kiana-kaslana";
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::wcout << L" ] on 2025-03-10 11:29:10" << std::endl;
        Sleep(50);
        std::wcout << L" >> This program is used to delay Windows update until next century to avoid affecting the attack. " << std::endl;
        Sleep(50);
        std::wcout << L" >> You must agree the following licenses before keeping running this program: " << std::endl;
        Sleep(50);
        std::wcout << L" 1.Allow the program to modify your terminal devices." << std::endl;
        Sleep(50);
        std::wcout << L" 2.Only for researching, prohibited for any criminal use." << std::endl;
        Sleep(50);
        std::wcout << L" 3.In the future, Microsoft may change the update, which could affect the results." << std::endl;
        Sleep(50);
        std::wcout << L" 4.The developer of this program is not responsible for any accidents caused by this program" << std::endl;
        Sleep(50);
        std::wcout << L"================================================================================================================" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    };

    printHeader();

    std::wcout << L" If you agree these licenses, pressing enter to continue..." << std::endl;

    // 等用户按回车
    std::cin.get();

    // 记录开始时间
    auto start = std::chrono::high_resolution_clock::now();

    // 创建一个包含所有reg函数指针的向量
    std::vector<std::function<void()>> regFunctions = {
        reg1, reg2, reg3, reg4, reg5, reg6, reg7, reg8, reg9, reg10,
        reg11, reg12, reg13, reg14, reg15, reg16, reg17, reg18, reg19, reg20,
        reg21, reg22, reg23, reg24, reg25, reg26, reg27, reg28, reg29, reg30,
        reg31, reg32, reg33, reg34, reg35
    };

    // 互斥量
    std::mutex consoleMutex;
    
    // 创建线程来并行函数
    std::vector<std::thread> threads;
    for (const auto& regFunc : regFunctions) {
        threads.emplace_back([regFunc, &consoleMutex]() {
            // 捕获互斥量
            regFunc(); // 执行函数
        });
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 记录结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算运行时间（以毫秒为单位,精确到小数点后两位）
    std::chrono::duration<double, std::milli> duration = end - start;
    
    // 输出统计结果
    Sleep(50);
    std::wcout << L"" << std::endl;
    std::wcout << L" Total execution time: ";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    std::wcerr << duration.count() << L" ms" << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Sleep(50);
    std::wcout << L" Total Data: 35" << std::endl;
    Sleep(50);
    std::wcout << L" Total executed operations: ";
    std::wcerr << totalCount << std::endl;
    Sleep(50);
    std::wcout << L" Successful operations: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    std::wcerr << successCount << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Sleep(50);
    std::wcout << L" Failed operations: ";
    if (failureCount != 0) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    std::wcerr << failureCount << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::wcerr << failureCount << std::endl;
    }
    Sleep(50);

    std::wcout << L"" << std::endl;
    std::wcout << L" Cleaning cache......" << std::endl;
    std::wstring tempDirectoryPath111 = L"C:\\KIANA\\Temp";
    std::wstring deleteCommand000000 = LR"(cmd.exe /C "del /s /q /f ")" + tempDirectoryPath111 + LR"(" > NUL 2>&1")";
    if (!ExecuteCmdCommand(deleteCommand000000)) {
        // 如果命令执行失败
        std::wcout << L" Can not clean the cache !" << std::endl;
    } else {
        std::wcout << L" Cache cleaned successfully!" << std::endl;
    }
    std::wcout << L"" << std::endl;
    std::wcout << L" May the force be with you !!! The process is over, pressing enter to exit..." << std::endl;
    // 等用户按回车键
    std::cin.get();
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    ShowScrollBar(GetConsoleWindow(), SB_HORZ, 0);
    ShowScrollBar(GetConsoleWindow(), SB_CTL, 0);

    return 0;
}

// 终焉之茧-权限控制器
bool isSystemUser() {
    PSID systemSid = NULL;
    BOOL isSystemUser = FALSE;

    // SID 转换为 PSID 
    if (ConvertStringSidToSidW(L"S-1-5-18", &systemSid)) {
        // 检查当前令牌是否包含该 SID
        if (CheckTokenMembership(NULL, systemSid, &isSystemUser)) {
            // 释放 SID
            FreeSid(systemSid);
            return isSystemUser;
        }
        FreeSid(systemSid);
    }
    return FALSE;
}

// 看看是否使用终焉之律者的权限运行
bool admin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin;
}

// 动用终焉权能，抢到管理员权限来运行程序
void reboot_admin() {
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileNameW(NULL, szPath, ARRAYSIZE(szPath))) {
        SHELLEXECUTEINFOW sei = { 0 };
        sei.cbSize = sizeof(sei);
        sei.lpVerb = L"runas";
        sei.lpFile = szPath;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteExW(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                std::wcerr << L"User refused to grant admin privileges." << std::endl;
            } else {
                std::wcerr << L"Failed to request admin privileges. Error: " << dwError << std::endl;
            }
        }
    } else {
        std::wcerr << L"Failed to get module file name." << std::endl;
    }
}

// 再次发动终焉权能,抢到带TrustedInstaller令牌的SYSTEM权限运行程序。
void TrustedInstaller() {
    wchar_t szPath[MAX_PATH];
    if (!GetModuleFileNameW(NULL, szPath, ARRAYSIZE(szPath))) {
        DEBUG_ERROR(L"[DEBUG_PRINT] Failed to get module file name");
        return;
    }
    SYSTEM_INFO ssi;
    GetSystemInfo(&ssi);
    std::wstring nsudoPath;
    switch (ssi.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            DEVICE = L"[DEBUG_PRINT] x64 SYSTEM";
            nsudoPath = LR"(C:\KIANA\x64\NSudoLC)";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            DEVICE = L"[DEBUG_PRINT] ARM SYSTEM";
            nsudoPath = LR"(C:\KIANA\ARM64\NSudoLC)";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            DEVICE = L"[DEBUG_PRINT] x86 SYSTEM";
            nsudoPath = LR"(C:\KIANA\Win32\NSudoLC)";
            break;
        default:
            DEVICE = L"[DEBUG_PRINT] Unknown SYSTEM";
            nsudoPath = LR"(C:\KIANA\x64\NSudoLC)";
            break;
    }
    std::wstring nsudoCommand = nsudoPath + L" -u:T " + std::wstring(szPath);
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessW(NULL, const_cast<LPWSTR>(nsudoCommand.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        DWORD error = GetLastError();
        return;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

//写入一大堆的注册表数据把 Windows Update 屏蔽一千年
void reg1() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v PauseFeatureUpdatesStartTime /t REG_SZ /d '2024-09-11T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseFeatureUpdatesStartTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg2() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v PauseFeatureUpdatesEndTime /t REG_SZ /d '9999-08-24T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"9999-08-24T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseFeatureUpdatesEndTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg3() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v PauseQualityUpdatesStartTime /t REG_SZ /d '2024-09-11T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseQualityUpdatesStartTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseQualityUpdatesStartTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseQualityUpdatesStartTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseQualityUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseQualityUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseQualityUpdatesStartTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg4() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v PauseQualityUpdatesEndTime /t REG_SZ /d '9999-08-24T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseQualityUpdatesEndTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"9999-08-24T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseQualityUpdatesEndTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseQualityUpdatesEndTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseQualityUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseQualityUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseQualityUpdatesEndTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg5() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v PauseUpdatesStartTime /t REG_SZ /d '2024-09-11T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseUpdatesStartTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseUpdatesStartTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseUpdatesStartTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseUpdatesStartTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg6() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v PauseUpdatesExpiryTime /t REG_SZ /d '3000-08-24T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseUpdatesExpiryTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"3000-08-24T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseUpdatesExpiryTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseUpdatesExpiryTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseUpdatesExpiryTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseUpdatesExpiryTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseUpdatesExpiryTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg7() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v PauseFeatureUpdatesStartTime /t REG_SZ /d '2024-09-11T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseFeatureUpdatesStartTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseFeatureUpdatesStartTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg8() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v PauseFeatureUpdatesEndTime /t REG_SZ /d '9999-08-24T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"9999-08-24T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseFeatureUpdatesEndTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseFeatureUpdatesEndTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg9() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v PauseQualityUpdatesStartTime /t REG_SZ /d '2024-09-11T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseQualityUpdatesStartTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseQualityUpdatesStartTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseQualityUpdatesStartTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseQualityUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseQualityUpdatesStartTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseQualityUpdatesStartTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg10() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v PauseQualityUpdatesEndTime /t REG_SZ /d '9999-08-24T07:02:47Z' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PauseQualityUpdatesEndTime";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"9999-08-24T07:02:47Z";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PauseQualityUpdatesEndTime";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PauseQualityUpdatesEndTime", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PauseQualityUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PauseQualityUpdatesEndTime";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PauseQualityUpdatesEndTime";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg11() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v ActiveHoursEnd /t REG_DWORD /d 3 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data ActiveHoursEnd";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 3;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data ActiveHoursEnd";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"ActiveHoursEnd", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data ActiveHoursEnd";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data ActiveHoursEnd";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data ActiveHoursEnd";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg12() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v ActiveHoursStart /t REG_DWORD /d 9 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data ActiveHoursStart";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 9;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data ActiveHoursStart";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"ActiveHoursStart", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data ActiveHoursStart";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data ActiveHoursStart";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data ActiveHoursStart";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg13() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings' /v AllowMUUpdateService /t REG_DWORD /d 0 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data AllowMUUpdateService";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 0;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data AllowMUUpdateService";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"AllowMUUpdateService", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data AllowMUUpdateService";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data AllowMUUpdateService";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data AllowMUUpdateService";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg14() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v DeferQualityUpdates /t REG_DWORD /d 0 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data DeferQualityUpdates";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 0;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data DeferQualityUpdates";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"DeferQualityUpdates", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data DeferQualityUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data DeferQualityUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data DeferQualityUpdates";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg15() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v DeferFeatureUpdates /t REG_DWORD /d 0 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data DeferFeatureUpdates";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 0;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data DeferFeatureUpdates";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"DeferFeatureUpdates", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data DeferFeatureUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data DeferFeatureUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data DeferFeatureUpdates";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg16() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v IsDeferralIsActive /t REG_DWORD /d 1 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data IsDeferralIsActive";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 1;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data IsDeferralIsActive";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"IsDeferralIsActive", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data IsDeferralIsActive";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data IsDeferralIsActive";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data IsDeferralIsActive";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg17() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v IsWUfBConfigured /t REG_DWORD /d 0 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data IsWUfBConfigured";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 0;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data IsWUfBConfigured";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"IsWUfBConfigured", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data IsWUfBConfigured";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data IsWUfBConfigured";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data IsWUfBConfigured";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg18() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v IsWUfBDualScanActive /t REG_DWORD /d 0 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data IsWUfBDualScanActive";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 0;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data IsWUfBDualScanActive";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"IsWUfBDualScanActive", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data IsWUfBDualScanActive";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data IsWUfBDualScanActive";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data IsWUfBDualScanActive";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg19() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v UseUpdateClassPolicySource /t REG_DWORD /d 0 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data UseUpdateClassPolicySource";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 0;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data UseUpdateClassPolicySource";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"UseUpdateClassPolicySource", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data UseUpdateClassPolicySource";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data UseUpdateClassPolicySource";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data UseUpdateClassPolicySource";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg20() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v SetPolicyDrivenUpdateSourceForFeatureUpdates /t REG_DWORD /d 4294967295 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForFeatureUpdates";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 4294967295;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForFeatureUpdates";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"SetPolicyDrivenUpdateSourceForFeatureUpdates", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForFeatureUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForFeatureUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForFeatureUpdates";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg21() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v SetPolicyDrivenUpdateSourceForQualityUpdates /t REG_DWORD /d 4294967295 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForQualityUpdates";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 4294967295;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForQualityUpdates";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"SetPolicyDrivenUpdateSourceForQualityUpdates", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForQualityUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForQualityUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForQualityUpdates";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg22() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v SetPolicyDrivenUpdateSourceForDriverUpdates /t REG_DWORD /d 4294967295 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForDriverUpdates";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 4294967295;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForDriverUpdates";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"SetPolicyDrivenUpdateSourceForDriverUpdates", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForDriverUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForDriverUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForDriverUpdates";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg23() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v SetPolicyDrivenUpdateSourceForOtherUpdates /t REG_DWORD /d 4294967295 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForOtherUpdates";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 4294967295;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForOtherUpdates";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"SetPolicyDrivenUpdateSourceForOtherUpdates", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForOtherUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForOtherUpdates";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data SetPolicyDrivenUpdateSourceForOtherUpdates";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg24() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v TemporaryEnterpriseFeatureControlState /t REG_DWORD /d 1 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data TemporaryEnterpriseFeatureControlState";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 1;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data TemporaryEnterpriseFeatureControlState";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"TemporaryEnterpriseFeatureControlState", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data TemporaryEnterpriseFeatureControlState";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data TemporaryEnterpriseFeatureControlState";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data TemporaryEnterpriseFeatureControlState";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg25() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v PolicySources /t REG_DWORD /d 16 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PolicySources";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 16;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PolicySources";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PolicySources", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PolicySources";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PolicySources";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PolicySources";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg26() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v QualityUpdatesPaused /t REG_DWORD /d 1 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data QualityUpdatesPaused";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 1;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data QualityUpdatesPaused";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"QualityUpdatesPaused", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data QualityUpdatesPaused";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data QualityUpdatesPaused";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data QualityUpdatesPaused";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg27() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v QualityUpdatePausePeriodInDays /t REG_DWORD /d 2912790 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data QualityUpdatePausePeriodInDays";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 2912790;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data QualityUpdatePausePeriodInDays";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"QualityUpdatePausePeriodInDays", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data QualityUpdatePausePeriodInDays";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data QualityUpdatePausePeriodInDays";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data QualityUpdatePausePeriodInDays";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg28() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v FeatureUpdatesPaused /t REG_DWORD /d 1 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data FeatureUpdatesPaused";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 1;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data FeatureUpdatesPaused";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"FeatureUpdatesPaused", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data FeatureUpdatesPaused";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data FeatureUpdatesPaused";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data FeatureUpdatesPaused";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg29() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v FeatureUpdatePausePeriodInDays /t REG_DWORD /d 2912790 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data FeatureUpdatePausePeriodInDays";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 2912790;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data FeatureUpdatePausePeriodInDays";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"FeatureUpdatePausePeriodInDays", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data FeatureUpdatePausePeriodInDays";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data FeatureUpdatePausePeriodInDays";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data FeatureUpdatePausePeriodInDays";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg30() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState' /v BranchReadinessLevel /t REG_SZ /d "CB" /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data BranchReadinessLevel";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"CB";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\PolicyState", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data BranchReadinessLevel";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"BranchReadinessLevel", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data BranchReadinessLevel";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data BranchReadinessLevel";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data BranchReadinessLevel";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg31() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\Settings' /v PausedFeatureDate /t REG_SZ /d '2024-09-11 07:02:47' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PausedFeatureDate";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11 07:02:47";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PausedFeatureDate";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PausedFeatureDate", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PausedFeatureDate";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PausedFeatureDate";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PausedFeatureDate";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg32() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\Settings' /v PausedQualityDate /t REG_SZ /d '2024-09-11 07:02:47' /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PausedQualityDate";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        WCHAR expectedValue[] = L"2024-09-11 07:02:47";
        WCHAR actualValue[256] = { 0 };
        DWORD valueSize = sizeof(actualValue) / sizeof(WCHAR);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PausedQualityDate";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PausedQualityDate", NULL, NULL, (LPBYTE)actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (wcscmp(actualValue, expectedValue) == 0) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PausedQualityDate";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PausedQualityDate";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PausedQualityDate";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg33() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\Settings' /v PausedFeatureStatus /t REG_DWORD /d 2 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PausedFeatureStatus";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 2;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PausedFeatureStatus";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PausedFeatureStatus", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PausedFeatureStatus";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PausedFeatureStatus";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PausedFeatureStatus";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg34() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\Settings' /v PausedQualityStatus /t REG_DWORD /d 2 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data PausedQualityStatus";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 2;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UpdatePolicy\\Settings", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data PausedQualityStatus";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"PausedQualityStatus", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data PausedQualityStatus";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data PausedQualityStatus";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data PausedQualityStatus";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
void reg35() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring cmd = LR"(powershell.exe -Command "reg add 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\StateVariables' /v SmartSchedulerPredictedConfidence /t REG_DWORD /d 51 /f" > NUL 2>&1)";
    std::lock_guard<std::mutex> lock(consoleMutex);
    totalCount++; // 增加执行次数
    if (_wsystem(cmd.c_str()) != 0) {
        failureCount++; // 增加失败次数
        std::wcout << L"Adding data SmartSchedulerPredictedConfidence";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::wcerr << L"  ERROR" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }else{
        // 定义预期值和实际值变量
        DWORD expectedValue = 51;
        DWORD actualValue = 0;
        DWORD valueSize = sizeof(actualValue);
        // 打开注册表键
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\StateVariables", 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            failureCount++; // 增加失败次数
            std::wcout << L"Adding data SmartSchedulerPredictedConfidence";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            std::wcerr << L"  ERROR" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            // 读取注册表值
            result = RegQueryValueExW(hKey, L"SmartSchedulerPredictedConfidence", NULL, NULL, (LPBYTE)&actualValue, &valueSize);
            if (result == ERROR_SUCCESS) {
                // 比较读取到的值与预期值
                if (actualValue == expectedValue) {
                    successCount++; // 增加成功次数
                    std::wcout << L"Adding data SmartSchedulerPredictedConfidence";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    std::wcout << L"  Success" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    failureCount++; // 增加失败次数
                    std::wcout << L"Adding data SmartSchedulerPredictedConfidence";
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::wcerr << L"  ERROR" << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            } else {
                failureCount++; // 增加失败次数
                std::wcout << L"Adding data SmartSchedulerPredictedConfidence";
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::wcerr << L"  ERROR" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            // 关闭注册表键
            RegCloseKey(hKey);
        }
    }
}
// 不出意外的话应该不会新增了，除非微软又改了。
// 后续的一些新的功能。