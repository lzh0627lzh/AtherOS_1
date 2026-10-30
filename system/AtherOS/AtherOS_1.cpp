#include <algorithm>
#include <cctype>
#include <charconv>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>
using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::random_device rd;
mt19937 rnd(rd());

struct SettingData {
    bool system_download;
    string AtherOS_version;
    int AtherOS_vnum;
    string Welcome_word;
    string Hash_1;
    string Hash_2;
    string Hash_3;
    string Hash_4;
} setting;

namespace other {
vector<string> input();
string byte2hex(unsigned char c);
string mat_to_hex(const vector<vector<unsigned char>> &mat);
string Hash1(string src);
string Hash2(string src);
string Hash3(string src);
string Hash4(string src);
}; // namespace other
using namespace other;

//!===================================================================

namespace big_char {
const int font[44][7] = {
    // A
    {14, 27, 17, 31, 17, 17, 17},
    // B
    {0x1F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F},
    // C
    {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E},
    // D
    {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F},
    // E
    {0x1F, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x1F},
    // F
    {0x1F, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x10},
    // G
    {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0E},
    // H
    {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11},
    // I
    {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E},
    // J
    {0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0E},
    // K
    {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11},
    // L
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F},
    // M
    {0x11, 0x1B, 0x15, 0x11, 0x11, 0x11, 0x11},
    // N
    {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11},
    // O
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E},
    // P
    {0x0F, 0x11, 0x11, 0x0F, 0x10, 0x10, 0x10},
    // Q
    {0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D},
    // R
    {0x0F, 0x11, 0x11, 0x0F, 0x14, 0x12, 0x11},
    // S
    {0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E},
    // T
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    // U
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E},
    // V
    {0x11, 0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04},
    // W
    {0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11},
    // X
    {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11},
    // Y
    {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04},
    // Z
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F},
    // 0
    {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E},
    // 1
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E},
    // 2
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F},
    // 3
    {0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E},
    // 4
    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02},
    // 5
    {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E},
    // 6
    {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E},
    // 7
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08},
    // 8
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E},
    // 9
    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C},
    // _ 36
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F},
    // - 37
    {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00},
    // . 38
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00},
    // ! 39
    {0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00},
    // = 40
    {0x00, 0x1F, 0x00, 0x00, 0x1F, 0x00, 0x00},
    // + 41
    {0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00},
    // / 42
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00},
    // * 43
    {0x00, 0x11, 0x04, 0x1F, 0x04, 0x11, 0x00},
};

int get_idx(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= '0' && c <= '9')
        return 26 + (c - '0');
    if (c == '_')
        return 36;
    if (c == '-')
        return 37;
    if (c == '.')
        return 38;
    if (c == '!')
        return 39;
    if (c == '=')
        return 40;
    if (c == '+')
        return 41;
    if (c == '/')
        return 42;
    if (c == '*')
        return 43;
    return -1;
}

void print_big(const string &s) {
    for (int row = 0; row < 7; row++) {
        for (char ch : s) {
            if (ch == ' ') {
                cout << "      ";
                continue;
            }
            int id = get_idx(ch);
            if (id == -1)
                continue;
            int bits = font[id][row];
            for (int b = 0; b < 5; b++) {
                if (bits & (1 << (4 - b)))
                    cout << "█";
                else
                    cout << " ";
            }
            cout << " ";
        }
        cout << '\n';
    }
}
} // namespace big_char
using namespace big_char;

//!====================================================================

namespace jsonaa {
void init(json &j) {
    string path = "..\\AtherOS_File\\setting.json";
    ifstream fin(path);
    j["system_download"] = false;
    j["AtherOS_version"] = "1.0.1(2610.1030)";
    j["AtherOS_vnum"] = 1011;
    j["Welcome_word"] = "欢迎!";
    j["Hash_1"] = Hash1("123456");
    j["Hash_2"] = Hash2("123456");
    j["Hash_3"] = Hash3("123456");
    j["Hash_4"] = Hash4("123456");
    ofstream fout(path);
    fout << j.dump(4);
    fout.close();
}

json LoadSetting() {
    string path = "..\\AtherOS_File\\setting.json";
    fs::create_directories("..\\AtherOS_File");
    ifstream fin(path);
    json j;
    if (!fin.is_open()) {
        init(j);
        fin.open(path);
    }
    try {
        fin >> j;
    } catch (const json::parse_error &e) {
        init(j);
    }
    fin.close();
    return j;
}

void InputSetting() {
    string path = "..\\AtherOS_File\\setting.json";
    fs::create_directories("..\\AtherOS_File");
    ifstream fin(path);
    json j;
    if (!fin.is_open()) {
        init(j);
        fin.open(path);
    }
    try {
        fin >> j;
    } catch (const json::parse_error &e) {
        init(j);
    }
    fin.close();
    setting.system_download = j.value<bool>("system_download", true);
    setting.AtherOS_version = j.value<string>("AtherOS_version", "1.1.0(2611.1027)");
    setting.AtherOS_vnum = j.value<int>("AtherOS_vnum", 1100);
    setting.Welcome_word = j.value<string>("Welcome_word", "欢迎!");
    setting.Hash_1 = j.value<string>("Hash_1", Hash1("123456"));
    setting.Hash_2 = j.value<string>("Hash_2", Hash2("123456"));
    setting.Hash_3 = j.value<string>("Hash_3", Hash3("123456"));
    setting.Hash_4 = j.value<string>("Hash_4", Hash4("123456"));
    return;
}
} // namespace jsonaa
using namespace jsonaa;

//!====================================================================

namespace windowsapi {
void RestartSelf() {
    wchar_t buf[MAX_PATH];
    GetModuleFileNameW(NULL, buf, MAX_PATH);
    ShellExecuteW(NULL, L"open", buf, NULL, NULL, SW_SHOWNORMAL);
    ExitProcess(0);
}

void SetCursorVisible(bool show) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(hOut, &ci);
    ci.bVisible = show;
    SetConsoleCursorInfo(hOut, &ci);
}
} // namespace windowsapi
using namespace windowsapi;

//!====================================================================

namespace system_op {
bool system_download() {
    json j = LoadSetting();
    return j.value<bool>("system_download", false);
}

string InputPass() {
    string pwd;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ir;
    DWORD readCnt;
    while (true) {
        ReadConsoleInput(hIn, &ir, 1, &readCnt);
        if (ir.EventType != KEY_EVENT || !ir.Event.KeyEvent.bKeyDown)
            continue;
        WCHAR ch = ir.Event.KeyEvent.uChar.UnicodeChar;
        if (ch == L'\r') {
            break;
        }
        if (ch == L'\b') {
            if (!pwd.empty()) {
                pwd.pop_back();
                cout << "\b \b";
                cout.flush();
            }
            continue;
        }
        if (ch >= 32 && ch <= 126) {
            pwd += (char)ch;
            cout << '.';
            cout.flush();
        }
    }
    cout << '\n';
    return pwd;
}

void download_s() {
    wchar_t buf[MAX_PATH];
    GetModuleFileNameW(NULL, buf, MAX_PATH);
    fs::path exepath(buf);
    fs::path target = exepath.parent_path() / ".." / ".." / "system" / "AtherOS_Other" / "download_AtherOS.exe";
    string cmd = "\"" + target.string() + "\"";
    system(cmd.c_str());
    Sleep(rnd() % 1700 + 500);
    system("cls");
    return;
}

void Boot() {
    Sleep(500);
    cout << "正在加载AtherOS_1: ";
    cout.flush();
    Sleep(500);
    for (int i = 0; i <= 100; i++) {
        cout << '\r' << "正在加载AtherOS_1: " << i << "%";
        cout.flush();
        if (rnd() % 15 + 1 != 1) {
            Sleep(rnd() % 30 + 10);
        } else {
            Sleep(rnd() % 300 + 100);
        }
        if (i == 0) {
            Sleep(rnd() % 700 + 300);
        }
    }
    cout.flush();
    cout << '\n';
    cout << "加载成功! 正在进入系统" << '\n';
    print_big("ATHEROS_1");
    cout.flush();
    cout << '\n';
    Sleep(rnd() % 2000 + 500);
    system("cls");
    cout.flush();
    system("cls");
    cout.flush();
    while (true) {
        cout << "请输入密码(默认密码为123456): ";
        cout.flush();
        string pwd = InputPass();
        cout.flush();
        cout << "请稍后, 正在验证密码";
        cout.flush();
        cout << '\n';
        cout.flush();
        if (Hash1(pwd) == setting.Hash_1 && Hash2(pwd) == setting.Hash_2 && Hash3(pwd) == setting.Hash_3 && Hash4(pwd) == setting.Hash_4) {
            cout << "密码正确!";
            Sleep(1000);
            break;
        } else {
            cout << "密码错误, 请重新输入";
            cout << "\n";
            continue;
        }
    }
    string Welcome_word = setting.Welcome_word;
    cout << Welcome_word << '\n';
    Sleep(rnd() % 1500 + 1200);
    system("cls");
    cout.flush();
    return;
}

void Time() {
    time_t t = time(NULL);
    tm lt{};
    localtime_s(&lt, &t);
    cout << setw(4) << setfill('0') << lt.tm_year + 1900 << "-"
         << setw(2) << setfill('0') << lt.tm_mon + 1 << "-"
         << setw(2) << setfill('0') << lt.tm_mday << " "
         << setw(2) << setfill('0') << lt.tm_hour << ":"
         << setw(2) << setfill('0') << lt.tm_min << ":"
         << setw(2) << setfill('0') << lt.tm_sec << '\n';
    cout.flush();
    return;
}

void About() {
    cout.flush();
    cout << "系统版本: " << setting.AtherOS_version << '\n';
    cout << "系统平台: " << "LZH_Ather1.0" << '\n';
    cout << "运行环境: " << "WindowsXP(x64)及以上, 推荐Windows10(x64)/11" << '\n';
}

void Change_Password() {
    bool old = false;
    for (int i = 1; i <= 3; i++) {
        cout << "请输入旧密码(默认密码为123456): ";
        cout.flush();
        string old_pwd = InputPass();
        cout << "请稍后, 正在验证密码";
        cout.flush();
        cout << '\n';
        cout.flush();
        if (Hash1(old_pwd) == setting.Hash_1 && Hash2(old_pwd) == setting.Hash_2 && Hash3(old_pwd) == setting.Hash_3 && Hash4(old_pwd) == setting.Hash_4) {
            cout << "密码正确!";
            old = true;
            Sleep(1000);
            break;
        } else {
            cout << "密码错误, 请重新输入";
            cout << "\n";
            continue;
        }
    }
    if (old) {
        for (int i = 1; i <= 3; i++) {
            cout << "请输入新密码: ";
            cout.flush();
            string new_pwd = InputPass();
            cout << '\n';
            cout << "请再次输入新密码: ";
            cout.flush();
            string pwd = InputPass();
            if (new_pwd != pwd) {
                cout << "两次输入的密码不一致, 请重新输入" << '\n';
                continue;
            } else {
                cout << "请稍后";
                cout << '\n';
                json j = LoadSetting();
                j["Hash_1"] = Hash1(pwd);
                j["Hash_2"] = Hash2(pwd);
                j["Hash_3"] = Hash3(pwd);
                j["Hash_4"] = Hash4(pwd);
                string path = "..\\AtherOS_File\\setting.json";
                fs::create_directories("..\\AtherOS_File");
                ofstream fout(path);
                fout << j.dump(4);
                fout.close();
                cout << "设置完成!";
                cout << '\n';
                InputSetting();
                return;
            }
        }
        cout << "设置失败! ";
        cout << '\n';
        return;
    } else {
        cout << "旧密码验证失败!";
        cout << '\n';
        return;
    }
}

void Help() {
    cout << "===============help===============" << '\n';
    cout << "1. time            查看本地时间" << '\n';
    cout << "2. about           查看系统信息" << '\n';
    cout << "3. change password 更改密码" << '\n';
    cout << "4. clean           清空屏幕" << '\n';
    cout << "5. exit            退出系统" << '\n';
    cout << "6. help            查看帮助" << '\n';
    return;
}

void Clean() {
    system("cls");
    cout.flush();
    return;
}

void Ather_Exit(){
    cout << "系统即将退出";
    Sleep(1000);
    exit(1);
    return;
}

void ShellLoop() {
    while (true) {
        cout << "AtherOS> ";
        cout.flush();
        vector<string> tokens = other::input();
        int num = tokens.size();
        if (num == 0)
            continue;
        if (num == 1 && tokens[0] == "time") {
            Time();
        } else if (num == 1 && tokens[0] == "about") {
            About();
        } else if (num == 2 && tokens[0] == "change" && tokens[1] == "password") {
            Change_Password();
        } else if (num == 1 && tokens[0] == "help") {
            Help();
        } else if (num == 1 && tokens[0] == "clean") {
            Clean();
        }else if(num == 1 && tokens[0] == "exit"){
            Ather_Exit();
        } else {
            cout << "未知指令，请重新输入" << '\n';
            cout.flush();
        }
    }
}
} // namespace system_op
using namespace system_op;

//!===================================================================

namespace other {
vector<string> input() {
    vector<string> args;
    string line;
    getline(cin, line);
    string cur;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == ' ') {
            args.push_back(cur);
            cur.clear();
        } else {
            cur += line[i];
        }
    }
    if (!cur.empty())
        args.push_back(cur);
    return args;
}

string byte2hex(unsigned char c) {
    stringstream ss;
    ss << hex << setw(2) << setfill('0') << (int)c;
    return ss.str();
}

string mat_to_hex(const vector<vector<unsigned char>> &mat) {
    string res;
    for (auto &row : mat)
        for (auto v : row)
            res += byte2hex(v);
    return res;
}

string Hash1(string src) {
    const int R = 8, C = 8;
    vector<vector<unsigned char>> mat(R, vector<unsigned char>(C, 0x23));
    int p = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (p < src.size())
                mat[i][j] = src[p++];
            else
                mat[i][j] = 0x23;
        }
    for (int i = 0; i < R; i++) {
        int step = i;
        vector<unsigned char> tmp(C);
        for (int j = 0; j < C; j++)
            tmp[j] = mat[i][(j + step) % C];
        mat[i] = tmp;
    }
    for (int j = 0; j < C; j++) {
        unsigned char x = mat[0][j];
        for (int i = 1; i < R; i++)
            x ^= mat[i][j];
        mat[0][j] = x;
    }
    return mat_to_hex(mat);
}

string Hash2(string src) {
    const int R = 10, C = 10;
    vector<vector<unsigned char>> mat(R, vector<unsigned char>(C, 0x23));
    int p = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (p < src.size())
                mat[i][j] = src[p++];
            else
                mat[i][j] = 0x23;
        }
    if (src.size() % 2 == 1) {
        swap(mat[0], mat[R - 1]);
        swap(mat[2], mat[5]);
    } else {
        for (int i = 0; i < R; i++)
            swap(mat[i][1], mat[i][8]);
    }
    for (int i = 0; i < R; i++) {
        int j = R - 1 - i;
        mat[i][j] ^= mat[j][i];
    }
    return mat_to_hex(mat);
}

string Hash3(string src) {
    const int R = 12, C = 12;
    vector<vector<unsigned char>> mat(R, vector<unsigned char>(C, 0x23));
    int p = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (p < src.size())
                mat[i][j] = src[p++];
            else
                mat[i][j] = 0x23;
        }
    for (int br = 0; br < R; br += 4)
        for (int bc = 0; bc < C; bc += 4) {
            for (int i = br; i < br + 4; i++)
                for (int j = bc; j < bc + 4; j++) {
                    if (i + 1 < R && j + 1 < C)
                        mat[i][j] = (mat[i][j] + mat[i + 1][j + 1]) % 256;
                }
        }
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i + 4 < R)
                mat[i][j] ^= mat[i + 4][j];
        }
    return mat_to_hex(mat);
}

string Hash4(string src) {
    const int R = 16, C = 16;
    vector<vector<unsigned char>> mat(R, vector<unsigned char>(C, 0x23));
    int p = 0;
    for (int i = 0; i < R; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < C; j++)
                if (p < src.size())
                    mat[i][j] = src[p++];
        } else {
            for (int j = C - 1; j >= 0; j--)
                if (p < src.size())
                    mat[i][j] = src[p++];
        }
    }
    vector<vector<unsigned char>> rot(C, vector<unsigned char>(R));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            rot[j][R - 1 - i] = mat[i][j];
    mat = rot;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            mat[i][j] ^= (i * j) & 0xFF;
    return mat_to_hex(mat);
}

} // namespace other
using namespace other;

//!===================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    LoadSetting();
    InputSetting();
    if (!system_download()) {
        download_s();
    }
    cout.flush();
    Boot();
    cout.flush();
    system("cls");
    cout << "========================AtherOS_1========================";
    cout << '\n';
    cout.flush();
    ShellLoop();
    return 0;
}
