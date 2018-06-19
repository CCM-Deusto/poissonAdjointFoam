Info << "Reading physicalProperties\n" << endl;
IOdictionary physicalProperties
(
    IOobject
    (
	"physicalProperties",
	runTime.constant(),
	mesh,
	IOobject::MUST_READ,
	IOobject::NO_WRITE
    )
);

dimensionedScalar k(physicalProperties.lookup("k"));
dimensionedScalar beta(physicalProperties.lookup("beta"));
dimensionedScalar gamma(physicalProperties.lookup("gamma"));

/***************************************************************************/

Info << "Reading numericalParameters\n" << endl;
IOdictionary numericalParameters
(
    IOobject
    (
	"numericalParameters",
	runTime.constant(),
	mesh,
	IOobject::MUST_READ,
	IOobject::NO_WRITE
    )
);

scalar tol(numericalParameters.lookupOrDefault<scalar>("tol", 1e-8));

/****************************************************************************/

Info << "Reading target field\n" << endl;
volScalarField yd
(
    IOobject
    (
	"yd",
	runTime.constant(),
	mesh,
	IOobject::MUST_READ,
	IOobject::NO_WRITE
    ),
    mesh
);

Info << "Reading source field\n" << endl;
volScalarField f
(
    IOobject
    (
	"f",
	runTime.constant(),
	mesh,
	IOobject::MUST_READ,
	IOobject::NO_WRITE
    ),
    mesh
);

/****************************************************************************/

Info << "Reading field y\n" << endl;
volScalarField y
(
    IOobject
    (
	"y",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading adjoint field\n" << endl;
volScalarField lambda
(
    IOobject
    (
	"lambda",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading control u\n" << endl;
volScalarField u
(
    IOobject
    (
	"u",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Calculating control variation p\n" << endl;
volScalarField p
(
    IOobject
    (
	"p",
	runTime.timeName(),
	mesh,
	IOobject::NO_READ,
	IOobject::AUTO_WRITE
    ),
    lambda + beta*u
);

scalarField volField = mesh.V();
