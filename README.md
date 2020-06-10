# DroneSim

A super simple drone simulation. Simulates the behavior of a single drone (only in Z/Up direction)
affected by a single input:
* Normalized drone acceleration (input)

The simulation considers:
* Time (advanced by simulation)
* Earth gravity (constant)
* Maximal drone acceleration (constant)
* Maximal landing speed (constant)

The flight data (time, height, speed, acceleration, user_data) is saved to a CSV file.
If the drone lands with more than the maximal landing speed, the vehicle is considered "crashed" and stops working.

Check out [drone_simulation.h](drone_simulation.h) for more details on the API.

## Goals

This simulation is used by beginners learning embedded software design in C on the topic of PID Control and thus tries to be
1. very simple,
2. compilable with [VirtualC IDE](https://sites.google.com/site/virtualcide/).
