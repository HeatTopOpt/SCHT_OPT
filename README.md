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
