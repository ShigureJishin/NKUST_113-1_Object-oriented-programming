#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>

#define MAX_LEN 500

using namespace std;

class Player {
  public:

    int getScore() {
      return score;
    }

    void getAllCards() {
      for (int i = 0; i < 5; ++i) {
        cout << cards[i] << " ";
      }
    }

    void saveCards(int index, int card) {
      cards[index] = card;
      
      suit[index] = (card - 1) / 13;  // 花色 (0~3)
      rank[index] = (card - 1) % 13;  // 數字 (0~12，代表A~K)
    }

    void countScore() {
      score = 0;
      int suitCount[4] = {0, 0, 0, 0};
      int rankCount[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

      for (int i = 0; i < 5; ++i) {
        suitCount[suit[i]]++;
        rankCount[rank[i]]++;
      }

      /* 同花 */
      int isFlush = 0;
      for (int i = 0; i < 4; ++i) {
        if (suitCount[i] == 5) {
          isFlush = 1;
          break;
        }
      }

      /* 順子 */
      int isStraight = 0;
      int check = 0;
      for (int i = 0; i < 13; ++i) {
        if (rankCount[i] > 0) {
          check++;
        } else {
          check = 0;
        }

        if (check == 5) {
          isStraight = 1;
          break;
        }
      }

      // A, 10, J, Q, K
      if (rankCount[0] > 0 && rankCount[9] > 0 && rankCount[10] > 0 && rankCount[11] > 0 && rankCount[12] > 0) {
        isStraight = 1;
      }

      /* 四條 & 葫蘆 & 三條 & 兩對 & 對子 */
      int hasFour = 0, hasThree = 0, hasPair = 0;
      for (int j = 0; j < 13; j++) {
        if (rankCount[j] == 4) {
          hasFour++;
        } else if (rankCount[j] == 3) {
          hasThree++;
        } else if (rankCount[j] == 2) {
          hasPair++;
        }
      }

      if (isFlush && isStraight) {
        score = 7;
      } else if (hasFour) {
        score = 6;
      } else if (hasThree && hasPair) {
        score = 5;
      } else if (isStraight) {
        score = 4;
      } else if (hasThree) {
        score = 3;
      } else if (hasPair == 2) {
        score = 2;
      } else if (hasPair == 1) {
        score = 1;
      } else {
        score = 0;
      }
    }

  private:
    int score = 0;
    int cards[5];
    int suit[5];
    int rank[5];
};  

int main() {
  while (true)
  {
    int playerCount;

    /* 輸入玩家數 */
    cin >> playerCount;

    if (playerCount <= 0) break;

    vector<Player> players(playerCount);

    /* 存取每位玩家的牌 */
    for (int i = 0; i < playerCount; ++i) {
      for (int j = 0; j < 5; ++j) {
        int card;
        cin >> card;
        players[i].saveCards(j, card);
      }
    }

    /* 分數計算 */
    for (int i = 0; i < playerCount; ++i) {
      players[i].countScore();
    }

    /* 輸出每位玩家的分數 */
    for (int i = 0; i < playerCount; ++i) {
      cout << players[i].getScore() << endl;
    }   
  }

  return 0;
}