# SCHT_OPT
## Description
This code is used to solve the topology optimization problem of simplified convective heat transfer.
## Configuration environment
(1) **OpenFOAM-6** (new version is applicable)  
(2) **PETSc-3.12.0** (new version is applicable)  
(3) **openMPI-1.10.0** (new version is not applicable)  
Parallel version of **MMA** changed by Yu Minghao  is also needed for updating the design variables (https://github.com/MTopOpt/MTO).
## Run the solver
After installing the above software, enter the _solver_ folder and compile the solver with the `wmake` command.Then topology optimization can be performed.  
### 2D SCHT topology optimization
(1) Use the `blockMesh` command to create a mesh.  
(2) Use the `decomposePar` command to block the calculation model.  
(3) Finally, `mpirun -n 6 SCHT_OPT -parallel` is used for parallel topology optimization calculation.
### 3D SCHT topology optimization
(1) Use the `blockMesh` command to create a mesh.Then, use `topoSet` to create an auxiliary domain and use the `createPatch -overwrite` command to create a new boundary domain.  
(2) Use the `decomposePar` command to block the calculation model.  
(3) Finally, `mpirun -n 6 SCHT_OPT -parallel` is used for parallel topology optimization calculation.
## Post-processing
After the optimization, users should run `reconstructPar` in the app folder and then run `paraFoam` to view the results with Paraview.
## Results
### 2D_h=1
![alt 属性文本](https://github.com/HeatTopOpt/SCHT_OPT/blob/master/SCHT/2D_h%3D1.gif)

