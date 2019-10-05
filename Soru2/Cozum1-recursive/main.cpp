#include <bits/stdc++.h>
#include <vector>

using namespace std;

// bulunduğumuz sayının asal olup olmadığını bulan fonksiyon
bool isPrime(int num) {
    if(num < 2)
        return false;
    else if(num == 2)
        return true;
    for(int i = 2; i < num / 2 + 1; i++){
        if(num % i == 0)
            return false;
    }
    return true;
}

// recursive şeklinde sağ, sol, aşağı ve yukarıyı kontrol eden fonksiyon
int recurIsland(vector <vector<int> > &list, int x, int y){
    int temp = 0, biggest = 0;
    int temporary;
    if(isPrime(list[x][y]) || list[x][y] == -1){
        return 0;
    }
	// x eksenini kontrol ettiğim if state
    if(x < list.size()){
        temporary = list[x][y];
        list[x][y] = -1;
        if(x != 0 && !isPrime(list[x - 1][y]) && list[x - 1][y] != -1){
            temp += recurIsland(list, x - 1, y);
        }
        if(x != list.size() - 1 && !isPrime(list[x + 1][y]) && list[x + 1][y] != -1){
            temp += recurIsland(list, x + 1, y);
        }
        temp += temporary;
    }
    // y eksenini kontrol ettiğim if state
    if(y < list.size()){
        temporary = list[x][y];
        list[x][y] = -1;
        if(y != 0 && !isPrime(list[x][y - 1]) && list[x][y - 1] != -1){
            temp += recurIsland(list, x, y - 1);
        }
        if(y != list.size() - 1 && !isPrime(list[x][y + 1]) && list[x][y + 1] != -1) {
            temp += recurIsland(list, x, y + 1);
        }
        if(temporary != -1)
            temp += temporary;
    }
    return temp;
}

// aramaya başlanan ana fonksiyon
int getMaxPrimeIsland(vector <vector<int> > &list, int x, int y){
    int temp = 0, biggest = 0;

    for(int i = x; i < list.size(); ++i){
        for(int j = y; j < list.size(); ++j){
            if(!isPrime(list[i][j])){
            	// eğer bulunduğumuz yer aramaya müsait ise aramaya başlıyoruz.
                if(x < list.size() || y < list.size()){
                    temp = recurIsland(list, i, j);
                    if(temp > biggest){
                        biggest = temp;
                    }
                }
            }
        }
    }
    return biggest;
}

int main()
{
    int size;
    cin >> size;
    vector<vector<int>> list;
    list.resize(size, vector<int>(size, 0));
    int result[size];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int input;
            cin >> input;
            list[j][i] = input;
        }
    }

    cout << getMaxPrimeIsland(list, 0, 0);
    return 0;
}