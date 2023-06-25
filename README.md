Autonomous Delivery Application
App files:
- 1 main file
- 3 header class files
- 3 cpp implementation files
- 3 data storage text file
First timer quick start:
  1. Load up all files and run main
  2. For fresh experience, empty .txt text files
  3. Any path errors will mean .txt file does not exist



Project requirements

1. The autonomous delivery drones would all standby at the package hub. There are 
designated drop-off points used as package drop-off, for simplicity we shall name 
them StopA, StopB, StopC, etc. These designated stops also serve as recharge 
points for the drones’ battery.
2. During the project prototype, each drone would be flying to a drop-off point, and it 
would pick-up a package that is going to the same drop-off point.
3. Your program should start by reading two different data files:
a. Drone data file which contains all information about drones
b. Package data file which contains all information about packages to be 
delivered
4. Your program should be developed to provide a matching plan based on input of 
the drones and the packages.
5. The program should include at least the following features:
5.1. Input a string from console containing the folder path for the drone data file 
and package data file such that the program can read all the data from the files 
into its memory.
5.2. Parse all information about drones and packages and use an appropriate data 
type to store the data for drones and packages.
5.3. Compute and display a matching plan for the drones and the packages such 
that all parcels and drones reach their destination. 
5.4. Display at least the following information:
• Drone that does not have a package.
• Package that is not assigned to any drone.
5.5. Save the matching plan to a file. The file should clearly list out each drone
assigned to each package.
5.6. Add/Edit/Delete functionality for both drones and packages
