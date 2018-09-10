
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "triangunator");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "sia5";

  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  const robot_state::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
  visual_tools.deleteAllMarkers();

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  move_group.setJointValueTarget(move_group.getNamedTargetValues("pose2"));
  move_group.plan(my_plan);
  move_group.move();
  
  sleep(2.0);

  move_group.setJointValueTarget(move_group.getNamedTargetValues("pose3"));
  move_group.plan(my_plan);
  move_group.move();
 
  sleep(2.0);
  move_group.setJointValueTarget(move_group.getNamedTargetValues("pose1"));
  move_group.plan(my_plan);
  move_group.move();
  

/*   visual_tools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);
  visual_tools.trigger(); */




  ros::shutdown();
  return 0;
}