//
// Created by wiche on 3/21/2023.
//
#include "stats.h"

double fert_multiplier;
double watering_can_capacity;
double player_speed;
int n_robots;
double robot_speed;

double get_fert_multiplier() {return fert_multiplier; }
void set_fert_multiplier(double n) {fert_multiplier = n; }
double get_watering_can_capacity() { return watering_can_capacity; }
void set_watering_can_capacity(double n) { watering_can_capacity = n; }
double get_player_speed() { return player_speed; }
void set_player_speed(double n) { player_speed = n; }
int get_n_robots() { return n_robots; }
void set_n_robots(int n) { n_robots = n; }
double get_robot_speed() { return robot_speed; }
void set_robot_speed(double n) { robot_speed = n; }