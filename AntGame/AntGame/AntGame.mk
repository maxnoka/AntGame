##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=AntGame
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=D:/git/AntGame/AntGame
ProjectPath            :=D:/git/AntGame/AntGame/AntGame
IntermediateDirectory  :=../build-$(ConfigurationName)/AntGame
OutDir                 :=../build-$(ConfigurationName)/AntGame
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Daniel
Date                   :=21/04/2021
CodeLitePath           :=D:/Programs/CodeLite
LinkerName             :=D:/MinGW/bin/g++.exe
SharedObjectLinkerName :=D:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=D:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/MinGW/bin/ar.exe rcu
CXX      := D:/MinGW/bin/g++.exe
CC       := D:/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := D:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\Programs\CodeLite
Objects0=../build-$(ConfigurationName)/AntGame/foo.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/AntGame/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/AntGame/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\AntGame" mkdir "..\build-$(ConfigurationName)\AntGame"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\AntGame" mkdir "..\build-$(ConfigurationName)\AntGame"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/AntGame/.d:
	@if not exist "..\build-$(ConfigurationName)\AntGame" mkdir "..\build-$(ConfigurationName)\AntGame"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/AntGame/foo.cpp$(ObjectSuffix): foo.cpp ../build-$(ConfigurationName)/AntGame/foo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/git/AntGame/AntGame/AntGame/foo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/foo.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AntGame/foo.cpp$(DependSuffix): foo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AntGame/foo.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AntGame/foo.cpp$(DependSuffix) -MM foo.cpp

../build-$(ConfigurationName)/AntGame/foo.cpp$(PreprocessSuffix): foo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AntGame/foo.cpp$(PreprocessSuffix) foo.cpp

../build-$(ConfigurationName)/AntGame/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/AntGame/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/git/AntGame/AntGame/AntGame/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AntGame/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AntGame/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AntGame/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/AntGame/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AntGame/main.cpp$(PreprocessSuffix) main.cpp


-include ../build-$(ConfigurationName)/AntGame//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


