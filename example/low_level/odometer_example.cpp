/**
 * @file odometer_example.cpp
 * @brief Subscribes to and prints odometry data published by the B1 robot.
 *
 * Odometry provides an estimate of the robot's change in position and orientation
 * over time based on its own motion sensors (like leg joint movements).
 * This program listens for these odometry messages and prints the received
 * pose (position and orientation) data.
 */
#include <booster/robot/channel/channel_subscriber.hpp>
#include <booster/idl/b1/Odometer.h>
#include <booster/robot/b1/b1_api_const.hpp>

#include <thread>
#include <chrono>
#include <iostream>

using namespace booster::robot;
using namespace booster::common;
using namespace booster_interface::msg;

void Handler(const void *msg) {
    const Odometer *odom_state_msg = static_cast<const Odometer *>(msg);
    std::cout << "Received message: " << std::endl
              << "x: " << odom_state_msg->x() << ", "
              << "y: " << odom_state_msg->y() << ", "
              << "theta: " << odom_state_msg->theta() << std::endl;
}

int main() {
    ChannelFactory::Instance()->Init(0);
    ChannelSubscriber<Odometer> channel_subscriber(booster::robot::b1::kTopicOdometerState, Handler);
    channel_subscriber.InitChannel();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}