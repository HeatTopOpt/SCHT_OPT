Info<< "\nslove conduction\n" << endl;
//T=Ta

Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;
solve(fvm::laplacian(DT, T)-fvm::Sp(c,T));//+c*Tw
//Info<< " \n" << "T = " << runTime.elapsedCpuTime() << " s" <<endl;
//solve(fvm::laplacian(DT, Ta)-fvm::Sp(c,Ta));
KK=T*T/mgxh*fvc::grad(xh);
phiT=linearInterpolate(DT*fvc::grad(T)) & mesh.Sf();


