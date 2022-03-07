Info<< "Reading thermal properties\n" << endl;
IOdictionary thermalProperties
(
    IOobject
    (
        "thermalProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar k(thermalProperties.lookup("k"));//Thermal Conductivity 
dimensionedScalar kmin(1e-3*k);
//dimensionedScalar b2("b2", dimensionSet(0,0,-1,2-Pnorm,0,0,0),1);
dimensionedScalar delta(thermalProperties.lookup("delta"));

dimensionedScalar hh(thermalProperties.lookup("hh"));
dimensionedScalar Tw(thermalProperties.lookup("Tw"));

volScalarField DT
(
    IOobject
    (
        "DT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    kmin+(k-kmin)*xh*xh*xh
);



volScalarField delm
(
    IOobject
    (
        "delm",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    scalar(deltam)
);

Info<< "Reading field T\n" << endl;
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
    volScalarField Ta
    (
        IOobject
        (
            "Ta",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
Info<< "Reading heatsource Q\n" << endl;
volScalarField Q
(
    IOobject
    (
        "Q",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("Q", dimensionSet(0,0,-1,1,0,0,0),1),
    calculatedFvPatchScalarField::typeName
);
volScalarField fsens
(
    IOobject
    (
        "fsens",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
   -3*(k-kmin)*xp*xp*(fvc::grad(T)&fvc::grad(T)),
   zeroGradientFvPatchScalarField::typeName
);
volScalarField fsensh(fsens);
volScalarField gsens
(
    IOobject
    (
        "gsens",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    xh,
    zeroGradientFvPatchScalarField::typeName
);
volScalarField gsensh(gsens);

volScalarField mgxh
(
    IOobject
    (
        "mgxh",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
   xh
);



volScalarField c
(
    IOobject
    (
        "c",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    k4*xh
);
volVectorField KK
(
    IOobject
    (
        "KK",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    //T*T*mesh.Sf()/mesh.magSf()
    T*T*fvc::grad(xh)
);

	surfaceScalarField phiT 
	(  
	    IOobject  
	    (  
	        "phiT",  
	        runTime.timeName(),  
	        mesh,  
	        IOobject::READ_IF_PRESENT,  
	        IOobject::AUTO_WRITE  
	    ),  
	    linearInterpolate(DT*fvc::grad(T)) & mesh.Sf() 
    );