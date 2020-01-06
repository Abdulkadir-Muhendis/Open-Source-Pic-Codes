#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-dsp33ep512gm710.mk)" "nbproject/Makefile-local-dsp33ep512gm710.mk"
include nbproject/Makefile-local-dsp33ep512gm710.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=dsp33ep512gm710
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/firdelay.s ../src/get_errloc.s ../src/tglpin.s ../src/traps.c ../src/system_config/exp16/dspic33ep512gm710/adc1drv.c ../src/system_config/exp16/dspic33ep512gm710/main.c ../src/fir.s ../src/firinit.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/firdelay.o ${OBJECTDIR}/_ext/1360937237/get_errloc.o ${OBJECTDIR}/_ext/1360937237/tglpin.o ${OBJECTDIR}/_ext/1360937237/traps.o ${OBJECTDIR}/_ext/54238140/adc1drv.o ${OBJECTDIR}/_ext/54238140/main.o ${OBJECTDIR}/_ext/1360937237/fir.o ${OBJECTDIR}/_ext/1360937237/firinit.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/firdelay.o.d ${OBJECTDIR}/_ext/1360937237/get_errloc.o.d ${OBJECTDIR}/_ext/1360937237/tglpin.o.d ${OBJECTDIR}/_ext/1360937237/traps.o.d ${OBJECTDIR}/_ext/54238140/adc1drv.o.d ${OBJECTDIR}/_ext/54238140/main.o.d ${OBJECTDIR}/_ext/1360937237/fir.o.d ${OBJECTDIR}/_ext/1360937237/firinit.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/firdelay.o ${OBJECTDIR}/_ext/1360937237/get_errloc.o ${OBJECTDIR}/_ext/1360937237/tglpin.o ${OBJECTDIR}/_ext/1360937237/traps.o ${OBJECTDIR}/_ext/54238140/adc1drv.o ${OBJECTDIR}/_ext/54238140/main.o ${OBJECTDIR}/_ext/1360937237/fir.o ${OBJECTDIR}/_ext/1360937237/firinit.o

# Source Files
SOURCEFILES=../src/firdelay.s ../src/get_errloc.s ../src/tglpin.s ../src/traps.c ../src/system_config/exp16/dspic33ep512gm710/adc1drv.c ../src/system_config/exp16/dspic33ep512gm710/main.c ../src/fir.s ../src/firinit.s


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-dsp33ep512gm710.mk dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512GM710
MP_LINKER_FILE_OPTION=,--script=p33EP512GM710.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/traps.o: ../src/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/traps.c  -o ${OBJECTDIR}/_ext/1360937237/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/54238140/adc1drv.o: ../src/system_config/exp16/dspic33ep512gm710/adc1drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/54238140" 
	@${RM} ${OBJECTDIR}/_ext/54238140/adc1drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/54238140/adc1drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/system_config/exp16/dspic33ep512gm710/adc1drv.c  -o ${OBJECTDIR}/_ext/54238140/adc1drv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/54238140/adc1drv.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/54238140/adc1drv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/54238140/main.o: ../src/system_config/exp16/dspic33ep512gm710/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/54238140" 
	@${RM} ${OBJECTDIR}/_ext/54238140/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/54238140/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/system_config/exp16/dspic33ep512gm710/main.c  -o ${OBJECTDIR}/_ext/54238140/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/54238140/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/54238140/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1360937237/traps.o: ../src/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/traps.c  -o ${OBJECTDIR}/_ext/1360937237/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/traps.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/54238140/adc1drv.o: ../src/system_config/exp16/dspic33ep512gm710/adc1drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/54238140" 
	@${RM} ${OBJECTDIR}/_ext/54238140/adc1drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/54238140/adc1drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/system_config/exp16/dspic33ep512gm710/adc1drv.c  -o ${OBJECTDIR}/_ext/54238140/adc1drv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/54238140/adc1drv.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/54238140/adc1drv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/54238140/main.o: ../src/system_config/exp16/dspic33ep512gm710/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/54238140" 
	@${RM} ${OBJECTDIR}/_ext/54238140/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/54238140/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/system_config/exp16/dspic33ep512gm710/main.c  -o ${OBJECTDIR}/_ext/54238140/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/54238140/main.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/54238140/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/firdelay.o: ../src/firdelay.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firdelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firdelay.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/firdelay.s  -o ${OBJECTDIR}/_ext/1360937237/firdelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/firdelay.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/firdelay.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/get_errloc.o: ../src/get_errloc.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/get_errloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/get_errloc.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/get_errloc.s  -o ${OBJECTDIR}/_ext/1360937237/get_errloc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/get_errloc.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/get_errloc.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/tglpin.o: ../src/tglpin.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tglpin.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tglpin.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/tglpin.s  -o ${OBJECTDIR}/_ext/1360937237/tglpin.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/tglpin.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/tglpin.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/fir.o: ../src/fir.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fir.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fir.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/fir.s  -o ${OBJECTDIR}/_ext/1360937237/fir.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/fir.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/fir.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/firinit.o: ../src/firinit.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firinit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firinit.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/firinit.s  -o ${OBJECTDIR}/_ext/1360937237/firinit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/firinit.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/firinit.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1360937237/firdelay.o: ../src/firdelay.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firdelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firdelay.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/firdelay.s  -o ${OBJECTDIR}/_ext/1360937237/firdelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/firdelay.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/firdelay.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/get_errloc.o: ../src/get_errloc.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/get_errloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/get_errloc.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/get_errloc.s  -o ${OBJECTDIR}/_ext/1360937237/get_errloc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/get_errloc.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/get_errloc.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/tglpin.o: ../src/tglpin.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tglpin.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tglpin.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/tglpin.s  -o ${OBJECTDIR}/_ext/1360937237/tglpin.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/tglpin.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/tglpin.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/fir.o: ../src/fir.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fir.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fir.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/fir.s  -o ${OBJECTDIR}/_ext/1360937237/fir.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/fir.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/fir.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/firinit.o: ../src/firinit.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firinit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/firinit.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../src/firinit.s  -o ${OBJECTDIR}/_ext/1360937237/firinit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -I"../src" -Wa,-MD,"${OBJECTDIR}/_ext/1360937237/firinit.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/firinit.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=dsp,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=dsp,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/fir_adc_dma.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/dsp33ep512gm710
	${RM} -r dist/dsp33ep512gm710

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
