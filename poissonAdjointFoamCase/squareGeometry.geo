Lx = 1;
Ly = 1;

Point(1) = {0, 0, 0};
Point(2) = {Lx, 0, 0};
Point(3) = {Lx, Ly, 0};
Point(4) = {0, Ly, 0};

Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};

Line Loop(5) = {1, 2, 3, 4};
Plane Surface(6) = {5};

//Transfinite Line{1, 3} = 50;
//Transfinite Line{2, 4} = 50;
Transfinite Line{1, 2, 3, 4} = 100;
Transfinite Surface{6};
Recombine Surface{6};

newEntities[] =
Extrude {0,0,0.1}
{
	Surface{6};
	Layers{1};
	Recombine;
};

Physical Surface("backAndFront") = {6,newEntities[0]};
Physical Surface("dirichletBoundary") = {newEntities[2],newEntities[3],newEntities[4],newEntities[5]};
Physical Volume(20) = {newEntities[1]};

Mesh 3;
Save "squareGeometry.msh";
