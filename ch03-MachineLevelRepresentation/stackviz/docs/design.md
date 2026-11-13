StackViz Design
Goal: Visualize x86-64 stack frames at runtime.

Version 1 Features:

RSP display
RBP display
Return address display
Saved frame pointer display
Frame size calculation
Raw stack memory dump
Not Supported:

DWARF parsing
Variable name recovery
Remote process inspection
ptrace
Compiler Requirements: -O0 -g -fno-omit-frame-pointer