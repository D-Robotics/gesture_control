// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef COMMON_H
#define COMMON_H

#include <chrono>
#include <memory>
#include <queue>
#include <vector>
#include <string>

#include "ai_msgs/msg/capture_targets.hpp"
#include "ai_msgs/msg/perception_targets.hpp"
#include "functional"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using namespace std::chrono_literals;  // NOLINT
using geometry_msgs::msg::Twist;

enum class GestureDirectionType { FRONT = 0, BACK, LEFT, RIGHT };

enum class GestureCtrlType {
  ThumbUp = 2,  // 点赞
  Victory = 3,
  Palm = 5,         // 手掌
  Okay = 11,        //  OK手势
  ThumbRight = 12,  // 大拇指向左
  ThumbLeft = 13,   // 大拇指向右
  Awesome = 14      // 666手势
};

enum class TrackingStatus { INITING = 0, TRACKING, LOST };

struct TrackInfo {
  TrackingStatus tracking_sta = TrackingStatus::INITING;
  uint64_t track_id = 0;
  uint64_t serial_lost_num = 0;
  uint64_t frame_ts_ms = 0;
  std::vector<int> present_rect{};
  int gesture = 0;
  int gesture_direction = -1;
};

struct TrackCfg {
  const GestureCtrlType wakeup_gesture = GestureCtrlType::Okay;  // OK手势
  const GestureCtrlType reset_gesture = GestureCtrlType::Palm;   // 手掌手势
  int activate_wakeup_gesture = 0;
  int track_serial_lost_num_thr = 100;
  float move_step = 0.1;
  float rotate_step = 0.5;
};

#endif  // COMMON_H
