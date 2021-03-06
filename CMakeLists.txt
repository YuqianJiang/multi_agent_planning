cmake_minimum_required(VERSION 2.8.3)
project(multi_agent_planning)

add_compile_options(-std=c++11)

find_package(Boost 1.58 REQUIRED COMPONENTS graph filesystem)
include_directories(include ${Boost_INCLUDE_DIRS} )

#add_executable(main src/main.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
#target_link_libraries( main ${Boost_LIBRARIES} )

#add_executable(idp_tester src/idp_tester.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
#target_link_libraries( idp_tester ${Boost_LIBRARIES} )

#add_executable(iidp_tester src/iidp_tester.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
#target_link_libraries( iidp_tester ${Boost_LIBRARIES} )

#add_executable(experiments src/experiments.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
#target_link_libraries( experiments ${Boost_LIBRARIES} )

add_executable(experiment_agents src/experiment_agents.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
target_link_libraries( experiment_agents ${Boost_LIBRARIES} )

add_executable(experiment_theta src/experiment_theta.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
target_link_libraries( experiment_theta ${Boost_LIBRARIES} )