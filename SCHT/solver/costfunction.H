Info<<"cost function"<<endl;

meanT=fvc::domainIntegrate(T).value()/area;
V=fvc::domainIntegrate(xh).value()/area-voluse; 

//objectFunction
objC=0;  

for (i=0; i<nObjPatch; i++)  
{  
	  objC =objC + sum(T.boundaryField()[conPatchList[i]]*phiT.boundaryField()[conPatchList[i]]);   
}

reduce(objC, sumOp<scalar>()); 


if (Pstream::master())
{ 
   ofstream outfile1("Voluse.txt",std::ios::app);
   outfile1<<V<<"\n";
   outfile1.close();

   ofstream outfile2("meanT.txt",std::ios::app);
   outfile2<<meanT<<"\n";
   outfile2.close(); 

   ofstream outfile3("Time.txt",std::ios::app);
   outfile3<<runTime.elapsedClockTime()<<"\n";
   outfile3.close();    

   ofstream outfile4("maxT.txt",std::ios::app);
   outfile4<<maxT<<"\n";
   outfile4.close();   

   ofstream outfile5("objC.txt",std::ios::app);
   outfile5<<objC<<"\n";
   outfile5.close(); 

   ofstream outfile6("mnd.txt",std::ios::app);
   outfile6<<mnd<<"\n";
   outfile6.close(); 
}
if(runTime.writeTime())
{
   T.write();   

}