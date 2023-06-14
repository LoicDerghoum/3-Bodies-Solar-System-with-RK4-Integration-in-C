# 3-Bodies-Solar-System-with-RK4-Integration-in-C
3 Bodies Solar System with RK4 Integration (FR comments)

# Execution

    $ make && ./sysol05 365 100 STL.DAT > sysol05.csv

## 1. Subject

As part of a mathematics project, we will need to design (in C) the numerical simulation program of the solar system. Like any realistic project, this is a cross-disciplinary project requiring skills from different domains:
- Physics, algebra, and analysis: modeling part
- Numerical mathematics: integration method
- Algorithmics and code production: computer science.

### 1.1 True System
The real system consists of a star (the Sun) around which planets orbit. These planets are divided into two groups:
- The terrestrial planets in the center:
    - Mercury
    - Venus
    - Earth with its satellite (the Moon)
    - Mars
- And the gas giants on the periphery:
    - Jupiter
    - Saturn
    - Uranus
    - Neptune.

The two aforementioned groups are separated by an asteroid belt (a likely trace of the failure of an additional planet's formation).

### 1.2 Required Simulation
The system to be simulated will be a simplification of the real system, reduced to the following three elements:

- The Sun
- The Earth
- The Moon

Only the forces of universal gravitation will act on them. Starting from the provided initial conditions (positions and velocities), it will be necessary to simulate the temporal evolution by calculating the positions and velocities of each of the three bodies in the system. It will be assumed that all the bodies in the system (including the Moon) orbit in the same plane (the plane of the ecliptic), allowing the system to be reduced to two dimensions.

The system to be simulated will be based on a system of second-order nonlinear differential equations. The prescribed numerical solution method for integration is the explicit fourth-order Runge-Kutta method (classical). A concise reference providing an overview of the coefficients used can be found at: https://en.wikipedia.org/wiki/Runge-Kutta_methods.

# 2. Specifications

### 2.1 Reference Frame and Initial Conditions

All objects will belong to the same plane (ecliptic):
The plane of the ecliptic will be defined by a centered orthonormal Cartesian coordinate system with its origin at (0,0), the probable initial position of the Sun.
Each body will be treated as a point mass.
The position of each body will be defined by a pair of Cartesian coordinates in this reference frame, expressed in kilometers.
The velocity of each body will be defined by a pair of Cartesian components in this reference frame, expressed in kilometers per second.
The individual gyroscopic rotation of each body is ignored. Consequently, the inclination of the Earth is also ignored, and the axis connecting the two celestial poles will be perpendicular to the plane of the ecliptic.
The plane will be viewed from the celestial north pole, which means that the Earth should rotate counterclockwise (anticlockwise) in the trigonometric direction.

Numeric Values
The numeric values related to the three celestial bodies necessary for our simulation, including:

    Masses,
    Initial positions (in x and y coordinates),
    Initial velocities (in x and y components),
    
### 2.2 Numeric
They will be contained in a text file that needs to be processed by our program (see section 3.3). Only the universal gravitational constant 𝐺 is given here:

$𝐺 = 6.6742 × 10^{-11} m^3 · kg^{-1} · s^{-2}$

### 2.3 Deliverable
For portability reasons, we are limited to using the headers defined by the SUS4 standard. To simplify, we limit ourself to the following headers, which are more than sufficient:

- float.h
- locale.h
- math.h
- stdbool.h
- stdlib.h
- stdio.h
- string.h
- unistd.h

On a Unix system (certified SUS4), our source code must be able to be compiled without any errors (or warnings) using the following command:

    $ gcc -o sysol05 main.c -lm

To maintain the initial state of the project's skeleton, we can use:

    $ gcc -o sysol05 main.c debug.c -lm

Or, even more simply:

    $ make

### 2.4 Execution
During execution, the program should accept three arguments in the following order:

    An integer: the total duration of the simulation in days.
    An integer: the calculation step (sampling period) in number of points per day.
    A string: the file path to the numeric data file (2.2).

For example (on a Unix or compatible system):

    $ ./sysol03 365 100 STL.dat

This command will initiate a simulation of the system for a total duration of 365 days, with 100 calculation points per day, resulting in a total of 36,500 calculation points. The simulation will use the numeric data provided by the file "STL.dat."

### 2.5 Presentation of Results
The program should display the raw simulation results on the standard output (stdout) in the form of a matrix with 22 columns, where:

- The first row will serve as the header row (with a label for each column).
- The following rows will represent the numeric simulation results (in scientific notation) for each calculation step, in the following order:
    - Time (the value of the current time step in days).
    - For each group of six columns, the program will present the numeric results of a celestial body in the order they appear in the numeric data file (the last argument of the command line). These six columns, in order, will contain:
        - The horizontal position of the body in the plane (in km).
        - The vertical position of the body in the plane (in km).
        - The horizontal component of the body's velocity in the plane (in km/s).
        - The vertical component of the body's velocity in the plane (in km/s).
        - The horizontal component of the body's acceleration in the plane (in km/s^2).
        - The vertical component of the body's acceleration in the plane (in km/s^2).
    - The next two columns (20 and 21) will present the horizontal and vertical components of the Moon's position relative to the Earth in km.
    - Finally, the 22nd and last column will represent the distance between the Earth and the Moon (the length of the line segment connecting the Earth and the Moon) in km.

Here is an example of the expected result format:

Time ... Sun ... Sun ... Sun ... Sun ... 0.0100e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0200e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0300e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0400e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0500e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0600e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0700e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0800e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...
0.0900e+00 #.####e+## #.####e+## #.####e+## #.####e+## ...

This format allows for easy graphical representation by redirecting and importing the data into a spreadsheet software (such as OpenOffice or LibreOffice).

For example:

    $ ./sysol05 365 100 STL.dat > sysol05.csv

This command will initiate the simulation for 365 days with 100 calculation points per day. The initial numeric data will be provided by the "STL.dat" file, and the results will be saved in the file "sysol05.csv." The ".csv" extension allows the file to be immediately opened by a spreadsheet software.

WARNING: No other messages should be displayed on the standard output. If you want to display additional information, you must use the error output (stderr). The "debug" and "trace" functions (or macros) present in the initial project skeleton (see section 3.2) are specifically dedicated to this purpose.

### 2.6 Representation of Time Scale
Since the simulation's time scale can be long (on the order of a terrestrial year), time will be expressed as a real number with the unit of a terrestrial day, starting from zero.

# 4 Important Notifications

### 4.1 Localization
French localization is set, meaning that all numbers will be written with a comma instead of a decimal point. That's why the following instruction is one of the first line of the program:

```c
setlocale(LC_NUMERIC ,"fr_FR");
```

As a result, all numbers (both input and output) will be in the natural format where the comma is used as the separator between the integer and decimal parts.

If you encounter any errors on a Linux-type system, please ensure that the "locales" and "locales-all" packages are properly installed.
