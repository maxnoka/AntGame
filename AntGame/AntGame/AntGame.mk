##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## MacDebug
ProjectName            :=AntGame
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/Users/MaxNoka/OneDrive/Projects/AntGame/AntGame
ProjectPath            :=/Users/MaxNoka/OneDrive/Projects/AntGame/AntGame/AntGame
IntermediateDirectory  :=../build-$(ConfigurationName)/AntGame
OutDir                 :=../build-$(ConfigurationName)/AntGame
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Maximilian Noka
Date                   :=21/04/2021
CodeLitePath           :="/Users/MaxNoka/Library/Application Support/CodeLite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
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
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=../build-$(ConfigurationName)/AntGame/main.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/AntGame/foo.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/AntGame/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/AntGame"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/AntGame"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/AntGame/.d:
	@mkdir -p "../build-$(ConfigurationName)/AntGame"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/AntGame/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/AntGame/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/MaxNoka/OneDrive/Projects/AntGame/AntGame/AntGame/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AntGame/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AntGame/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AntGame/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/AntGame/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AntGame/main.cpp$(PreprocessSuffix) main.cpp

../build-$(ConfigurationName)/AntGame/foo.cpp$(ObjectSuffix): foo.cpp ../build-$(ConfigurationName)/AntGame/foo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/MaxNoka/OneDrive/Projects/AntGame/AntGame/AntGame/foo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/foo.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AntGame/foo.cpp$(DependSuffix): foo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AntGame/foo.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AntGame/foo.cpp$(DependSuffix) -MM foo.cpp

../build-$(ConfigurationName)/AntGame/foo.cpp$(PreprocessSuffix): foo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AntGame/foo.cpp$(PreprocessSuffix) foo.cpp


-include ../build-$(ConfigurationName)/AntGame//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


