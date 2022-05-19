// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#include <cstdio>

#include "include/gesture_control_engine.h"

int main(int argc, char** argv) {
  std::stringstream ss;
  ss << "\n\tThis is gesture control package.\n\n"
     << "============================================\n"
     << "\tgesture control usage\n"
     << "\nWake up gesture is \"Okay\".\n"
     << "Reset gesture is \"Palm\".\n"
     << "Gesture control definitions are:\n"
     << "\t\"Awesome\": move front. (close from controler)\n"
     << "\t\"Victory\": move back. (far from controler)\n"
     << "\t\"ThumbRight\": rotate robot to right. (rotate to the thumb "
        "orientation)\n"
     << "\t\"ThumbLeft\": rotate robot to left. (rotate to the thumb "
        "orientation)\n"
     << "Control will be paused if gesture is lost.\n"
     << "Control will be reset if hand is lost or the gesture is \"Palm\".\n"
     << "============================================\n";
  std::cout << ss.str() << std::endl;

  rclcpp::init(argc, argv);

  rclcpp::executors::SingleThreadedExecutor exec;
  auto nodes = GestureControlEngine::Instance()->GetNodes();
  for (auto& node : nodes) {
    exec.add_node(node);
  }
  exec.spin();
  rclcpp::shutdown();

  return 0;
}
