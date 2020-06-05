#include "drone_simulation.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define EARTH_ACCELERATION  -9.81f // [m/s^2]
#define DRONE_MAX_ACCELERATION  13.0f // [m/s^2]

static FILE *log_file = NULL;
static float user_data_to_log;
static struct vehicle {
    float height;   // [m]
    float speed;    // [m/s]
    float throttle; // [m/s^2]
    bool crashed;
} drone;

float sim_advance_time(void)
{
    static float time = 0.0f; // [s]

    assert(log_file != NULL); // called before sim_start
    fprintf(log_file, "%f, %f, %f, %f, %f\n",
            time, drone.height, drone.speed, drone.throttle, user_data_to_log);

    if(drone.crashed == false) {
        float previous_height = drone.height;
        float acceleration = drone.throttle * DRONE_MAX_ACCELERATION + EARTH_ACCELERATION;
        drone.speed += acceleration * TIME_STEP;
        drone.height += drone.speed * TIME_STEP;

        if (drone.height <= 0.0f) {
            if(drone.speed < (EARTH_ACCELERATION * TIME_STEP * 2)) {
                printf("Drone crashed with speed %f!\n", -drone.speed);
                drone.crashed = true;
            } else if(previous_height > 0.0f) {
                printf("Drone landed!\n");
            }
            drone.speed = 0.0f;
            drone.height = 0.0f;
        }
    }

    time += TIME_STEP;
    return time;
}

float sim_get_height(void)
{
    return drone.height;
}

void sim_set_throttle(float throttle)
{
    assert(throttle >= 0.0f); // hardware limit: cannot accelerate downwards
    assert(throttle <= 1.0f); // hardware limit: max motor torque
    drone.throttle = throttle;
}

void sim_set_user_data(float user_data)
{
    user_data_to_log = user_data;
}

void sim_start(const char *filename)
{
    assert(filename != NULL); // no path given
    assert(filename[0] != '\0'); // empty path given
    log_file = fopen(filename, "w");
    assert(log_file != NULL); // file creation failed
    fprintf(log_file, "time, height, speed, throttle, user_data\n");
    sim_advance_time();
}

void sim_end(void)
{
    assert(log_file != NULL); // called before sim_start
    fclose(log_file);
}
