#ifndef DRONE_SIMULATION_H
#define DRONE_SIMULATION_H

#define TIME_STEP  0.01f // [s]

/// Start the simulation and create a log file which contains flight data.
/// File contains: time, height, speed, throttle, user_data
/// Matlab example for plotting the height over time:
///   flight_data = csvread("flight.log",1);
///   plot(flight_data(:,1), flight_data(:,2)); % plot height
void sim_start(const char *filename);

/// End the simulation.
void sim_end(void);

/// Increase the simulation time by a timer tick.
/// Returns current time in seconds.
float sim_advance_time(void);

/// Returns the vehicle's height over ground in meters.
float sim_get_height(void);

/// Set the throttle of the vehicles propellers (must be in range 0 to 1).
void sim_set_throttle(float throttle);

/// Set optional user data which will be logged in the flight data file.
/// Note: User data can be used for logging the target height.
void sim_set_user_data(float user_data);


/// Example trajectory for a simulation in 0 < t < 30 seconds

#define move_linear(t,t1,t2,z1,z2) ((z1) + ((t)-(t1))*((z2)-(z1))/((t2)-(t1)))
#define move_linear_in_interval(t,t1,t2,z1,z2)      \
if((t) > (t1) && (t) < (t2)){                          \
    return move_linear((t),(t1),(t2),(z1),(z2)); }

static inline float sim_get_example_trajectory(float time)
{
    move_linear_in_interval(time,  0.0f,  5.0f, 0.0f, 5.0f);
    move_linear_in_interval(time,  5.0f, 15.0f, 5.0f, 5.0f);
    move_linear_in_interval(time, 15.0f, 24.5f, 5.0f, 0.5f);
    move_linear_in_interval(time, 24.5f, 29.0f, 0.5f, 0.0f);
    return 0.0f;
}

#endif //DRONE_SIMULATION_H
