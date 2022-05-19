// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef PARAM_NODE_H
#define PARAM_NODE_H

#include <string>
#include "include/common.h"

class ParametersClass : public rclcpp::Node {
 public:
  ParametersClass(
      TrackCfg *cfg,
      const std::string &node_name = "gesture_control_parameter_node");
  void Respond();

 private:
  TrackCfg *cfg_ = nullptr;
  rclcpp::TimerBase::SharedPtr timer_;
  bool first_dump_config_ = true;
};

#endif  // PARAM_NODE_H
