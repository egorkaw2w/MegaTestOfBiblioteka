#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    HINSTANCE hDLL = LoadLibrary(L"BibliotekaSearcher.dll");
    if (hDLL == NULL) {
        cerr << "Не удалось загрузить DLL.\n";
        return 1;
    }

    typedef bool(*FindCharactersFunc)(const char*, const char*);
    FindCharactersFunc findCharacters = (FindCharactersFunc)GetProcAddress(hDLL, "FindCharacters");
    if (findCharacters == NULL) {
        cerr << "Не удалось получить указатель на функцию в DLL.\n";
        FreeLibrary(hDLL);
        return 1;
    }

    wstring inputStringWide;
    wcout << L"Введите строку: ";
    wcin.ignore();
    getline(wcin, inputStringWide);

    string inputString(inputStringWide.begin(), inputStringWide.end());

    wstring charactersToFindWide;
    wcout << L"Введите символы для поиска: ";
    wcin.ignore();
    getline(wcin, charactersToFindWide);

    string charactersToFind(charactersToFindWide.begin(), charactersToFindWide.end());

    bool result = findCharacters(inputString.c_str(), charactersToFind.c_str());

    if (result) {
        cout << "Все символы найдены в строке.\n";
    }
    else {
        cout << "Не все символы найдены в строке.\n";
    }

    FreeLibrary(hDLL);

    return 0;
}