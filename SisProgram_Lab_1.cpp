#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <set> 

using namespace std;

// Функція для перевірки, чи символ є літерою 
bool isAlphabetic(char c) {
    return isalpha(static_cast<unsigned char>(c)) != 0;
}

// Функція для обчислення відстані між двома словами
int Distance(const string& word1, const string& word2) {
    int distance = 0;
    int len1 = word1.length();
    int len2 = word2.length();

    int i = 0;
    int j = 0;

    // Порівняння символів у двох словах
    while (i < len1 && j < len2) {
        char char1 = word1[i];
        char char2 = word2[j];
        if (isAlphabetic(char1) && isAlphabetic(char2)) {
            if (char1 != char2) {
                distance++; // Збільшення відстані на 1, якщо символи відрізняються
            }
            i++;
            j++;
        }
        else {
            if (!isAlphabetic(char1)) {
                i++;
            }
            if (!isAlphabetic(char2)) {
                j++;
            }
        }
    }

    // Додавання різниці у довжинах рядків до відстані
    distance += abs(len1 - len2);

    return distance;
}

int main() {
    ifstream inputFile("H:\\visual\\SisProgram_Lab_1\\test.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    string text;
    string line; // Змінна для зберігання кожного рядка файлу

    // Зчитування файлу 
    while (getline(inputFile, line)) {
        text += line + " "; // Додавання кожного рядка та пробілу до тексту
    }

    inputFile.close();

    vector<string> words; // Вектор для зберігання слів з рядка
    string currentWord; // Змінна для зберігання поточного слова
    set<pair<string, string>> uniquePairs; // Множина для зберігання унікальних пар слів з максимальною відстанню

    // Розбиття рядка на слова і додавання їх до відповідних контейнерів
    for (char c : text) {
        if (isAlphabetic(c)) {
            currentWord += c;
        }
        else {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
    }

    // Додавання останнього слова до вектора
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    int maxDistance = 0; // Змінна для зберігання максимальної відстанні

    // Обчислення відстаней між парами слів і збереження унікальних пар
    for (size_t i = 0; i < words.size(); i++) {
        for (size_t j = i + 1; j < words.size(); j++) {
            int distance = Distance(words[i], words[j]);
            if (distance > maxDistance) {
                maxDistance = distance; // Оновлення максимальної відстані
                uniquePairs.clear(); // Очищення множини унікальних пар слів
                uniquePairs.insert(make_pair(words[i], words[j])); // Додавання пари з новою максимальною відстанню
            }
            else if (distance == maxDistance) {
                // Перевірка, чи зеркальна пара вже існує у множині
                if (uniquePairs.find(make_pair(words[j], words[i])) == uniquePairs.end()) {
                    uniquePairs.insert(make_pair(words[i], words[j])); // Додавання пари з однаковою відстанню
                }
            }
        }
    }

    // Виведення слів з максимальною відстанню
    cout << "Words with max distance (" << maxDistance << "):" << endl;
    for (const auto& pair : uniquePairs) {
        cout << pair.first << " || " << pair.second << endl;
    }

    return 0;
}
