// Gmsh project created on Mon Jun 03 23:39:16 2024
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, -0, 1.0};
//+
Point(8) = {3, 0, -0, 1.0};
//+
Point(9) = {3, 1, -0, 1.0};
//+
Point(14) = {0, 1, -0, 1.0};
//+
Line(1) = {1, 8};
//+
Line(2) = {9, 8};
//+
Line(3) = {9, 14};
//+
Line(4) = {14, 1};
//+
Curve Loop(1) = {4, 1, -2, 3};
//+
Plane Surface(1) = {1};
