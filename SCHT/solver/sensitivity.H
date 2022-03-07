
Info<<"sensitivity analysis"<<endl;


Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;
fsensh=-3*xh*xh*(k-kmin)*(fvc::grad(T)&fvc::grad(T))+hh*k1*k1*(fvc::div(KK));

fsensh=fsensh/gMax(mag(fsensh.primitiveField()));
gsensh.primitiveFieldRef()=mesh.V()/gMax(mesh.V());



del=8;
eta5=0.5;

#include "filter_sens.H"

gx[0]=(PetscScalar)(V);//constraint function

VecGetArray(dfdx,&dfdx_array);
VecGetArrays(dgdx,m,&dgdx_array);
for(i=0;i<n;i++)
{
 dfdx_array[i]=fsens[i]/N;//sensitivities of objective function
 dgdx_array[0][i]=gsens[i]/N;//sensitivities of constraint function
}
VecRestoreArray(dfdx,&dfdx_array);
VecRestoreArrays(dgdx,m,&dgdx_array);

Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;

Info<< "\n run MMA \n" << endl;
mma->SetOuterMovelimit(Xmin,Xmax,movlim,xmma,xmin,xmax);
mma->Update(xmma,dfdx,gx,dgdx,xmin,xmax,raa0,mma_dec,mma_inc);

VecGetArray(xmma,&xmma_array);
for(i=0;i<n;i++)
{
   x[i]=xmma_array[i];
}
VecRestoreArray(xmma,&xmma_array);

Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;

#include "filter_x.H"

Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;


