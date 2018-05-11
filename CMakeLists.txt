cmake_minimum_required(VERSION 2.8.3)
project(multi_agent_planning)

add_compile_options(-std=c++11)

find_package(Boost 1.58 REQUIRED COMPONENTS graph)
include_directories(include ${Boost_INCLUDE_DIRS} )

add_executable(main src/main.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
target_link_libraries( main ${Boost_LIBRARIES} )

add_executable(idp_tester src/idp_tester.cpp src/plan_utils.cpp src/InteractionCostCalculator.cpp src/PlanningAgent.cpp src/MultiAgentPlanner.cpp src/Scenario.cpp)
target_link_libraries( idp_tester ${Boost_LIBRARIES} )