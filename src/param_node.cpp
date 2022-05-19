// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#include <string>
#include "include/param_node.h"

ParametersClass::ParametersClass(TrackCfg *cfg, const std::string &node_name)
    : Node(node_name) {
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ParametersClass node construct");
  cfg_ = cfg;
  if (cfg_) {
    this->declare_parameter<int>("track_serial_lost_num_thr",
                                 cfg_->track_serial_lost_num_thr);
    this->declare_parameter<int>("activate_wakeup_gesture",
                                 cfg_->activate_wakeup_gesture);
    this->declare_parameter<float>("move_step", cfg_->move_step);
    this->declare_parameter<float>("rotate_step", cfg_->rotate_step);
    timer_ = this->create_wall_timer(
        1000ms, std::bind(&ParametersClass::Respond, this));
  }
}

void ParametersClass::Respond() {
  if (!cfg_) return;
  this->get_parameter("track_serial_lost_num_thr",
                      cfg_->track_serial_lost_num_thr);
  this->get_parameter("activate_wakeup_gesture", cfg_->activate_wakeup_gesture);
  this->get_parameter("move_step", cfg_->move_step);
  this->get_parameter("rotate_step", cfg_->rotate_step);

  std::stringstream ss;
  ss << "track_serial_lost_num_thr: " << cfg_->track_serial_lost_num_thr
     << std::endl;
  ss << "activate_wakeup_gesture: " << cfg_->activate_wakeup_gesture
     << std::endl;
  ss << "move_step: " << cfg_->move_step << std::endl;
  ss << "rotate_step: " << cfg_->rotate_step << std::endl;
  if (first_dump_config_) {
    first_dump_config_ = false;
    RCLCPP_WARN(this->get_logger(), "TrackCfg param are\n%s", ss.str().data());
  } else {
    RCLCPP_DEBUG(this->get_logger(), "TrackCfg param are\n%s", ss.str().data());
  }
}
