// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef GESTURE_CONTROL_ENGINE_H
#define GESTURE_CONTROL_ENGINE_H

#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "include/common.h"
#include "include/gesture_control_node.h"
#include "include/param_node.h"

class GestureControlEngine {
 public:
  static std::shared_ptr<GestureControlEngine> Instance();
  ~GestureControlEngine();

  void FeedSmart(const ai_msgs::msg::PerceptionTargets::ConstSharedPtr &msg);
  void UpdateRobotPose(const geometry_msgs::msg::Twist::SharedPtr &pose);

  std::vector<std::shared_ptr<rclcpp::Node>> GetNodes() {
    std::vector<std::shared_ptr<rclcpp::Node>> node_ptrs;
    node_ptrs.push_back(param_node_);
    node_ptrs.push_back(gesture_control_node_);
    return node_ptrs;
  }

 private:
  GestureControlEngine();

  void RunStrategy(const ai_msgs::msg::PerceptionTargets::ConstSharedPtr &msg);
  void ProcessSmart(const ai_msgs::msg::PerceptionTargets::ConstSharedPtr &msg);
  // rotate robot
  // direction: 0 left, 1 right; unit of step is radian
  void DoRotate(int direction, float step = 0.5);
  // direction: 0 front, 1 back, 2 left, 3 right; unit of step is m/s
  void DoMove(int direction, float step = 0.05);
  void CancelMove();
  // push dest world position msg to queue, which will be pub using action
  void FeedMovePoseMsg(const Twist::SharedPtr &pose);

  std::shared_ptr<ParametersClass> param_node_ = nullptr;
  std::shared_ptr<GestureControlNode> gesture_control_node_ = nullptr;

  TrackInfo track_info_;
  bool start_ = false;

  size_t queue_len_limit_ = 10;
  std::queue<ai_msgs::msg::PerceptionTargets::ConstSharedPtr> smart_queue_;
  std::mutex smart_queue_mtx_;
  std::condition_variable smart_queue_condition_;

  std::shared_ptr<std::thread> smart_process_task_ = nullptr;
  std::shared_ptr<std::thread> feed_pose_task_ = nullptr;

  TrackCfg track_cfg_;
  bool last_ctrl_is_cancel_ = false;
};

#endif  // GESTURE_CONTROL_ENGINE_H
