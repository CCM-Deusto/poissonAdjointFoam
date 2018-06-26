// Initialize L2 norm of control update
scalar pL2 = 10*tol;

// Get the volume of mesh cells
scalarField volField = mesh.V();

while (runTime.loop() && ::sqrt(pL2) > tol)
{
    // Solve primal equation
    solve(fvm::laplacian(k, y) + u);

    // Solve ajoint equation
    solve(fvm::laplacian(k, lambda) + y - yd);

    // Update control
    p = lambda + beta*u;
    u = u - gamma*p;

    // Control update norm
    pL2 = ::sqrt(gSum(volField*p.internalField()*p.internalField()));

    // Compute cost function
    J = 0.5*gSum(volField*(Foam::pow(y.internalField()-yd.internalField(),2) \
	    + beta*Foam::pow(u.internalField(),2)));

    // Display information
    Info << "Iteration " << runTime.timeName() << " - " \
	    << "Cost value " << J << " - " \
	    << "Control variation L2 norm " << ::sqrt( pL2 ) << endl;

    // Save current iteration results
    runTime.write();
}
