
//***********************************//PDE filter
solve(-fvm::laplacian(xp)+fvm::Sp(b,xp)-x*b);
//***********************************//Heaviside_filter



for(i=0;i<n;i++)    //Heaviside filter
{

    xh[i]=(Foam::tanh(del*eta5)+Foam::tanh(del*(xp[i]-eta5)))/(Foam::tanh(del*eta5)+Foam::tanh(del*(1-eta5)));
}

