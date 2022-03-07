
//***********************************//Heaviside_filter




if(opt>1)
{
  for(i=0;i<n;i++)
  {
    drho[i]=(del*(1-Foam::tanh(del*(xp[i]-eta5))*Foam::tanh(del*(xp[i]-eta5))))/
    (Foam::tanh(del*eta5)+Foam::tanh(del*(1-eta5)));
  }
  fsensh=fsensh*drho;//drho=dxh/dxp
  gsensh=gsensh*drho;

}



//***********************************//PDE filter
solve(fvm::laplacian(fsens)-fvm::Sp(b,fsens)+fsensh*b);  //get fsens

solve(fvm::laplacian(gsens)-fvm::Sp(b,gsens)+gsensh*b);