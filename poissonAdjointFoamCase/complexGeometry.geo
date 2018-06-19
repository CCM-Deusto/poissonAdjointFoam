Lx = 1;
Ly = 1;

R = 0.75;

Point(1) = {0, 0, 0};
Point(2) = {Lx, 0, 0};
Point(3) = {Lx, Ly-R, 0};
Point(4) = {Lx-R, Ly, 0};
Point(5) = {0, Ly, 0};
Point(6) = {Lx, Ly, 0};

Line(1) = {1, 2};
Line(2) = {2, 3};
Circle(3) = {3, 6, 4};
Line(4) = {4, 5};
Line(5) = {5, 1};

Line Loop(6) = {1, 2, 3, 4, 5};
Plane Surface(7) = {6};

Transfinite Line{2, 4} = 10;
Transfinite Line{1, 5} = 40;
//Transfinite Line{3} = 60;
Transfinite Surface{7};
Recombine Surface{7};

newEntities[] =
Extrude {0,0,0.1}
{
	Surface{7};
	Layers{1};
	Recombine;
};

Physical Surface("backAndFront") = {7,newEntities[0]};
Physical Surface("dirichletBoundary") = {newEntities[2],newEntities[3],newEntities[4],newEntities[5],newEntities[6]};
Physical Volume(20) = {newEntities[1]};

Mesh 3;
Save "complexGeometry.msh";
