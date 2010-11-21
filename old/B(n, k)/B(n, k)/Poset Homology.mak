# Microsoft Developer Studio Generated NMAKE File, Based on Poset Homology.dsp
!IF "$(CFG)" == ""
CFG=Poset Homology - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Poset Homology - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Poset Homology - Win32 Release" && "$(CFG)" != "Poset Homology - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Poset Homology.mak" CFG="Poset Homology - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Poset Homology - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Poset Homology - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Poset Homology - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Poset Homology.exe"


CLEAN :
	-@erase "$(INTDIR)\basis.obj"
	-@erase "$(INTDIR)\chain.obj"
	-@erase "$(INTDIR)\Hom.obj"
	-@erase "$(INTDIR)\Matrix.obj"
	-@erase "$(INTDIR)\Partition.obj"
	-@erase "$(INTDIR)\Perm.obj"
	-@erase "$(INTDIR)\RankSet.obj"
	-@erase "$(INTDIR)\tableau.obj"
	-@erase "$(INTDIR)\tabloid.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Poset Homology.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Poset Homology.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Poset Homology.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Poset Homology.pdb" /machine:I386 /out:"$(OUTDIR)\Poset Homology.exe" 
LINK32_OBJS= \
	"$(INTDIR)\basis.obj" \
	"$(INTDIR)\chain.obj" \
	"$(INTDIR)\Hom.obj" \
	"$(INTDIR)\Matrix.obj" \
	"$(INTDIR)\Partition.obj" \
	"$(INTDIR)\Perm.obj" \
	"$(INTDIR)\RankSet.obj" \
	"$(INTDIR)\tableau.obj" \
	"$(INTDIR)\tabloid.obj"

"$(OUTDIR)\Poset Homology.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Poset Homology - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Poset Homology.exe"


CLEAN :
	-@erase "$(INTDIR)\basis.obj"
	-@erase "$(INTDIR)\chain.obj"
	-@erase "$(INTDIR)\Hom.obj"
	-@erase "$(INTDIR)\Matrix.obj"
	-@erase "$(INTDIR)\Partition.obj"
	-@erase "$(INTDIR)\Perm.obj"
	-@erase "$(INTDIR)\RankSet.obj"
	-@erase "$(INTDIR)\tableau.obj"
	-@erase "$(INTDIR)\tabloid.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Poset Homology.exe"
	-@erase "$(OUTDIR)\Poset Homology.ilk"
	-@erase "$(OUTDIR)\Poset Homology.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Poset Homology.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Poset Homology.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Poset Homology.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Poset Homology.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\basis.obj" \
	"$(INTDIR)\chain.obj" \
	"$(INTDIR)\Hom.obj" \
	"$(INTDIR)\Matrix.obj" \
	"$(INTDIR)\Partition.obj" \
	"$(INTDIR)\Perm.obj" \
	"$(INTDIR)\RankSet.obj" \
	"$(INTDIR)\tableau.obj" \
	"$(INTDIR)\tabloid.obj"

"$(OUTDIR)\Poset Homology.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Poset Homology.dep")
!INCLUDE "Poset Homology.dep"
!ELSE 
!MESSAGE Warning: cannot find "Poset Homology.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Poset Homology - Win32 Release" || "$(CFG)" == "Poset Homology - Win32 Debug"
SOURCE=.\basis.cpp

"$(INTDIR)\basis.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\chain.cpp

"$(INTDIR)\chain.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Hom.cpp

"$(INTDIR)\Hom.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\Perm Test\Matrix.cpp"

"$(INTDIR)\Matrix.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Partition.cpp

"$(INTDIR)\Partition.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Perm.cpp

"$(INTDIR)\Perm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RankSet.cpp

"$(INTDIR)\RankSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tableau.cpp

"$(INTDIR)\tableau.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tabloid.cpp

"$(INTDIR)\tabloid.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

