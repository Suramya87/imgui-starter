# imgui-starter

Using the provided code provided here you have a base Dear IMGUI project for Windows and macOS. There is a basic CMakefile in this project that includes the necessary files to create an application that brings up just a basic screen.

You must add a logging system to this code that you will be using THROUGHOUT the quarter. This logging system should do two things.

It should be able to log to a Dear IMGUI debug console
It should also log its output to a file.

For the submission, make a branch of this repo and submit a new GitHub URL

# Approach

I looked throught the imgui documentaion and also looking at the c++ documentation as it has been ages since I have used it. First I tried following the imgui code snippets on github to try and make something work in with in the demo after which I had a better sense of how work with the system. I have the console to have three buttons for now to test and have the ability to have it log on the console and into a file after finding out how to do so using imgui. As for logging the console into a text file I wanted to have a point where it starts and stops recording so now there is a button that you hit and anything that will appear on the console will be logged and when you hit it again will then output whatever was sent in in the console in the game log file.

# Things i learned about cmake
Dont push your build folders it ends very badly and for some reason the git ignore does not ignore it go check that out
# OS
Windows

# TOOLS

vscode
cmake 
imgui
