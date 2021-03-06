﻿/*
机器人功能抽象
author: hulang
*/
#ifndef ROBOT_FUNCTION_H
#define ROBOT_FUNCTION_H

#include <string>
#include "message.hpp"
#include "robot.h"

using namespace std;
using namespace QQRobot;

namespace QQRobot
{
    class Function
    {
    public:
        enum handle_message_code {
            syntax_error,
            block,
            ignore
        };

        /*
        机器人的状态是所有功能共享的
        */
        Robot *robot;

        Function() {}

        virtual handle_message_code handleMessage(Message &fromMsg, Message &toMsg) = 0;

        static string functionInfo()
        {
            string info = code_msg_face(66) + "功能列表：\n";
            info += "* 如果你@我，我也会@你。\n";
            info += "* 执行JS程序：eval:\n";
            info += "* 天气预报：天气\n";
            info += "* osu!查询：!stat\n";
            info += "* 黑名单：black\n";
            //info += "* 代发消息：send\n";
            //info += "* 代发消息到群：sendtogroup\n";
            info += "* 命令用法查询：!man <命令名>，例如：!man eval\n";
            info += "* 游戏 - Bulls and Cows猜数字：AB\n";
            info += "* 关于：about\n";
            info += "* 功能：function-list\n";
            return info;
        }
    };
}

#endif // ! FUNCTION_H
