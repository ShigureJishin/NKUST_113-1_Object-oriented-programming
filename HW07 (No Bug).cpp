#include <stdio.h>
#include <stdbool.h>

// �����d�P���I�ơ]Rank�^�����
int getRank(int card) {
    return (card - 1) % 13 + 1;  // �d�P�s���q1��52�A���������X�I�ƽd��1 (A) ��13 (K)
}

// �����d�P�����]Suit�^�����
int getSuit(int card) {
    return (card - 1) / 13;  // ��^ 0 ��ܶ®�, 1 ��ܬ���, 2 ��ܤ��, 3 ��ܱ���
}

// �ˬd�d�P�O�_�Φ����l�A�]�A 10, J, Q, K, A ���S���p
bool isStraight(int ranks[]) {
    // �N�I�ƶi��Ƨ�
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (ranks[i] > ranks[j]) {
                int temp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = temp;
            }
        }
    }
    
    // �ˬd�O�_���@�붶�l�]�s���I�ơ^
    bool regularStraight = true;
    for (int i = 1; i < 5; i++) {
        if (ranks[i] != ranks[i - 1] + 1) {
            regularStraight = false;
            break;
        }
    }

    // �S���p�A�ˬd A (1) �@�����l�����̤j�P (10, J, Q, K, A)
    bool aceHighStraight = (ranks[0] == 1 && ranks[1] == 10 && ranks[2] == 11 && ranks[3] == 12 && ranks[4] == 13);

    return regularStraight || aceHighStraight;
}

// �ˬd�Ҧ��d�P�O�_���P�@���]�P��^
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
        int n;  // ���a�ƶq
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
                score[i] = 7;  // �P�ᶶ
            } else if (straight) {
                score[i] = 4;  // ���l
            } else {
                // ��L�զX�G�|���B��Ī�B�T���B���B�@��
                int numCount[14] = {0};  // �O���Ʀr�X�{����
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
                    score[i] = 6;  // �|��
                } else if (three && pair) {
                    score[i] = 5;  // ��Ī
                } else if (three) {
                    score[i] = 3;  // �T��
                } else if (pair == 2) {
                    score[i] = 2;  // ���
                } else if (pair == 1) {
                    score[i] = 1;  // �@��
                } else {
                    score[i] = 0;  // ���P
                }
            }

            // ��X����
            printf("%d\n", score[i]);
        }
    }

    return 0;
}

