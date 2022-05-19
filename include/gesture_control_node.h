// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef GESTURE_STRATEGY_NODE_H
#define GESTURE_STRATEGY_NODE_H

#include <string>
#include "include/common.h"

using geometry_msgs::msg::Twist;
using SmartCbType = std::function<void(
    const ai_msgs::msg::PerceptionTargets::ConstSharedPtr &msg)>;

class GestureControlNode : public rclcpp::Node {
 public:
  GestureControlNode(const std::string &node_name, SmartCbType smart_cb);

  void RobotCtl(const Twist &msg) const;

 private:
  rclcpp::Subscription<ai_msgs::msg::PerceptionTargets>::SharedPtr
      ai_msg_subscription_ = nullptr;
  void SmartTopicCallback(
      const ai_msgs::msg::PerceptionTargets::ConstSharedPtr msg);

  std::string ai_msg_sub_topic_name_ = "/hobot_hand_gesture_detection";
  SmartCbType smart_cb_ = nullptr;
  rclcpp::Subscription<ai_msgs::msg::PerceptionTargets>::SharedPtr
      smart_subscription_ = nullptr;

  // topic name for turtle sim is "turtle1/cmd_vel" and for robot is "/cmd_vel"
  std::string twist_pub_topic_name_ = "/cmd_vel";
  rclcpp::Publisher<Twist>::SharedPtr twist_publisher_ = nullptr;
};

#endif  // GESTURE_STRATEGY_NODE_H
