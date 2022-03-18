#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;
// для сжатия файла (Алгоритм Хаффмана с деревом)
string buildHuffmanTree(string);
struct Node
{
    char ch;
    int freq;
    Node* left, * right;
};
Node* getNode(char, int, Node*, Node*);
void encode(Node*, string, unordered_map<char, string>&);
void decode(Node*, int&, string);
void Input(int** Arr, int size) {
    for (int i(0); i < size; i++) {
        for (int j(0); j < size; j++) {
            cout << "Element matrix [" << i << "][" << j << "]=";
            cin >> Arr[i][j];
        }
    }
}
void Print(int** Arr, int size) {
    for (int i(0); i < size; i++) {
        for (int j(0); j < size; j++) {
            cout << Arr[i][j] << " ";
        }
        cout << endl;
    }
}
void SumOfMatrices(int** matrice1, int** matrice2, int** matrice3, int size) {
    for (int i(0); i < size; i++) {
        for (int j(0); j < size; j++) {
            matrice3[i][j] = matrice1[i][j] + matrice2[i][j];
        }
    }
}
void MultiplicationOfMatrices(int** matrice1, int** matrice2, int** matrice3, int size) {
    for (int i(0); i < size; i++) {
        for (int j(0); j < size; j++) {
            matrice3[i][j] = (matrice1[i][j]) * (matrice2[i][j]);
        }
    }
}
void ReadFromFile(string FileName, int** matrice,int row,int col) {
    int i = 0 , j = 0;
    ifstream file;
    file.open(FileName);
    if (file.is_open()) {
        for (int i = 0; i < row && !file.eof(); i++) {
            for (int j = 0; j < col && !file.eof(); j++) {
                file >> matrice[i][j];
            }
        }
    }
    else {
        cout << "Can't open the file!" << endl;
    }
}
void Framework() {
    cout << "1. Заполнить матрицы" << endl;
    cout << "2. Считать с файла" << endl;
    cout << "3. Вывести матрицы на консоль" << endl;
    cout << "4. Сумма матриц" << endl;
    cout << "5. Произведение матриц" << endl;
    cout << "6. Сжатие и запись в файл" << endl;
    cout << "0. Выход" << endl;
}
void PrintToFile(string temp) {
    ofstream file;
    file.open("Encoded.txt");
    file << "Код Хаффмана для сжатия файла: " << endl;
    file << temp;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    string temp;
    int** matrice1, ** matrice2, ** matrice3;
    int size, key, MatriceIsReady = 0;
    cout << "Введите размер матриц: ";
    cin >> size;
    // Выделяем память
    matrice1 = new int* [size];
    for (int i(0); i < size; i++) {
        matrice1[i] = new int[size]; 
    }
    matrice2 = new int* [size];
    for (int i(0); i < size; i++) { 
        matrice2[i] = new int[size]; 
    }
    matrice3 = new int* [size];
    for (int i(0); i < size; i++) {
        matrice3[i] = new int[size];
    }
    while (true) {
        Framework();
        cout << "Выберите функцию: ";
        cin >> key;
        switch (key) {
        case 1: {
            Input(matrice1, size);
            Input(matrice2, size);
            MatriceIsReady = 1;
            break;
        }
        case 2:
            ReadFromFile("Matrice1.txt", matrice1, size, size);
            ReadFromFile("Matrice2.txt", matrice2, size, size);
            break;
        case 3: {
            if (MatriceIsReady == 1) {
                cout << "\tМатрица 1:" << endl;
                Print(matrice1, size);
                cout << "\tМатрица 2:" << endl;
                Print(matrice2, size);
            }
            else
                cout << "Для начала стоит заполнить матрицу(выберите 1)!" << endl << endl;
            break;
        }
        case 4: {
            if (MatriceIsReady == 1) {
                matrice3 = new int* [size];
                for (int i(0); i < size; i++) { matrice3[i] = new int[size]; }
                SumOfMatrices(matrice1, matrice2, matrice3, size);
                cout << "Сумма матриц: " << endl;
                Print(matrice3, size);

                for (int i(0); i < size; i++)
                    delete[] matrice3[i];
                delete[] matrice3;
            }
            else
                cout << "Для начала стоит заполнить матрицу(выберите 1)!" << endl << endl;
            break;
        }
        case 5: {
            if (MatriceIsReady == 1) {
                matrice3 = new int* [size];
                for (int i(0); i < size; i++) { matrice3[i] = new int[size]; }

                MultiplicationOfMatrices(matrice1, matrice2, matrice3, size);
                cout << "Умножение матриц: " << endl;
                Print(matrice3, size);

                for (int i(0); i < size; i++) {
                    delete[] matrice3[i];
                }
                delete[] matrice3;
            }
            else
                cout << "Для начала стоит заполнить матрицу(выберите 1)!" << endl << endl;
            break;
        }
        case 6:
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    char temp1[1];
                    temp1[0] = matrice3[i][j];
                    temp.append(temp1);
                }
            }
            temp = buildHuffmanTree(temp);
            PrintToFile(temp);
            break;
        case 0: {
            cout << "Досвидания!";
            return 0;
        }
        }
    }
    // Удаляем память
    for (int i = 0; i < size; i++) {
        delete[] matrice1[i];
    }
    delete[] matrice1;

    for (int i = 0; i < size; i++) {
        delete[] matrice2[i];
    }
    delete[] matrice2;
    return 0;
}
// Реализуем алгоритм Хаффмана для сжатия файла


// Функция добавления новой клетки в дерево
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Сравнение
struct comp
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

// итерация по дереву
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str)
{
    if (root == nullptr) {
        return;
    }
    if (!root->left && !root->right)
    {
        cout << root->ch;
        return;
    }
    index++;
    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

// Создание дерева Хаффмана
string buildHuffmanTree(string text)
{
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
    while (pq.size() != 1)
    {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();	pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }
    return str;
}
