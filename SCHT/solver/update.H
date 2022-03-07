//***********************************//update mu and lambda
opt++;

xh.correctBoundaryConditions();

mnd=0;

for(i=0;i<n;i++) 
{  
	  mnd =mnd + 4*xh[i]*(1-xh[i]);   
}
reduce(mnd, sumOp<scalar>());
mnd=mnd/N;

if(runTime.writeTime())
{
   xh.write();     
   fsensh.write();
}
DT=kmin+(k-kmin)*xh*xh*xh;

mgxh=Foam::sqrt(((fvc::grad(xh))&(fvc::grad(xh)))*k1*k1+delm);
c=mgxh*hh;

Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;


