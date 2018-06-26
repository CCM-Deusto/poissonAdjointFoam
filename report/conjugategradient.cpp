// Compute b: right-hand side of Ax = b
solve(fvm::laplacian(k, y));
solve(fvm::laplacian(k, lambda) + yd - y);
volScalarField b = lambda;

// Compute A*f0
// Primal equation
solve(fvm::laplacian(k, y0) + u);
// Adjoint equation
solve(fvm::laplacian(k, lambda) + y0);

// Compute g0: initial gradient
volScalarField g = lambda + beta*u - b;
scalar gL2 = gSum( volField * g.internalField() * g.internalField() );
scalar gL2a = 0;

// Compute initial residual and its norm
volScalarField r = -g;
scalar rL2 = gL2;

volScalarField w = g;

scalar alpha = 0;
scalar gamma = 0;

while (runTime.loop() && ::sqrt( rL2 ) > tol)
{
    r.dimensions().reset( u.dimensions() );

    // Compute w = A*r
    solve(fvm::laplacian(k, y0) + r);
    solve(fvm::laplacian(k, lambda) + y0);
    w = lambda + beta*r;

    // Update alpha
    alpha = gL2 / gSum( volField * r.internalField() * w.internalField() );

    // Update control
    u = u + alpha*r;

    // Update cost gradient and its norm
    g = g + alpha*w;
    gL2a = gL2;
    gL2 = gSum( volField * g.internalField() * g.internalField() );
    gamma = gL2/gL2a;

    // Update residual and its norm
    r.dimensions().reset( g.dimensions() );
    r = -g + gamma*r;
    rL2 = gSum( volField * r.internalField() * r.internalField() );

    solve(fvm::laplacian(k, y) + u);

    J = 0.5*gSum(volField*(Foam::pow(y.internalField()-yd.internalField(),2) \
     + beta*Foam::pow(u.internalField(),2)));

    Info << "Iteration no. " << runTime.timeName() << " - " \
	    << "Cost value " << J << " - " \
	    << "Residual " << ::sqrt( rL2 ) << endl;

    runTime.write();
}
