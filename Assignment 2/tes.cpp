#include <iostream>
#include <random>
#include <set>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd()); // 梅森旋轉算法（Mersenne Twister）PRNG
    std::uniform_int_distribution<int> dis(1, 100000); // 範圍：1到100,000

    std::set<int> uniqueNumbers;

    while (uniqueNumbers.size() < 100000) {
        int randomNum = dis(gen);
        if (uniqueNumbers.insert(randomNum).second) {
            std::cout << randomNum << std::endl;
        }
    }

    return 0;
}
