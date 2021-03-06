# Realtime-Visualizer

![Alt Text](https://github.com/alilajevardi/Realtime-Visualizer/blob/main/artifacts/Molecules_01.gif)

![Alt Text](https://github.com/alilajevardi/Realtime-Visualizer/blob/main/artifacts/C60.gif)

# Main control panel
The main program has written in VB.Net that control the simulation and visulization.
The visualization can be set in either of realtime mode or retained mode.

![User Interface](https://github.com/alilajevardi/Realtime-Visualizer/blob/main/artifacts/main2.PNG)

The simulation properties set in this section:
* Type of MD simulation: NVT, NPT, MVT
* Interatomic potential: Lennard-Jones, Morse, Sutton-Chen, Tersoff-Bernner
* Intial values

![User Interface](https://github.com/alilajevardi/Realtime-Visualizer/blob/main/artifacts/SimulationProperties.jpg)

# Molecular Simulation via FORTRAN
The simulation code solves the Lennard-Jones potential for Ar atoms
The simulation dll can be replace with any other simulation code consiting the following format:

```fortran
Subroutine Simulation(NMD,ITNIN,NALL,SAMPELING,TEMP,ENERGY,POTENTIAL,X,Y,Z,IP)
!DEC$ ATTRIBUTES DLLEXPORT::Simulation
!DEC$ ATTRIBUTES ALIAS:'Simulation' :: Simulation
IMPLICIT NONE
INTEGER NMD, NALL, ITNIN, SAMPELING
REAL*8 ENERGY, POTENTIAL, TEMP
INTEGER, DIMENSION(NALL):: IP 
REAL*8, DIMENSION(NALL):: X, Y, Z


!Insert your MD code here 


End Subroutine Simulation
```



![User Interface](https://github.com/alilajevardi/Realtime-Visualizer/blob/main/artifacts/main3.PNG)





# Visualizer DLL
The code written in C++ call DirectX 9.0c library to visualize simulation data either in realtime mode or retained mode.
