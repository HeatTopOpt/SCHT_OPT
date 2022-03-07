Info<< "Reading optimization parameters\n" << endl;
IOdictionary optProperties
(
   IOobject
   (
       "optProperties",
       runTime.constant(),
       mesh,
       IOobject::MUST_READ_IF_MODIFIED,
       IOobject::NO_WRITE
   )
);
//optimization parameters
scalar raa0(readScalar(optProperties.lookup("raa0")));
scalar mma_init(readScalar(optProperties.lookup("mma_init")));
scalar mma_dec(readScalar(optProperties.lookup("mma_dec")));
scalar mma_inc(readScalar(optProperties.lookup("mma_inc")));
scalar movlim(readScalar(optProperties.lookup("movlim")));
scalar voluse(readScalar(optProperties.lookup("voluse")));
scalar filterR(readScalar(optProperties.lookup("filterR")));

scalar deltam(readScalar(optProperties.lookup("deltam")));

dimensionedScalar b("b", dimensionSet(0,-2,0,0,0,0,0),1.0);
Switch solid_area(optProperties.lookup("solid_area"));

//Balanced dimension
dimensionedScalar k1("k1", dimensionSet(0,1,0,0,0,0,0),1.0);
dimensionedScalar k2("k2", dimensionSet(0,-1,0,0,0,0,0),1.0);
dimensionedScalar k3("k3", dimensionSet(0,0,0,1,0,0,0),1.0);
dimensionedScalar k4("k4", dimensionSet(0,0,-1,0,0,0,0),1.0);
dimensionedScalar k5("k5", dimensionSet(0,2,0,0,0,0,0),1.0);


Info<< "Reading pseudo-density field\n" << endl;
volScalarField xp
(
    IOobject
    (
        "xp",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    scalar(0.001),
    zeroGradientFvPatchScalarField::typeName
);
volScalarField xh
(
    IOobject
    (
        "xh",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    scalar(0.001),
    zeroGradientFvPatchScalarField::typeName
);
volScalarField x(xh);
volScalarField drho(xh);




// find the cells in the non-design area
labelList cells;
if(solid_area)
{
  word zoneName="solid_area";
  label zoneID=mesh.cellZones().findZoneID(zoneName);
  cells=mesh.cellZones()[zoneID];
  forAll(cells, i)
  {
     x[cells[i]]=1;
     xh[cells[i]]=1;
  }
}


 
 
dictionary Fun1=mesh.solutionDict().subDict("thermal_compliance");  
int nObjPatch=Fun1.lookupOrDefault<scalar>("numberConstraintPatches",1);//number of patch   
wordList conPatchNames = Fun1.lookup("constraintPatchesNames");//function name  
label conPatchList[nObjPatch];//patch list  
int iLoop;  
for (iLoop=0; iLoop<nObjPatch; iLoop++)  
{  
	conPatchList[iLoop] = mesh.boundaryMesh().findPatchID(conPatchNames[iLoop]);  
}   

