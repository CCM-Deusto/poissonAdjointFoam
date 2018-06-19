/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    poissonAdjointFoam

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"

    // Disable solvers performance output
    lduMatrix::debug = 0;
    solverPerformance::debug = 0;

    // Cost function value
    scalar Jy = 0;
    scalar Ju = 0;
    scalar J = Jy + Ju;

    // Compute cost function value
    #include "costFunctionValue.H"

    scalar pL2 = 10*tol;

    std::ofstream file("results.csv");
    file << 0 << "," << Jy << "," << Ju << "," << J << "," << 0 << nl;

    while (runTime.loop() && ::sqrt(pL2) > tol)
    {
	// Primal equation
	solve(fvm::laplacian(k, y) + f + u);

	// Adjoint equation
	solve(fvm::laplacian(k, lambda) + y - yd);

	// Control update (delta u)
	p = lambda + beta*u;
	// Control update norm
	pL2 = ::sqrt( gSum( volField * p.internalField() * p.internalField() ) );

	// Update control
	u = u - gamma*p;

	#include "costFunctionValue.H"

	Info << "Iteration " << runTime.timeName() << " - " \
		<< "Jy " << Jy << " - " \
		<< "Ju " << Ju << " - " \
		<< "J " << J << " - " \
		<< "Control variation L2 norm " << ::sqrt( pL2 ) << endl;

	file << runTime.value() << "," << Jy << "," << Ju << "," << J << "," << ::sqrt(pL2) << nl;

	runTime.write();
    }

    file.close();

    runTime++;
    y.write();
    lambda.write();
    u.write();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << nl << endl;
    Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
	<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
	<< nl << endl;

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
