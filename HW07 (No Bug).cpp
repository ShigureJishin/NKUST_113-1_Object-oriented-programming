#include <stdio.h>
#include <stdbool.h>

// 提取卡牌的點數（Rank）的函數
int getRank(int card) {
    return (card - 1) % 13 + 1;  // 卡牌編號從1到52，此公式給出點數範圍為1 (A) 到13 (K)
}

// 提取卡牌的花色（Suit）的函數
int getSuit(int card) {
    return (card - 1) / 13;  // 返回 0 表示黑桃, 1 表示紅桃, 2 表示方塊, 3 表示梅花
}

// 檢查卡牌是否形成順子，包括 10, J, Q, K, A 的特殊情況
bool isStraight(int ranks[]) {
    // 將點數進行排序
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (ranks[i] > ranks[j]) {
                int temp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = temp;
            }
        }
    }
    
    // 檢查是否為一般順子（連續的點數）
    bool regularStraight = true;
    for (int i = 1; i < 5; i++) {
        if (ranks[i] != ranks[i - 1] + 1) {
            regularStraight = false;
            break;
        }
    }

    // 特殊情況，檢查 A (1) 作為順子中的最大牌 (10, J, Q, K, A)
    bool aceHighStraight = (ranks[0] == 1 && ranks[1] == 10 && ranks[2] == 11 && ranks[3] == 12 && ranks[4] == 13);

    return regularStraight || aceHighStraight;
}

// 檢查所有卡牌是否為同一花色（同花）
bool isFlush(int suits[]) {
    for (int i = 1; i < 5; i++) {
        if (suits[i] != suits[0]) {
            return false;
        }
    }
    return true;
}


int main() {
    while (1) {
        int n;  // 玩家數量
        scanf("%d", &n);

        if (n <= 0)
            break;

        int player[100][5], ranks[100][5], suits[100][5], score[100] = {0};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 5; j++) {
                scanf("%d", &player[i][j]);
                ranks[i][j] = getRank(player[i][j]);
                suits[i][j] = getSuit(player[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            bool straight = isStraight(ranks[i]);
            bool flush = isFlush(suits[i]);

            if (straight && flush) {
                score[i] = 7;  // 同花順
            } else if (straight) {
                score[i] = 4;  // 順子
            } else {
                // 其他組合：四條、葫蘆、三條、兩對、一對
                int numCount[14] = {0};  // 記錄數字出現次數
                for (int j = 0; j < 5; j++) {
                    numCount[ranks[i][j]]++;
                }

                int pair = 0, three = 0, four = 0;
                for (int j = 1; j <= 13; j++) {
                    if (numCount[j] == 4) {
                        four = 1;
                    } else if (numCount[j] == 3) {
                        three = 1;
                    } else if (numCount[j] == 2) {
                        pair++;
                    }
                }

                if (four) {
                    score[i] = 6;  // 四條
                } else if (three && pair) {
                    score[i] = 5;  // 葫蘆
                } else if (three) {
                    score[i] = 3;  // 三條
                } else if (pair == 2) {
                    score[i] = 2;  // 兩對
                } else if (pair == 1) {
                    score[i] = 1;  // 一對
                } else {
                    score[i] = 0;  // 雜牌
                }
            }

            // 輸出分數
            printf("%d\n", score[i]);
        }
    }

    return 0;
}

