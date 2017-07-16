﻿/*
Bulls And Cows标准规则猜数字
author: hulang
*/
#include <string>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "../../functions/function.hpp"
#include "../../robot.h"

using namespace std;
using namespace QQRobot;

namespace QQRobot {
    class BullsAndCows : public Game {
    public:
        handle_message_code handleMessage(Message &fromMsg, Message &toMsg) {
            string output;
            vector<string> strs = stringutil::split(fromMsg.getContent(), " ");

            LOOP:
            switch (gameState) {
            case unstarted:
            case ended:
                genRandQuestion();

                output = "我已经想出了一个无重复的四位数字，请开始猜吧~";
                if (strs.size() > 1 && strs[1] == "show")
                    output += "\n偷偷告诉你，数字是 " + string(answer);
                gameState = GameState::playing;
                break;
            case started:
            case playing:
                if (strs.size() > 1) {
                    if (strs[1] == "restart") {
                        gameState = GameState::unstarted;
                        goto LOOP;
                    }
                    else if (strs[1] == "end") {
                        gameState = GameState::ended;
                        output = "已结束";
                    }
                    else {
                        string input = strs[1];
                        if (input.length() != ANSWER_N) {
                            output = "答案位数不对";
                            break;
                        }

                        output = feedback(input);
                        if (output == "4A0B") {
                            output += "\n" + code_msg_at(fromMsg.from) + "恭喜你，猜对了！";
                            gameState = GameState::ended;
                        }
                    }
                }
                else {
                    output = "缺少答案";
                    break;
                }
                break;
            }

            toMsg.setContent(output);
            robot->sender->sendMessage(toMsg);
            return handle_message_code::block;
        }


    private:
        static const size_t ANSWER_N = 4;
        char answer[ANSWER_N + 1] = {0};

        void genRandQuestion() {
            srand(time(NULL));

            const size_t N = 10;
            char seedArray[] = "0123456789";
            for (size_t i = 0; i < ANSWER_N; i++) {
                size_t r = rand() % (N - i);
                answer[i] = seedArray[r];
                seedArray[r] = seedArray[N - i - 1];
            }

        }

        string feedback(string input) {
            int A = 0;//位置正确的数的个数
            int B = 0;//数字正确而位置不对的数的个数

            for (size_t ai = 0; ai < ANSWER_N; ai++) {
                if (answer[ai] == input[ai])
                    A++;
                else {
                    for (size_t i = 0; i < ANSWER_N; i++)
                        if (ai != i && answer[i] == input[ai])
                            B++;
                }
            }

            return to_string(A) + "A" + to_string(B) + "B";
        }
    };
}