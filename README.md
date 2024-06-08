# Turn-Base Game Development Project
To change the inputs of the files tc1_armyknights and tc1_events for your turn-based game development project, you need to follow the structure specified for each file. 

1. tc1_armyknights File
This file specifies the initial state of the knights. Here's how you can change the inputs:

First line: This line represents the number of knights, n.
Next n lines: Each line represents a knight with the attributes: HP_level_phoenixdownI_gil_antidote.

Example Structure
3
100_5_2_50_0
150_3_1_100_1
200_4_3_200_0

This example indicates there are 3 knights with the following attributes:
Knight 1: HP = 100, Level = 5, Phoenixdown I = 2, Gil = 50, Antidote = 0
Knight 2: HP = 150, Level = 3, Phoenixdown I = 1, Gil = 100, Antidote = 1
Knight 3: HP = 200, Level = 4, Phoenixdown I = 3, Gil = 200, Antidote = 0

If you need additional information, please refer to page 2 of the "About the game.pdf" file for a more detailed explanation of the tc1_armyknights file.

Steps to Change tc1_armyknights:
Open the tc1_armyknights.txt file in a text editor.
Modify the first line to change the number of knights.
Modify the subsequent lines to change the attributes of each knight.

2. tc1_events File
This file specifies the events that will occur during the game. Here's how you can change the inputs:

First line: This line represents the number of events, n.
Next n numbers: Each line represents an event, seperating by the "space"

Example Structure
5
1 4 8 98 99
This example indicates there are 5 events: 1, 4, 8, 98, and 99. 

If you need additional information, please refer to page 4 of the "About the game.pdf" file for a more detailed explanation of the tc1_events file.

Steps to Change tc1_events:
Open the tc1_events.txt file in a text editor.
Modify the first line to change the number of events.
Modify the subsequent lines to change the events based on the details provided in the game documentation.

3. Example
Suppose you want to set up the game with 2 knights and 3 events, your files would look like this:

tc1_armyknights.txt
2
120_4_1_60_0
180_5_2_150_1

tc1_events.txt
3
1 98 99

Summary
Ensure the first line of each file accurately reflects the number of knights or events.
Follow the correct format for each knight's attributes and the list of events.
Use a text editor to make these changes and save the files with the correct format.

# How to run a game
To run the game, follow these steps:

1. Download the Entire Project:
Ensure you have downloaded the entire project file.

2. Navigate to the Project Directory:
- Open a command prompt (cmd) on Windows or a terminal on other operating systems.
- Navigate to the project directory using the cd command. For example:
    cd path\to\your\project\directory

3. Ensure C++ is Installed:
Make sure you have a C++ compiler installed on your computer. Visual Studio Code with the Code Runner extension is commonly used.

4. Compile the Code:
Copy and run the following command to compile the code:
    g++ -g -o main main.cpp knight2.cpp -std=c++11

5. Run the Game:
After compiling, run the game with the following command:
    ./main

This process will compile the C++ files and execute the game. Make sure all necessary files (main.cpp and knight2.cpp) are present in the directory.