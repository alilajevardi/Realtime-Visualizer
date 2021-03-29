!  Simulation.f90 
!
!  FUNCTIONS/SUBROUTINES exported from Simulation.dll:
!  Simulation      - subroutine 
!

subroutine Simulation(NMD,ITNIN,NALL,SAMPELING,CURTEMP,ENERGY,POTENTIAL,RX,RY,RZ,IP)

  ! Expose subroutine Simulation to users of this DLL
  !
  !DEC$ ATTRIBUTES DLLEXPORT::Simulation
  !DEC$ ATTRIBUTES ALIAS:'Simulation' :: Simulation

  
      IMPLICIT NONE
      INTEGER NMD,NALL
      INTEGER IP,ITN,ITNIN,I,K,N,NU
      INTEGER IEQULV,IPRINT,ISAVE,IEQULT
      INTEGER SAMPELING

      INTEGER NSTEP
      INTEGER NMAX
!-------------------------------------------------------
      REAL*8 tmp,temperature
      REAL*8 BMASS,EUNIT,LUNIT
      REAL*8 PRESSR,PDT,CURTMP,OLDV,BOXF
      REAL*8 DELTAV
      REAL*8 VX,VY,VZ,DT2,H,vxc,vyc,vzc
      REAL*8 SUMKE,VKE,VPE,VAV
      REAL*8 CURTEMP
	  REAL*8 ENERGY
      REAL*8 POTENTIAL


      REAL*8 PE,RX,RY,RZ,FX,FY,FZ
      REAL*8 BOXX,BOXY,BOXZ
      REAL*8 TEMP,DT,DTSQ
      REAL*8 MUNIT,RCMAX
!---------------------------------------------------------
      DIMENSION FX(NALL),FY(NALL),FZ(NALL)
      DIMENSION RX(NALL),RY(NALL),RZ(NALL)
      DIMENSION VX(NALL),VY(NALL),VZ(NALL)
      DIMENSION IP(NALL)
      CHARACTER CNFILE*80,TITLE*80

!cccccccNEW NEW ccccccccccccccccccccccccccccccccc
    
!C--------------------------------------------------------------------
!C:NMD=Number of iteration points
!C:NSTEP= Iteration number
!C:NALL= Total number of atoms
!C:NMAX= maximum number of atoms
!C:IP=Flag for atomic colour 
!C:ISAVE=Flag for saving the Configuration file
!C:IPRINT=Flag for printing intermediate results
!C:IEQULV= Flag for volume equilibration
!C:IEQULT= Flag for temperature equilibration
!C--------------------------------------------- 
!C--------------------------------------------------------------------
!C:VX,VY,VZ= Components of atomic velocities
!C:RX,RY,RZ= Components of atomic positions
!C:FX,FY,FZ= Components of force experienced by atoms
!C---------------------------------------------------------------------

!C-----Control Data------------------------------
!C      NMD=1000000

	NMAX=5000
	RCMAX=2.0
    TEMP=300.0
      
!c---------------
!c      OPEN(202,FILE='TEMP.DAT',STATUS='unknown')
!c      write(202,*)temp
! 
!c      close(202)
!C---------------	

	DT=1.0D-15
	PDT=50
	ISAVE=10
	IPRINT=10
	IEQULT=1
	IEQULV=0
	

!C ----Writes the cotrol data for checking--------------
!C ---------------------------------------------------------------------
997         FORMAT(1X,'CONSTANT TEMPERATURE MOLECULAR DYNAMICS ',A80,/)
998         FORMAT(A80)
999         FORMAT(1X,'CONFIGURATION FILE:',/,1X,A80)
1001        FORMAT(1X,'PRESSURE TIME CONSTANT:',F8.4)
1002        FORMAT(1X,'MAXIMUM NUMBER OF ITERATIONS=',I6)
1004        FORMAT(1X,'CONFIGURATION SAVED EVERY',I6,' ITERATIONS')
1005        FORMAT(1X,'LINE PRINTER OUTPUT EVERY',I6,' ITERATIONS')
1007        FORMAT(1X,'TEMPERATURE EQUILIBRATION FLAG=',I2)
1008        FORMAT(1X,'INI`TIAL TEMPERATURE=',F7.1,'K')
1009        FORMAT(1X,'TIME-STEP=',E9.2,' SECONDS')
1011        FORMAT(1X,'PRESSURE EQUILIBRATION FLAG=',I2)
!C-------------------------------------------------------
!C---Start of the Main Programme-----------------------



!C---Opens the initial cofiguration file----------
      OPEN(22,FILE='SHARIF.DAT',STATUS='OLD')
!C
!C-----Reads the data from CNFILE-------------------
      CALL INCRD(NSTEP,NALL,NMAX,RX,RY,RZ,IP,BOXX,BOXY,BOXZ,VX,VY,VZ,TITLE,OLDV,RCMAX)
!C
    CLOSE(22)
!c	OPEN(99,FILE='AVS1.DAT',STATUS='UNKNOWN')
!c	WRITE(99,*)NALL
!c************************** 
     
     
!C ----The subroutine that contains the simulation parameters-------
      CALL POTIN(BMASS,MUNIT,EUNIT,LUNIT,DT,TEMP,NALL,TMP)
!C---------------------------------------------------------------------
      IF(ISAVE.EQ.0 ) ISAVE  = NMD+1
      IF(IPRINT.EQ.0) IPRINT = NMD+1


!c======================= Neek addition


!C-----The subroutine that sets up the initial random velocities-----
      CALL STRTUP(NSTEP,RX,RY,RZ,VX,VY,VZ,NALL,TEMP,DT,DT2,DTSQ,IP,BMASS)
!C-----The main subroutine that performs the MD simulation-------
!c      CALL MD_RUN(NMD,RX,RY,RZ,BOXX,BOXY,
!c     &                 BOXZ,FX,FY,FZ,IP,
!c     &                 VX,VY,VZ,NALL,
!c     &                 DT2,DTSQ,NSTEP,IPRINT,ISAVE,
!c     &                 CNFILE,TEMP,DT,TITLE,PDT,OLDV,IEQULV,
!c     &                 BMASS,EUNIT,LUNIT,IEQULT,tmp)
!C---------------------------------------------------------------------
  

!cccccccccccccEND NEW NEWccccccccccccccccccccccccccccccccc
!C-----------------------------------------------------------------
      VAV=0.
      VKE=0.
      VPE=0.

      CALL IMPRSN(RX,RY,RZ,NALL,BOXX,BOXY,BOXZ)

      CALL LENNARD_JONES(RX,RY,RZ,FX,FY,FZ,H,PRESSR,NALL,BOXX,BOXY,BOXZ)

     
!C********************************************************
   DO 10 ITN=ITNIN,(ITNIN+SAMPELING-1) !ITN=NSTEP+1,NSTEP+NMD
!
!C=====================Neek Addition

!c======================================================
!C
            IF(MOD(ITN+9,10).EQ.0) THEN
            CALL IMPRSN(RX,RY,RZ,NALL,BOXX,BOXY,BOXZ)
            ENDIF


!c======================= neek addition      
      
     

		  
           CALL RMOVES(NALL,RX,VX,RY,VY,RZ,VZ,DT,BMASS,IP,FX,FY,FZ,DT2,DTSQ,BOXX,BOXY,BOXZ)

           CALL LENNARD_JONES(RX,RY,RZ,FX,FY,FZ,H,PRESSR,NALL,BOXX,BOXY,BOXZ)
!C--------------------------------------------
             CALL VMOVES(NALL,VX,VY,VZ,FX,FY,FZ,DT2,BMASS,SUMKE,IP,DT,itn,vxc,vyc,vzc,nmd)
!C-----------------------------------------------------------------------
           CURTMP=2.*SUMKE/DBLE(3*(NALL-1))

           PRESSR=PRESSR+2.*SUMKE/3

           PRESSR=PRESSR/BOXX/BOXY/BOXZ
           PRESSR=PRESSR*EUNIT/LUNIT**3. 

           IF(IEQULV.EQ.1) THEN
           CALL VSCALE(PRESSR,PDT,DT,RX,RY,BOXX,BOXY,NALL)
           ENDIF
!C-------------
            
           IF(IEQULT.EQ.1)THEN
           CALL TSCALE(TEMP,NALL,VX,VY,VZ,SUMKE,CURTMP)
           ENDIF

           DELTAV=(BOXX*BOXY*BOXZ/OLDV-1.)*100.

           VAV=VAV+BOXX*BOXY*BOXZ

           VKE=VKE+SUMKE
           VPE=VPE+H
!C================================Neek addition
          open(16,file='current.dat',status='Unknown')

		write(16,*) curtmp*tmp,(SUMKE+H)*EUNIT, PRESSR*EUNIT/LUNIT**3.,BOXx,BOXy,BOXz,itn
		close(16)
		
		IF(MOD(ITN,IPRINT).EQ.0) THEN
          !!WRITE(6,80) ITN,SUMKE*EUNIT,H*EUNIT,(SUMKE+H)*EUNIT,PRESSR,DELTAV
          WRITE(77,80) ITN,SUMKE*EUNIT,H*EUNIT,(SUMKE+H)*EUNIT,PRESSR,DELTAV
        ENDIF

!c-----------------new 29
      CURTEMP=curtmp*tmp
	  ENERGY=(SUMKE+H)*EUNIT
      POTENTIAL=H*EUNIT
	IF(MOD(ITN+9,10).EQ.0) THEN     
	
	open(140,file='datafile.dat',status='unknown')
            
      
	write(140,*)ITN
	write(140,*)CURTEMP
     	write(140,*)ENERGY
     	write(140,*)POTENTIAL

     	write(140,*)NALL
     	
      write(140,110)(RX(i),RY(i),RZ(i),IP(i),I=1,NALL)
       
!c	close(140) 

110   FORMAT(f10.4,f10.4,f10.4,i6)

131   FORMAT(I1) 
132   FORMAT(I3,',',I3,',',I3)

133   FORMAT(E11.3)
134   FORMAT(I2) 

135   FORMAT(E11.4,',',E11.4,',',E11.4)


      ENDIF

!C-----------------------------------------------------------------------
!          IF(MOD(ITN,ISAVE).EQ.0) THEN
!
!          OPEN(22,FILE='SHARIF.DAT',STATUS='OLD')
!
!          CALL OUTCRD(ITN,BOXX,BOXY,BOXZ,RX,RY,RZ,IP,NALL,VX,VY,VZ,TEMP,TITLE,OLDV)
!          CLOSE (22)
!          ENDIF
!C-----------------------------------------------------------------------
!C         IF(MOD(ITN,10).EQ.0) THEN
!C         WRITE(NU,427)NALL
!C         WRITE(NU,4299)BOXX,BOXY,BOXF
!C         WRITE(NU,428) (RX(I),RY(I),RZ(I),IP(I),I=1,NALL)
!C         CLOSE(NU)
!C         NU=NU+1
!c     IF(MOD(ITN+1,10).EQ.0)THEN
!c	OPEN(99,FILE='AVS1.DAT',STATUS='UNKNOWN')
!c	WRITE(99,333)ITN,300D0,2000D0,3000D0,5000D0
!c	WRITE(99,428)(RX(I),RY(I),RZ(I),IP(I),I=1,NALL)
333       FORMAT(I8,4(1X,F15.7))
427       FORMAT(I8)
4299      FORMAT(3E21.12)
428       FORMAT(3E25.16,I6)
!c          ENDIF
!C-----------------------------------------------------------------------
10    CONTINUE
!C-----------------------------------------------------------------------
         N=NMD
         !!WRITE(6,887) VKE*EUNIT/DBLE(N),VPE*EUNIT/DBLE(N),VAV*LUNIT**3/DBLE(N)
         WRITE(77,887) VKE*EUNIT/DBLE(N),VPE*EUNIT/DBLE(N),VAV*LUNIT**3/DBLE(N)
         NSTEP=ITN-1
80    FORMAT(1X,'ITN=',I6,2X,'K.E.=',E11.4,'eV',2X,'P.E.=',E11.4,'eV',2X,'TOTAL=',E11.4,'eV',/,2X,'P=',E11.4,'eV/A**3',2X,'DV/V=',F8.3,'%')

887   FORMAT(//,2X,'<K.E.>=',E11.4,2X,'<P.E.>=',E11.4,2X,'<CELL VOL.>=',E11.4)

!c     Call TACF(VXC,VYC,VZC,NMD,NALL)

!ccccccccccccccccccccc

      OPEN(22,FILE='SHARIF.DAT',STATUS='OLD')
!C----The subroutine that outputs the results-----------------
      CALL OUTCRD(NSTEP,BOXX,BOXY,BOXZ,RX,RY,RZ,IP,NALL,VX,VY,VZ,TEMP,TITLE,OLDV)
      CLOSE(22)
!C---------------------------------------------------------------------
!C      STOP 

     
      RETURN
      
end subroutine Simulation


!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

!C------The subroutine that enforces periodic boundary conditions

      SUBROUTINE IMPRSN(RX,RY,RZ,NALL,BOXX,BOXY,BOXZ)
      IMPLICIT NONE
      REAL*8 RX,RY,RZ,BOXX,BOXY,BOXZ
      INTEGER NALL,I
      DIMENSION RX(NALL),RY(NALL),RZ(NALL)
!C
      DO 5 I=1,NALL
      RX(I)=RX(I)-BOXX*ANINT(RX(I)/BOXX)
      RY(I)=RY(I)-BOXY*ANINT(RY(I)/BOXY)
      RZ(I)=RZ(I)-BOXZ*ANINT(RZ(I)/BOXZ)

5     CONTINUE
!c=========================  Neek Addition
      
!c==========================	
      RETURN
      END SUBROUTINE IMPRSN
      
      
      
 !     ccccccccccccccccccccccccccc
      SUBROUTINE INCRD(NSTEP,NALL,NMAX,RX,RY,RZ,IP,BOXX,BOXY,BOXZ,VX,VY,VZ,TITLE,OLDV,RCMAX)
      IMPLICIT NONE
      INTEGER NALL,NMAX,IP
      INTEGER I,NSTEP
      CHARACTER TITLE*80
!C--------------------------------------
      REAL*8 RX,RY,RZ,BOXX,BOXY,BOXZ,VX,VY,VZ,OLDV,RCMAX
!C------------------------------------------------
      DIMENSION RX(NMAX),RY(NMAX),RZ(NMAX),IP(NMAX)
      DIMENSION VX(NMAX),VY(NMAX),VZ(NMAX)
!C------------------------------------------
      READ(22,*) NSTEP
      READ(22,99) TITLE
      READ(22,*) NALL
      READ(22,*) BOXX,BOXY,BOXZ
!C----------
      READ(22,*) (RX(I),RY(I),RZ(I),IP(I),I=1,NALL)
!C---------------
       IF(NSTEP.NE.0)THEN
       READ(22,*)OLDV
       ENDIF
!C------------------------
       IF(NSTEP.NE.0)THEN
        READ(22,*) (VX(I),VY(I),VZ(I),I=1,NALL)
      ENDIF
!C----------------
      IF(NSTEP.EQ.0) OLDV=BOXX*BOXY*BOXZ
!C----------------
      !!WRITE(6,250) TITLE
      !!WRITE(6,1000) NALL
      !WRITE(6,1001)BOXX,BOXY,BOXZ
      WRITE(77,250) TITLE
      WRITE(77,1000) NALL
      WRITE(77,1001)BOXX,BOXY,BOXZ
 
    IF(BOXX.LT.2.*RCMAX.OR.BOXY.LT.2.*RCMAX.OR.BOXZ.LT.0.5*RCMAX)THEN
    !WRITE(6,*)'YOU MUST DECREASE THE CUTOFF RADIUS OF POTENTIAL'
    !WRITE(6,*)'OR INCREASE THE SIZE OF THE 3-D PERIODIC CELL'
    STOP
    ENDIF
!C 
99    FORMAT(A80)
999   FORMAT((1X,A2,2X,A4))
250   FORMAT(/,2X,'CONFIGURATION FILE TITLE:',/,2X,A80)
1000  FORMAT(/,2X,'NALL=',I6,2X,'ATOMS',//)
1001  FORMAT(/,2X,'X,Y,Z BOX SIDES:',3E13.4)
      RETURN
      END SUBROUTINE INCRD


!C----The subroutine that updates the atomic position using velocity Verlet algorithms
      SUBROUTINE RMOVES(NALL,RX,VX,RY,VY,RZ,VZ,DT,BMASS,IP,FX,FY,FZ,DT2,DTSQ,BOXX,BOXY,BOXZ)
!C
      IMPLICIT NONE
      REAL*8 RX,VX,RY,VY,RZ,VZ,FX,FY,FZ,DT2,DTSQ,DT
      REAL*8 BOXX,BOXY,BOXZ,MASS,BMASS
!C--------------------------------
      INTEGER NALL,NATL,IP,I,J,K,II
!C------------------------------------
      DIMENSION RX(NALL),VX(NALL),RY(NALL),VY(NALL)
      DIMENSION RZ(NALL),VZ(NALL),FX(NALL),FY(NALL),FZ(NALL)
      DIMENSION IP(NALL)
!C----------------------------------------
         MASS=BMASS
        DO I=1,NALL
        RX(I) = RX(I) + VX(I)*DT + DTSQ*(FX(I)/MASS)
        RY(I) = RY(I) + VY(I)*DT + DTSQ*(FY(I)/MASS)
        RZ(I) = RZ(I) + VZ(I)*DT + DTSQ*(FZ(I)/MASS)
        VX(I) = VX(I) + DT2*(FX(I)/MASS)
        VY(I) = VY(I) + DT2*(FY(I)/MASS)
        VZ(I) = VZ(I) + DT2*(FZ(I)/MASS)
         ENDDO
         RETURN
         END SUBROUTINE RMOVES

!C-------The subroutine that updates the atomic velocities---
       SUBROUTINE VMOVES(NALL,VX,VY,VZ,FX,FY,FZ,DT2,BMASS,SUMKE,IP,DT,itn,vxc,vyc,vzc,nmd)
!C
      IMPLICIT NONE
      REAL*8 VX,VY,VZ,FX,FY,FZ,DT2,SCALE1,SCALE2,vxc,vyc,vzc
      REAL*8 SUMKE,MASS,BMASS,DT
!C-----------------------------------------------
      INTEGER NALL,I,IP,NATL,J,itn,nmd
      DIMENSION IP(NALL)
      DIMENSION VX(NALL),VY(NALL),VZ(NALL),FX(NALL),FY(NALL),FZ(NALL)
!C--------------------------------------------
      SUMKE=0.0D0
!C************************
       MASS=BMASS
      DO I=1,NALL
           VX(I) =  (VX(I)+DT2*FX(I)/MASS)
           VY(I) =  (VY(I)+DT2*FY(I)/MASS)
           VZ(I) =  (VZ(I)+DT2*FZ(I)/MASS)
      SUMKE= SUMKE + MASS*(VX(I)*VX(I) + VY(I)*VY(I) + VZ(I)*VZ(I))
      ENDDO

      SUMKE=SUMKE/2.
!C-------Addition---
     
!C-----------------

      RETURN
      END SUBROUTINE VMOVES



!C------The subroutine that computes the L-J potential and force--
      SUBROUTINE LENNARD_JONES (RX,RY,RZ,FX,FY,FZ,H,PRESSR,NALL,BOXX,BOXY,BOXZ)
      IMPLICIT NONE
      INTEGER NALL,I,J,NB
!C--------------------------------------
      REAL*8 RXI,RYI,RZI,RZJ,DZ,RXJ,DX,RYJ,DY
      REAL*8 RX,RY,RZ,BOXX,BOXY,BOXZ,RJ,R2
      REAL*8 SIGMA,EPSI,EREP_C,EATT_C,FREP_C,FATT_C
      REAL*8 FIJDXI_C,FIJDYI_C,FIJDZI_C
      REAL*8 FIJDXJ_C,FIJDYJ_C,FIJDZJ_C
      REAL*8 FX,FY,FZ,FR_C,FA_C
      REAL*8 H,FIJR_C,PRESSR
!C-------------------------------------
      DIMENSION RX(NALL),RY(NALL),RZ(NALL)
      DIMENSION FX(NALL),FY(NALL),FZ(NALL)
!C----------------------
      DO  NB=1,NALL
      FX(NB)=0.
      FY(NB)=0.
      FZ(NB)=0.
      END DO
!C---------------------------
      H=0.0D0
      PRESSR=0.
!C-----Argon Potential Parameter
      SIGMA=3.405/5.31
      EPSI=4.0*0.01035/0.01035
!C-----------------------------
      DO 13 I=1,NALL-1
            RXI=RX(I)
            RYI=RY(I)
            RZI=RZ(I)
      DO 11 J=I+1,NALL
                DZ=RZI-RZ(J)
                DZ=DZ-BOXZ*ANINT(DZ/BOXZ)
                R2=DZ*DZ
                DX=RXI-RX(J)
                DX=DX-BOXX*ANINT(DX/BOXX)
                R2=R2+DX*DX
                DY=RYI-RY(J)
                DY=DY-BOXY*ANINT(DY/BOXY)
                R2=R2+DY*DY
           RJ=DSQRT(R2)
           FR_C=EPSI*((SIGMA/RJ)**DBLE(12))
           FA_C=EPSI*((SIGMA/RJ)**DBLE(6))
           FREP_C=EPSI*((SIGMA/RJ)**DBLE(12))*(-12.0/RJ)
           FATT_C=EPSI*((SIGMA/RJ)**DBLE(6))*(6.0/RJ)
           H=H+(FR_C-FA_C)
           FIJR_C=(FREP_C+FATT_C)
!C----------------
           FIJDXI_C=FIJR_C*DX/RJ
           FIJDYI_C=FIJR_C*DY/RJ
           FIJDZI_C=FIJR_C*DZ/RJ
           FIJDXJ_C=-FIJDXI_C
           FIJDYJ_C=-FIJDYI_C
           FIJDZJ_C=-FIJDZI_C
!C-----------------
           FX(I)=FX(I)-FIJDXI_C
           FY(I)=FY(I)-FIJDYI_C
           FZ(I)=FZ(I)-FIJDZI_C
           FX(J)=FX(J)-FIJDXJ_C
           FY(J)=FY(J)-FIJDYJ_C
           FZ(J)=FZ(J)-FIJDZJ_C
           PRESSR=PRESSR-(FIJDXI_C*DX+FIJDYI_C*DY+FIJDZI_C*DZ)
11    CONTINUE
13    CONTINUE
       PRESSR=PRESSR/3.
!C
      RETURN
      END SUBROUTINE LENNARD_JONES
!C-----The subroutine that outputs the simulation results---
      SUBROUTINE OUTCRD(NSTEP,BOXX,BOXY,BOXZ,RX,RY,RZ,IP,NALL,VX,VY,VZ,TEMP,TITLE,OLDV)
      IMPLICIT NONE
!C-----------------------------
      REAL*8 BOXX,BOXY,RX,RY,RZ,VX,VY,VZ,TEMP1,DT,BOXZ
      REAL*8 OLDV,TEMP
!C--------------------------
      INTEGER IP,NALL,I,NSTEP
      CHARACTER TITLE*80
!C-----------------------------
      DIMENSION RX(NALL),RY(NALL),RZ(NALL),IP(NALL)
      DIMENSION VX(NALL),VY(NALL),VZ(NALL)
!C------------------------------
      CALL IMPRSN(RX,RY,RZ,NALL,BOXX,BOXY,BOXZ)
      WRITE(22,100) NSTEP
      WRITE(22,99) TITLE
      WRITE(22,100) NALL
      WRITE(22,111) BOXX,BOXY,BOXZ
      WRITE(22,110) (RX(I),RY(I),RZ(I),IP(I),I=1,NALL)
      WRITE(22,113) OLDV
      WRITE(22,111) (VX(I),VY(I),VZ(I),I=1,NALL)
99    FORMAT(A80)
999   FORMAT((1X,A2,2X,A4))
100   FORMAT(2I8)
110   FORMAT(3E25.16,I6)
111   FORMAT(3E25.16)
112   FORMAT(E25.16)
113   FORMAT(2(1X,E25.16))
      RETURN
      END SUBROUTINE OUTCRD
!C-----The subroutine that sets up the initial random velocities
!C-----according to Maxwell-Boltzmann distribution-------------
      SUBROUTINE STRTUP(NSTEP,RX,RY,RZ,VX,VY,VZ,NALL,TEMP,DT,DT2,DTSQ,IP,BMASS)
      IMPLICIT NONE
!C-------------------------------------
      REAL*8 RTEMP,DUMMY,GAUSS,SUMX,SUMY,SUMZ
      REAL*8 RX,RY,RZ,VX,VY,VZ,TEMP,DT,DT2,DTSQ
      REAL*8 BMASS,MASS,RMASS
      REAL*4 RMAXY
!C--------------------------------------------------
      INTEGER NSTEP,NALL,I,IP,KOUNT
      INTEGER PP,QQ,INTSIZ,IDELAY,MM(100),MAX,II,K1
      INTEGER J,K,N
!C--------------------------------------------------
      COMMON/RANDOM2/MM,PP,QQ,INTSIZ,IDELAY
      COMMON/RANDOM1/RMAXY
!C------------------------------------------------
      DIMENSION RX(NALL),VX(NALL),RY(NALL),VY(NALL)
      DIMENSION RZ(NALL),VZ(NALL),IP(NALL)
!C******************************
      DT2=DT/2.
      DTSQ=DT*DT/2.
!C************************
!C  INITIALISE RANDOM NUMBER GENERATOR:
      PP=98
      QQ=27
      INTSIZ=31
      IDELAY=9800
      MAX=(2**(INTSIZ-1)-1)*2+1
      RMAXY=MAX
      II=5321
      CALL SETR(II)
!C*******************************
      RTEMP=SQRT(TEMP)
      MASS=BMASS
      RMASS=SQRT(MASS)
!C------------------------
      DO 10 I=1,NALL
      VX(I)=RTEMP*GAUSS(DUMMY)/RMASS
      VY(I)=RTEMP*GAUSS(DUMMY)/RMASS
      VZ(I)=RTEMP*GAUSS(DUMMY)/RMASS
10    CONTINUE
!C*********************************
      SUMX=0.0D0
      SUMY=0.0D0
      SUMZ=0.0D0
!C*************************************
      DO 20 I=1,NALL
      SUMX=SUMX+MASS*VX(I)
      SUMY=SUMY+MASS*VY(I)
      SUMZ=SUMZ+MASS*VZ(I)
20    CONTINUE
!C*************************************
      SUMX=SUMX/DBLE(NALL)
      SUMY=SUMY/DBLE(NALL)
      SUMZ=SUMZ/DBLE(NALL)
!C**********************************
      DO 30 I=1,NALL
      VX(I)=VX(I)-SUMX/MASS
      VY(I)=VY(I)-SUMY/MASS
      VZ(I)=VZ(I)-SUMZ/MASS
30    CONTINUE
!C*********************************
      RETURN
      END SUBROUTINE STRTUP
!C****************************
      FUNCTION GAUSS(DUMMY)
      IMPLICIT NONE
      REAL*8 DUMMY,A1,A3,A5,A7,A9,SUM,G05CAF,R,R2,GAUSS,Y
      REAL*4 X
      INTEGER I,KOUNT
!C
      PARAMETER (A1=3.949846138,A3=0.252408784,A5=0.076542912)
      PARAMETER (A7=0.008355968,A9=0.029899776)
!C
      SUM=0
      DO 1091 I=1,12
      CALL RANDY(X)
      SUM=SUM+(X)
1091    CONTINUE
!C
      R=(SUM-6.0)/4.0
      R2=R*R
      GAUSS=((((A9*R2+A7)*R2+A5)*R2+A3)*R2+A1)*R
!C
      RETURN
      END FUNCTION GAUSS
!C----The subroutine that contains the simulation parameters--
      SUBROUTINE POTIN(BMASS,MUNIT,EUNIT,LUNIT,DT,TEMP,NALL,TMP)
      IMPLICIT NONE
!C---------------------------
!C------------------------------
      INTEGER I,NALL
!C------------------------------
      REAL*8 TIME,TMP,DT,TEMP
      REAL*8 BMASS,LUNIT,MUNIT,EUNIT
      REAL*8 PI / 3.14159265358979 /
!C--------------------------------------------
      MUNIT=39.90D0
      LUNIT=5.31
      EUNIT=0.01035
      
      BMASS=39.90D0/MUNIT
      TIME=MUNIT*LUNIT*LUNIT/EUNIT
      TIME=SQRT(TIME*0.1/6.022/1.602)*1.E-13
!C
      !WRITE(6,360) TIME
360   FORMAT(2X,'UNIT OF TIME=',E10.3,' SECONDS')
      WRITE(77,360) TIME
!C
      DT=DT/TIME
      !WRITE(6,361) DT
361   FORMAT(2X,'SIMULATION TIME-STEP=',E10.3,' TIME UNITS')
      WRITE(77,361) DT
!C
      !WRITE(6,465) EUNIT
465   FORMAT(2X,'UNIT OF ENERGY=',E11.4,' eV')
      WRITE(77,465) EUNIT
!C
      !WRITE(6,466) LUNIT
466   FORMAT(2X,'UNIT OF LENGTH=',F6.4,' ANGSTROMS')
      WRITE(77,466) LUNIT
      
      !WRITE(6,467) MUNIT
467   FORMAT(2X,'UNIT OF MASS=',F6.2,' g/MOLE')
      WRITE(77,467) MUNIT
!C
      TMP=EUNIT*1.602E-19/1.381E-23
      !WRITE(6,365) TMP
365   FORMAT(2X,'UNIT OF TEMPERATURE=',E10.3,' KELVIN',/,2X,'(I.E. k * UNIT OF TEMPERATURE = UNIT OF ENERGY)')
      WRITE(77,365) TMP
!C
      TEMP=TEMP/TMP
      !WRITE(6,362) TEMP
362   FORMAT(2X,'SUB_SIMUL TEMPERATURE=',E10.3,' TEMPERATURE UNITS',///)
	  WRITE(77,362) TEMP
      RETURN
      END SUBROUTINE POTIN
      
!C-----The subroutine that scales the velocities to keep the temperature constant----
      SUBROUTINE TSCALE(TEMP,NALL,VX,VY,VZ,SUMKE,CURTMP)
      IMPLICIT NONE
      INTEGER N,NALL
      REAL*8 SCALE,TEMP,CURTMP,VX,VY,VZ,SUMKE
      DIMENSION VX(NALL),VY(NALL),VZ(NALL)
!C------------------------------------
      SCALE=SQRT(TEMP/CURTMP)
!C-------------------------------
      DO N=1,NALL
      VX(N)=SCALE*VX(N)
      VY(N)=SCALE*VY(N)
      VZ(N)=SCALE*VZ(N)
      ENDDO
!C-------------------------
       SUMKE=SUMKE*SCALE*SCALE
      RETURN
      END SUBROUTINE TSCALE
      
!C-----The subroutine that scales the volume--------------
      SUBROUTINE VSCALE(PRESSR,PDT,DT,RX,RY,BOXX,BOXY,NALL)
      IMPLICIT NONE
      INTEGER NALL,N
      REAL*8 PRESSR,PDT,DT,RX,RY,BOXX,BOXY,BOXZ,RZ
      REAL*8 SCALER
      DIMENSION RX(NALL),RY(NALL)
!C
      SCALER=1.0+(DT/PDT)*PRESSR
      DO 10 N=1,NALL
      RX(N)=SCALER*RX(N)
      RY(N)=SCALER*RY(N)
10    CONTINUE
      BOXX=BOXX*SCALER
      BOXY=BOXY*SCALER
!C
      RETURN
      END SUBROUTINE VSCALE
      
!C-----The random number generator subroutine------
      SUBROUTINE RANDY(X)
      IMPLICIT NONE
      INTEGER P,Q,INTSIZ,IDELAY,M(100)
      REAL*4 RMAXY,X
      INTEGER J,K
      COMMON/RANDOM2/M,P,Q,INTSIZ,IDELAY
      COMMON/RANDOM1/RMAXY
      COMMON/RJ/J
      J=MOD(J,P)+1
      K=MOD(J+Q-1,P)+1
      M(J)=IEOR(M(J),M(K))
      X=FLOAT(M(J))/RMAXY
      RETURN
      END SUBROUTINE RANDY
      
!C-----The subroutine called by the random number generator----
      SUBROUTINE SETR(ISETR)
      IMPLICIT NONE
      INTEGER P,Q,INTSIZ,IDELAY,M(100)
      INTEGER ONE,J0,ISETR,K,J,INTS,KOUNT,I,PP,ITEMP
      REAL*4 RMAXY,X
      COMMON/RANDOM2/M,P,Q,INTSIZ,IDELAY
      COMMON/RANDOM1/RMAXY
      COMMON/RJ/J0
      J0=0
      ISETR=P+1
      ONE=2**(INTSIZ-1)
      DO 1 I=1,P
  1   M(I)=ONE
      INTS=INTSIZ
      DO 4 K=1,INTS
      DO 2 J=1,IDELAY
  2   CALL RANDY(X)
      KOUNT=0
      DO 3 I=1,P
      ITEMP=ONE/2**(K-1)
      ITEMP=(M(I)-M(I)/ONE*ONE)/ITEMP
      IF(ITEMP.EQ.1)KOUNT=KOUNT+1
      IF(K.EQ.INTSIZ)GOTO 3
      M(I)=M(I)/2+ONE
  3   CONTINUE
      IF(KOUNT.EQ.P)ISETR=K
  4   CONTINUE
      PP=P
      DO 6 I=1,5000
      DO 5 J=1,PP
  5   CALL RANDY(X)
  6   CONTINUE
      RETURN
      END SUBROUTINE SETR
