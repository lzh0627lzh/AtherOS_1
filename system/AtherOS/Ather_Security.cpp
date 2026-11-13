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

struct SettingData {
    bool system_download;
    string AtherOS_version;
    int AtherOS_vnum;
    string Welcome_word;
    string Hash_1;
    string Hash_2;
    string Hash_3;
    string Hash_4;
} setting1, setting2;

const string SET_PATH = "..\\AtherOS_File\\setting.json";

void SaveSetting(const SettingData &s) {
    json j;
    j["system_download"] = s.system_download;
    j["AtherOS_version"] = s.AtherOS_version;
    j["AtherOS_vnum"] = s.AtherOS_vnum;
    j["Welcome_word"] = s.Welcome_word;
    j["Hash_1"] = s.Hash_1;
    j["Hash_2"] = s.Hash_2;
    j["Hash_3"] = s.Hash_3;
    j["Hash_4"] = s.Hash_4;

    fs::create_directories("..\\AtherOS_File");
    ofstream fout(SET_PATH);
    fout << j.dump(4);
    fout.close();
}

void init_setting(json &j) {
    j["system_download"] = false;
    j["AtherOS_version"] = "1.0.1(2610.1030)";
    j["AtherOS_vnum"] = 1011;
    j["Welcome_word"] = "欢迎!";
    j["Hash_1"] = Hash1("123456");
    j["Hash_2"] = Hash2("123456");
    j["Hash_3"] = Hash3("123456");
    j["Hash_4"] = Hash4("123456");
    SaveSetting(setting1);
}

void LoadSetting(SettingData &out) {
    fs::create_directories("..\\AtherOS_File");
    ifstream fin(SET_PATH);
    json j;
    if (!fin.is_open()) {
        init_setting(j);
        fin.open(SET_PATH);
    }
    try {
        fin >> j;
    } catch (const json::parse_error &) {
        init_setting(j);
        fin.open(SET_PATH);
        fin >> j;
    }
    fin.close();
    out.system_download = j.value<bool>("system_download", true);
    out.AtherOS_version = j.value<string>("AtherOS_version", "1.1.0(2611.1027)");
    out.AtherOS_vnum = j.value<int>("AtherOS_vnum", 1100);
    out.Welcome_word = j.value<string>("Welcome_word", "欢迎!");
    out.Hash_1 = j.value<string>("Hash_1", Hash1("123456"));
    out.Hash_2 = j.value<string>("Hash_2", Hash2("123456"));
    out.Hash_3 = j.value<string>("Hash_3", Hash3("123456"));
    out.Hash_4 = j.value<string>("Hash_4", Hash4("123456"));
}

int main() {
    LoadSetting(setting2);
    while (true) {
        LoadSetting(setting1);
        bool diff = (setting1.Hash_1 != setting2.Hash_1) || (setting1.Hash_2 != setting2.Hash_2) || (setting1.Hash_3 != setting2.Hash_3) || (setting1.Hash_4 != setting2.Hash_4);
        if (diff) {
            int r = MessageBoxW(NULL, L"密码发生改变, 请问是否保持更改?", L"Ather Security Centre", MB_YESNO);
            if (r == IDYES) {
                setting2 = setting1;
            } else {
                SaveSetting(setting2);
            }
        }
        Sleep(300);
    }
    return 0;
}
