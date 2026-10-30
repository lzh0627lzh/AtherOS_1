#include <bits/stdc++.h>
#include <windows.h>
#include <nlohmann/json.hpp>
using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::random_device rd;
mt19937 rnd(rd());

void SetCursorVisible(bool show) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(hOut, &ci);
    ci.bVisible = show;
    SetConsoleCursorInfo(hOut, &ci);
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Sleep(rnd() % 1000 + 800);
    cout << "============AtherOS_1 setup============\n";
    Sleep(500);
    SetCursorVisible(false);
    for (int i = 1; i <= rnd() % 3 + 2; i++) {
        cout << "\r" << setw(30) << "" << "\r";
        cout << "请稍后";
        cout.flush();
        for (int j = 1; j <= 3; j++) {
            Sleep(400);
            cout << ".";
            cout.flush();
        }
        Sleep(400);
    }
    cout << "\r" << setw(30) << "" << "\r";
    cout.flush();

    for(int i = 0;i <= 100;i++){
        cout << "\r[";
        for(int j = 1;j < i / 5;j++){
            cout << "=";
        }
        cout << ">";
        for(int j = 1;j < 20 - i / 5 + 1;j++){
            if(i == 0 && j == 20){
                break;
            }
            cout << " ";
        }
        cout << "] " << i << "%  ";
        cout.flush();
        Sleep(rnd() % 25 + 1);
        if(i == 0){
            Sleep(rnd() % 700 + 300);
        }
    }
    Sleep(500);
    cout << "\n安装环境准备就绪, 即将开始安装\n";
    Sleep(1000);

    for(int i = 0;i <= 90;i++){
        cout << "\r[";
        for(int j = 1;j < i / 5;j++){
            cout << "=";
        }
        cout << ">";
        for(int j = 1;j < 20 - i / 5 + 1;j++){
            if(i == 0 && j == 20){
                break;
            }
            cout << " ";
        }
        cout << "] " << i << "%  ";
        cout.flush();
        if(rnd() % 15 + 1 != 1){
            Sleep(rnd() % 70 + 30);
        }else{
            Sleep(rnd() % 500 + 300);
        }
        if(i == 0){
            Sleep(rnd() % 700 + 300);
        }
    }

    for(int i = 90;i <= 100;i++){
        cout << "\r[";
        for(int j = 1;j < i / 5;j++){
            cout << "=";
        }
        cout << ">";
        for(int j = 1;j < 20 - i / 5 + 1;j++){
            if(i == 0 && j == 20){
                break;
            }
            cout << " ";
        }
        cout << "] " << i << "%";
        cout.flush();
        if(rnd() % 10 + 1 != 1){
            Sleep(rnd() % 300 + 100);
        }else{
            Sleep(rnd() % 700 + 500);
        }
    }
    cout << "\n安装完成, 开始校验文件\n";

    for(int i = 0;i <= 100;i++){
        cout << "\r[";
        for(int j = 1;j < i / 5;j++){
            cout << "=";
        }
        cout << ">";
        for(int j = 1;j < 20 - i / 5 + 1;j++){
            if(i == 0 && j == 20){
                break;
            }
            cout << " ";
        }
        cout << "] " << i << "%  ";
        cout.flush();
        Sleep(rnd() % 40 + 10);
        if(i == 0){
            Sleep(rnd() % 700 + 300);
        }
    }
    cout << "\n系统安装完成, 即将重启";
    SetCursorVisible(true);

    string path = "..\\AtherOS_File\\setting.json";
    fs::create_directories("..\\AtherOS_File");
    ifstream fin(path);
    json j;
    if (!fin.is_open()) {
        j["system_download"] = false;
        j["AtherOS_version"] = "1.0.1(2610.1024)";
        j["AtherOS_vnum"] = 1010;
        j["Welcome_word"] = "欢迎!";
        ofstream fout(path);
        fout << j.dump(4);
        fout.close();
        fin.open(path);
    }
    try {
        fin >> j;
    } catch (const json::parse_error &e) {
        j["system_download"] = false;
        j["AtherOS_version"] = "1.0.0(1000.1024)";
        j["Welcome_word"] = "欢迎!";
        ofstream fout(path);
        fout << j.dump(4);
        fout.close();
    }
    fin.close();
    j["system_download"] = true;
    ofstream fout(path);
    fout << j.dump(4);
    fout.close();
    return 0;
}
