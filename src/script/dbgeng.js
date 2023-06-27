
const assert = require("assert");

const typing = require("typing");

const binding = require("binding");

const fmt = require('fmt');

const int = require("integer");

const Int64 = int.Int64;
const Uint64 = int.Uint64;

// Classes of debuggee.  Each class
// has different qualifiers for specific
// kinds of debuggees.
exports.DEBUG_CLASS_UNINITIALIZED  = 0;
exports.DEBUG_CLASS_KERNEL        = 1;
exports.DEBUG_CLASS_USER_WINDOWS  = 2;
exports.DEBUG_CLASS_IMAGE_FILE    = 3;




// Generic dump types.  These can be used
// with either user or kernel sessions.
// Session-type-specific aliases are also
// provided.
exports.DEBUG_DUMP_SMALL = 1024;

exports.DEBUG_DUMP_DEFAULT = 1025;

exports.DEBUG_DUMP_FULL = 1026;

exports.DEBUG_DUMP_IMAGE_FILE = 1027;

exports.DEBUG_DUMP_TRACE_LOG = 1028;

exports.DEBUG_DUMP_WINDOWS_CE = 1029;

exports.DEBUG_DUMP_ACTIVE = 1030;


// Specific types of kernel debuggees.
exports.DEBUG_KERNEL_CONNECTION = 0;

exports.DEBUG_KERNEL_LOCAL = 1;

exports.DEBUG_KERNEL_EXDI_DRIVER = 2;

exports.DEBUG_KERNEL_IDNA = 3;

exports.DEBUG_KERNEL_INSTALL_DRIVER = 4;

exports.DEBUG_KERNEL_REPT = 5;


exports.DEBUG_KERNEL_SMALL_DUMP = exports.DEBUG_DUMP_SMALL;

exports.DEBUG_KERNEL_DUMP = exports.DEBUG_DUMP_DEFAULT;


exports.DEBUG_KERNEL_ACTIVE_DUMP = exports.DEBUG_DUMP_ACTIVE;


exports.DEBUG_KERNEL_FULL_DUMP = exports.DEBUG_DUMP_FULL;


exports.DEBUG_KERNEL_TRACE_LOG = exports.DEBUG_DUMP_TRACE_LOG;


// Specific types of Windows user debuggees.

exports.DEBUG_USER_WINDOWS_PROCESS = 0;

exports.DEBUG_USER_WINDOWS_PROCESS_SERVER = 1;

exports.DEBUG_USER_WINDOWS_IDNA = 2;


exports.DEBUG_USER_WINDOWS_REPT = 3;

exports.DEBUG_USER_WINDOWS_SMALL_DUMP = exports.DEBUG_DUMP_SMALL;

exports.DEBUG_USER_WINDOWS_DUMP = exports.DEBUG_DUMP_DEFAULT;

exports.DEBUG_USER_WINDOWS_DUMP_WINDOWS_CE = exports.DEBUG_DUMP_WINDOWS_CE;



//----------
// for CodeLevel
exports.DEBUG_LEVEL_SOURCE = 0;
exports.DEBUG_LEVEL_ASSEMBLY = 1;





// Indices for ReadDebuggerData interface

const debugDataIndices = {
    KernBase                           : 24,
    BreakpointWithStatus              :32,
    SavedContext                      :40,
    KiCallUserMode                    :56,
    KeUserCallbackDispatcher          :64,
    PsLoadedModuleList                :72,
    PsActiveProcessHead               :80,
    PspCidTable                       :88,
    ExpSystemResourcesList            :96,
    ExpPagedPoolDescriptor           :104,
    ExpNumberOfPagedPools            :112,
    KeTimeIncrement                  :120,
    KeBugCheckCallbackListHead       :128,
    KiBugcheckData                   :136,
    IopErrorLogListHead              :144,
    ObpRootDirectoryObject           :152,
    ObpTypeObjectType                :160,
    MmSystemCacheStart               :168,
    MmSystemCacheEnd                 :176,
    MmSystemCacheWs                  :184,
    MmPfnDatabase                    :192,
    MmSystemPtesStart                :200,
    MmSystemPtesEnd                  :208,
    MmSubsectionBase                 :216,
    MmNumberOfPagingFiles            :224,
    MmLowestPhysicalPage             :232,
    MmHighestPhysicalPage            :240,
    MmNumberOfPhysicalPages          :248,
    MmMaximumNonPagedPoolInBytes     :256,
    MmNonPagedSystemStart            :264,
    MmNonPagedPoolStart              :272,
    MmNonPagedPoolEnd                :280,
    MmPagedPoolStart                 :288,
    MmPagedPoolEnd                   :296,
    MmPagedPoolInformation           :304,
    MmPageSize                           :312,
    MmSizeOfPagedPoolInBytes         :320,
    MmTotalCommitLimit               :328,
    MmTotalCommittedPages            :336,
    MmSharedCommit                   :344,
    MmDriverCommit                   :352,
    MmProcessCommit                  :360,
    MmPagedPoolCommit                :368,
    MmExtendedCommit                 :376,
    MmZeroedPageListHead             :384,
    MmFreePageListHead               :392,
    MmStandbyPageListHead            :400,
    MmModifiedPageListHead           :408,
    MmModifiedNoWritePageListHead    :416,
    MmAvailablePages                 :424,
    MmResidentAvailablePages         :432,
    PoolTrackTable                   :440,
    NonPagedPoolDescriptor           :448,
    MmHighestUseress             :456,
    MmSystemRangeStart               :464,
    MmUserProbeess               :472,
    KdPrintCircularBuffer            :480,
    KdPrintCircularBufferEnd         :488,
    KdPrintWritePointer              :496,
    KdPrintRolloverCount             :504,
    MmLoadedUserImageList            :512,
    NtBuildLab                       :520,
    KiNormalSystemCall                   :528,
    KiProcessorBlock                 :536,
    MmUnloadedDrivers                :544,
    MmLastUnloadedDriver             :552,
    MmTriageActionTaken              :560,
    MmSpecialPoolTag                 :568,
    KernelVerifier                   :576,
    MmVerifierData                   :584,
    MmAllocatedNonPagedPool          :592,
    MmPeakCommitment                 :600,
    MmTotalCommitLimitMaximum        :608,
    CmNtCSDVersion                   :616,
    MmPhysicalMemoryBlock            :624,
    MmSessionBase                        :632,
    MmSessionSize                        :640,
    MmSystemParentTablePage              :648,
    MmVirtualTranslationBase             :656,
    OffsetKThreadNextProcessor           :664,
    OffsetKThreadTeb                     :666,
    OffsetKThreadKernelStack             :668,
    OffsetKThreadInitialStack            :670,
    OffsetKThreadApcProcess              :672,
    OffsetKThreadState                   :674,
    OffsetKThreadBStore                  :676,
    OffsetKThreadBStoreLimit             :678,
    SizeEProcess                         :680,
    OffsetEprocessPeb                    :682,
    OffsetEprocessParentCID              :684,
    OffsetEprocessDirectoryTableBase     :686,
    SizePrcb                             :688,
    OffsetPrcbDpcRoutine                 :690,
    OffsetPrcbCurrentThread              :692,
    OffsetPrcbMhz                        :694,
    OffsetPrcbCpuType                    :696,
    OffsetPrcbVendorString               :698,
    OffsetPrcbProcessorState             :700,
    OffsetPrcbNumber                     :702,
    SizeEThread                          :704,
    KdPrintCircularBufferPtr         :712,
    KdPrintBufferSize                :720,
    MmBadPagesDetected                   :800,
    EtwpDebuggerData                     :816,
    PteBase                              :864,

    PaeEnabled                        :100000,
    SharedUserData                    :100008,
    ProductType                       :100016,
    SuiteMask                         :100024,
    DumpWriterStatus                  :100032,
    DumpFormatVersion                 :100040,
    DumpWriterVersion                 :100048,
    DumpPowerState                    :100056,
    DumpMmStorage                     :100064,
    DumpAttributes                    :100072,
    PagingLevels                      :100080
};

// DEBUG_VALUE types.

exports.DEBUG_VALUE_INVALID      = 0;

exports.DEBUG_VALUE_INT8         = 1;

exports.DEBUG_VALUE_INT16        = 2;

exports.DEBUG_VALUE_INT32        = 3;

exports.DEBUG_VALUE_INT64        = 4;

exports.DEBUG_VALUE_FLOAT32      = 5;

exports.DEBUG_VALUE_FLOAT64      = 6;

exports.DEBUG_VALUE_FLOAT80      = 7;

exports.DEBUG_VALUE_FLOAT82      = 8;

exports.DEBUG_VALUE_FLOAT128     = 9;

exports.DEBUG_VALUE_VECTOR64     = 10;

exports.DEBUG_VALUE_VECTOR128    = 11;


exports.DEBUG_REGISTER_SUB_REGISTER  = 0x00000001;

//-----------------------------IDebugClient--------------------------------------------------

/**
 * get the exit code of the current process if that process has already run through to completion.
 * @returns {Number} exitCode
 */
function getExitCode()
{
    return binding.dbgeng.getExitCode();
}
exports.getExitCode = getExitCode;

/**
 * get a string describing the computer and user this client represents
 * @returns {String}
 */
function getIdentity()
{
    return binding.dbgeng.getIdentity();
}
exports.getIdentity = getIdentity;

/**
 * get a description of the process that includes the executable image name, the service names, the MTS package names, and the command line
 * @param {Number , String , Uint64} server
 * @param {Number} systemId
 * @param {Number} flags
 * @returns {Object}
 */
function getRunningProcessDescription(server , systemId , flags)
{
    let argServer = 0;

    if ( typing.isNumber(server) )
    {
        argServer = server;
    }
    else if ( typing.isString(server) )
    {
        argServer = server;
    }
    else
    {
        assert( Uint64.isUint64(server) );

        argServer = '0x' + server.toString(16);
    }

    assert( typing.isNumber(systemId) );

    assert( typing.isNumber(flags) );

    return binding.dbgeng.getRunningProcessDescription( argServer , systemId , flags );
}
exports.getRunningProcessDescription = getRunningProcessDescription;

/**
 * searches for a process with a given executable file name and return its process ID.
 * @param {Number , String , Uint64} server
 * @param {String} exeName
 * @param {Number} flags
 * @returns {Number}
 */
function getRunningProcessSystemIdByExecutableName(server , exeName , flags )
{
    let argServer = 0;

    if ( typing.isNumber(server) )
    {
        argServer = server;
    }
    else if ( typing.isString(server) )
    {
        argServer = server;
    }
    else
    {
        assert( Uint64.isUint64(server) );

        argServer = '0x' + server.toString(16);
    }

    assert( typing.isString(exeName) );

    assert( typing.isNumber(flags) );

    return binding.dbgeng.getRunningProcessSystemIdByExecutableName( argServer , exeName , flags);
}
exports.getRunningProcessSystemIdByExecutableName = getRunningProcessSystemIdByExecutableName;


/**
 * creates a user-mode or kernel-modecrash dump file
 * @param {String} filename
 * @param {Number} qualifier
 * @returns {Boolean}
 */
function writeDumpFile(filename , qualifier)
{
    assert( typing.isString(filename) );

    assert( typing.isNumber(qualifier) );

    return binding.dbgeng.writeDumpFile(filename , qualifier);
}
exports.writeDumpFile = writeDumpFile;

/**
 * checks whether kernel debugging is enabled for the local kernel.
 * @returns {Boolean}
 */
function isKernelDebuggerEnabled()
{
    return binding.dbgeng.isKernelDebuggerEnabled();
}
exports.isKernelDebuggerEnabled = isKernelDebuggerEnabled;





//------------  IDebugControl -----------------------------------

/**
 * assembles a single processor instruction
 * @param {Number,Uint64} offset
 * @param {String} instruction
 * @returns {Uint64} endOffset
 */
function assemble(offset , instruction  )
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    assert( typing.isString(instruction) );

    let endOffset = binding.dbgeng.assemble( argOffset , instruction);

    return new Uint64(endOffset);
}
exports.assemble = assemble;

/**
 * calls a debugger extension
 * @param {String} routine
 * @param {String} [cmdline]
 * @returns {String} extension output
 */
function callExtension(routine , cmdline )
{
    assert( typing.isString(routine) );

    return binding.dbgeng.callExtension(0 , routine , cmdline);
}
exports.callExtension = callExtension;

/**
 * disassembles a processor instruction in the target's memory.
 * @param {Number , String , Uint64} offset
 * @param {Number} [flags]
 * @returns {{endOffset: Uint64, text: String}}
 */
function disassemble(offset , flags)
{
    let argOffset = 0;

    let argFlags = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    if ( arguments.length >= 2 )
    {
        assert( typing.isNumber(flags) );

        argFlags = flags;
    }


    let info = binding.dbgeng.disassemble(argOffset, argFlags);

    return {
        'text' : info.text,
        'endOffset' : new Uint64(info.endOffset)
    }
}
exports.disassemble = disassemble;


/**
 * execute a command and return the output
 * @param {String} command
 * @param {{echo: Boolean, logged: Boolean , repeat: Boolean}} [options]
 * @returns {String}
 */
function execute(command , options)
{
    assert( typing.isString(command) && ( 0 !== command.length) );

    let argOptions = {
        'echo' : false ,
        'logged' : false,
        'repeat' : false
    };

    if ( arguments.length >= 2 )
    {
        assert( typing.isObject(options) );

        if ( options )
        {
            argOptions = options;
        }
    }

    return binding.dbgeng.execute(command , argOptions);
}
exports.execute = execute;

/**
 * returns the processor type of the physical processor of the computer that is running the target.
 * @returns {Number}
 */
function getActualProcessorType()
{
    return binding.dbgeng.getActualProcessorType();
}
exports.getActualProcessorType = getActualProcessorType;

/**
 * returns the current code level and is mainly used when stepping through code.
 * @returns {Number}
 */
function getCodeLevel()
{
    return binding.dbgeng.getCodeLevel();
}
exports.getCodeLevel = getCodeLevel;


/**
 *  describes the nature of the current target.
 * @returns {{type : Number , qualifier : Number }}
 */
function getDebuggeeType()
{
    return binding.dbgeng.getDebuggeeType();
}
exports.getDebuggeeType = getDebuggeeType;

/**
 * returns the effective processor type of the processor of the computer that is running the target.
 * @returns {Number}
 */
function getEffectiveProcessorType()
{
    return binding.dbgeng.getEffectiveProcessorType();
}
exports.getEffectiveProcessorType = getEffectiveProcessorType;

/**
 * returns the executing processor type for the processor for which the last event occurred.
 * @returns {Number}
 */
function getExecutingProcessorType()
{
    return binding.dbgeng.getExecutingProcessorType();
}
exports.getExecutingProcessorType = getExecutingProcessorType;


/**
 * returns information about the execution status of the debugger engine.
 * @returns {Number}
 */
function getExecutionStatus()
{
    return binding.dbgeng.getExecutionStatus();
}
exports.getExecutionStatus = getExecutionStatus;

/**
 * returns the location of a processor instruction relative to a given location.
 * @param {Number , String , Uint64} offset
 * @param {Number} [delta]
 * @returns {Uint64}
 */
function getNearInstruction(offset , delta)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }


    let argDelta = 0;

    if ( arguments.length >= 2)
    {
        assert( typing.isNumber(delta) );

        argDelta = delta;
    }

    let nearOffset = binding.dbgeng.getNearInstruction(argOffset , argDelta);

     return new Uint64(nearOffset);
}
exports.getNearInstruction = getNearInstruction;

/**
 * returns the number of processor types that are supported by the computer running the current target
 * @returns {Number}
 */
function getNumberPossibleExecutingProcessorTypes()
{
    return binding.dbgeng.getNumberPossibleExecutingProcessorTypes();
}
exports.getNumberPossibleExecutingProcessorTypes = getNumberPossibleExecutingProcessorTypes;

/**
 * returns the number of processors on the computer running the current target.
 * @returns {Number}
 */
function getNumberProcessors()
{
    return binding.dbgeng.getNumberProcessors();
}
exports.getNumberProcessors = getNumberProcessors;

/**
 * returns the number of processor types supported by the engine.
 * @returns {Number}
 */
function getNumberSupportedProcessorTypes()
{
    return binding.dbgeng.getNumberSupportedProcessorTypes();
}
exports.getNumberSupportedProcessorTypes = getNumberSupportedProcessorTypes;


/**
 * get the page size for the effective processor mode.
 * @returns {Number}
 */
function getPageSize()
{
    return binding.dbgeng.getPageSize();
}
exports.getPageSize = getPageSize;


/**
 * returns the full name and abbreviated name of the specified processor type.
 * @param {Number} type
 * @returns {{fullName:String , abbrevName:string}}
 */
function getProcessorTypeNames(type)
{
    assert( typing.isNumber(type) );

    return binding.dbgeng.getProcessorTypeNames(type);
}
exports.getProcessorTypeNames = getProcessorTypeNames;


/**
 * returns the return address for the current function
 * @returns {Uint64}
 */
function getReturnOffset()
{
    let offset = binding.dbgeng.getReturnOffset();

    return new Uint64(offset);
}
exports.getReturnOffset = getReturnOffset;

/**
 * returns the frames at the top of the specified call stack
 * @param {Number , String , Uint64} frameOffset
 * @param {Number , String , Uint64} stackOffset
 * @param {Number , String , Uint64} instructionOffset
 * @param {Number} depth
 * @returns {Array}
 */
function getStackTrace( frameOffset , stackOffset , instructionOffset , depth)
{
    let argFrameOffset = 0;

    let argStackOffset = 0;

    let argInstructionOffset = 0;

    // frameOffset
    if ( typing.isNumber(frameOffset) )
    {
        argFrameOffset = frameOffset;
    }
    else if ( typing.isString(frameOffset) )
    {
        argFrameOffset = frameOffset;
    }
    else
    {
        assert( Uint64.isUint64(frameOffset) );

        argFrameOffset = '0x' + frameOffset.toString(16);
    }

    // stackOffset
    if ( typing.isNumber(stackOffset) )
    {
        argStackOffset = stackOffset;
    }
    else if ( typing.isString(stackOffset) )
    {
        argStackOffset = stackOffset;
    }
    else
    {
        assert( Uint64.isUint64(stackOffset) );

        argStackOffset = '0x' + stackOffset.toString(16);
    }

    // instructionOffset
    if ( typing.isNumber(instructionOffset) )
    {
        argInstructionOffset = instructionOffset;
    }
    else if ( typing.isString(instructionOffset) )
    {
        argInstructionOffset = instructionOffset;
    }
    else
    {
        assert( Uint64.isUint64(instructionOffset) );

        argInstructionOffset = '0x' + instructionOffset.toString(16);
    }


    assert( typing.isNumber(depth) );


    let frameArray = binding.dbgeng.getStackTrace(
        argFrameOffset ,
        argStackOffset,
        argInstructionOffset,
        depth
    );

    let i = 0;

    let j = 0;

    for ( i = 0; i < frameArray.length; i++ )
    {
        frameArray[i].instructionOffset = new Uint64( frameArray[i].instructionOffset );

        frameArray[i].returnOffset = new Uint64( frameArray[i].returnOffset );

        frameArray[i].frameOffset = new Uint64( frameArray[i].frameOffset );

        frameArray[i].stackOffset = new Uint64( frameArray[i].stackOffset );

        frameArray[i].funcTableEntry = new Uint64( frameArray[i].funcTableEntry );

        for ( j = 0; j < 4; j++ )
        {
            frameArray[i].params[j] = new Uint64( frameArray[i].params[j] );
        }
    }

    return frameArray;
}
exports.getStackTrace = getStackTrace;


/**
 *  returns information that identifies the operating system on the computer that is running the current target.
 * @returns {Object}
 */
function getSystemVersion()
{
    return binding.dbgeng.getSystemVersion();
}
exports.getSystemVersion = getSystemVersion;

/**
 * determines if the effective processor uses 64-bit pointers
 * @returns {Boolean}
 */
function isPointer64Bit()
{
    return binding.dbgeng.isPointer64Bit();
}
exports.isPointer64Bit = isPointer64Bit;

/**
 * reads the kernel bug check code and related parameters
 * @returns {{args: Uint64[4], code : Number}}
 */
function readBugCheck()
{
    let info =  binding.dbgeng.readBugCheck();

    return {
        'code' : info.code ,
        'args' : [
            new Uint64( info.arg1) ,
            new Uint64( info.arg2) ,
            new Uint64( info.arg3) ,
            new Uint64( info.arg4)
        ]
    }
}
exports.readBugCheck = readBugCheck;

/**
 * sets the current code level and is mainly used when stepping through code.
 * @param {Number} level
 * @returns {Boolean}
 */
function setCodeLevel(level)
{
    assert( typing.isNumber(level) );

    return binding.dbgeng.setCodeLevel();
}
exports.setCodeLevel = setCodeLevel;

/**
 * sets the effective processor type of the processor of the computer that is running the target.
 * @param {Number} type
 * @returns {Boolean}
 */
function setEffectiveProcessorType(type)
{
    assert( typing.isNumber(type) );

    return binding.dbgeng.setEffectiveProcessorType();
}
exports.setEffectiveProcessorType = setEffectiveProcessorType;

/**
 * requests that the debugger engine enter an executable state
 * @param {Number} status
 * @returns {Boolean}
 */
function setExecutionStatus(status)
{
    assert( typing.isNumber(status) );

    return binding.dbgeng.setExecutionStatus();
}
exports.setExecutionStatus = setExecutionStatus;

//------------  IDebugDataSpaces -----------------------------------

/**
 * reads data from a system bus
 * @param {Number} busDataType
 * @param {Number} busNumber
 * @param {Number} slotNumber
 * @param {Number} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number} bytesRead
 */
function readBus(busDataType , busNumber , slotNumber , offset , buffer)
{
    assert( typing.isNumber(busDataType) );

    assert( typing.isNumber(busNumber) );

    assert( typing.isNumber(slotNumber) );

    assert( typing.isArrayBuffer(buffer) );

    return binding.dbgeng.readBus(busDataType , busNumber , slotNumber ,offset , buffer);
}
exports.readBus = readBus;


/**
 * reads implementation-specific system data
 * @param {Number} processor
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number} bytesRead
 */
function readControl(processor , offset , buffer)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    assert( typing.isNumber(processor) );

    assert( typing.isArrayBuffer(buffer) );

    return binding.dbgeng.readControl(processor , argOffset , buffer);
}
exports.readControl = readControl;


/**
 * returns information about the target that the debugger engine has queried or determined during the current session
 * @param {String} name
 * @param {ArrayBuffer} buffer
 * @returns {Number} DataSize
 */
function readDebugger( name , buffer )
{
    assert( typing.isString(name) );

    assert( typing.isArrayBuffer(buffer) );

    let index = debugDataIndices[name];

    if ( typing.isUndefined(index) )
    {
        throw new Error(fmt.sprintf('unknown debug data index for "%s"' , name));
    }

    return binding.dbgeng.readDebugger(index , buffer);
}
exports.readDebugger = readDebugger;

/**
 * reads from the system and bus I/O memory
 * @param {Number} interfaceType
 * @param {Number} busNumber
 * @param {Number} addressSpace
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number} bytesRead
 */
function readIo(interfaceType , busNumber , addressSpace , offset , buffer)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    assert( typing.isNumber(interfaceType) );

    assert( typing.isNumber(busNumber) );

    assert( typing.isNumber(addressSpace) );

    assert( Uint64.isUint64(offset) );

    assert( typing.isArrayBuffer(buffer) );

    return binding.dbgeng.readIo(
        interfaceType ,
        busNumber,
        addressSpace,
        argOffset,
        buffer
    );
}
exports.readIo = readIo;

/**
 * reads a specified Model-Specific Register (MSR)
 * @param {Number} address
 * @returns {Uint64} value
 */
function readMsr(address)
{
    let value = binding.dbgeng.readMsr(address);

    assert( typing.isNumber(address) );

    return new Uint64(value);
}
exports.readMsr = readMsr;

/**
 *  reads the target's memory from the specified physical address
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number} bytesRead
 */
function readPhysical(offset , buffer)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    assert( typing.isArrayBuffer(buffer) );

    return binding.dbgeng.readPhysical( argOffset , buffer);
}
exports.readPhysical = readPhysical;

/**
 * returns data about the specified processor
 * @param {Number} processor
 * @param {String} name
 * @param {ArrayBuffer} buffer
 * @returns {Number} bytesRead
 */
function readProcessor(processor , name  , buffer )
{
    assert( typing.isNumber(processor) );

    assert( typing.isString(name) );

    assert( typing.isArrayBuffer(buffer) );

    let index = 0;

    return binding.dbgeng.readProcessor(processor , index , buffer);
}
exports.readProcessor = readProcessor;

/**
 * reads memory from the target's virtual address spac
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number} bytesRead
 */
function readVirtual(offset , buffer)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) , fmt.sprintf('type is %s' , typeof offset) );

        argOffset = '0x' + offset.toString(16);
    }

    return binding.dbgeng.readVirtual( argOffset , buffer);
}
exports.readVirtual = readVirtual;

/**
 * searches the target's virtual memory for a specified pattern of bytes
 * @param {Number , String , Uint64} offset
 * @param {Number , String , Uint64} length
 * @param {ArrayBuffer} pattern
 * @param {Number} granularity
 * @returns {Uint64} matchOffset
 */
function searchVirtual(offset , length , pattern , granularity)
{
    let argOffset = 0;

    let argLength = 0;

    // offset
    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    // length
    if ( typing.isNumber(length) )
    {
        argLength = length;
    }
    else if ( typing.isString(length) )
    {
        argLength = length;
    }
    else
    {
        assert( Uint64.isUint64(length) );

        argLength = '0x' + length.toString(16);
    }

    assert( Uint64.isUint64(length) );

    assert( typing.isArrayBuffer(pattern) );

    assert( typing.isNumber(granularity) );

    let matchOffset = binding.dbgeng.searchVirtual(
        argOffset,
        argLength,
        pattern,
        granularity
    );

    return new Uint64(matchOffset);
}
exports.searchVirtual = searchVirtual;


/**
 * writes data to a system bus
 * @param {Number} busDataType
 * @param {Number} busNumber
 * @param {Number} slotNumber
 * @param {Number} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number} BytesWritten
 */
function writeBus(busDataType , busNumber , slotNumber , offset , buffer)
{
    return binding.dbgeng.writeBus(
        busDataType,
        busNumber,
        slotNumber,
        offset,
        buffer
    );
}
exports.writeBus = writeBus;

/**
 * writes implementation-specific system data
 * @param {Number} processor
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number}
 */
function writeControl(processor , offset , buffer)
{
    let argOffset = 0;

    // offset
    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    return binding.dbgeng.writeControl(
        processor ,
        argOffset,
        buffer
        );
}
exports.writeControl = writeControl;

/**
 * writes to the system and bus I/O memory
 * @param {Number} interfaceType
 * @param {Number} busNumber
 * @param {Number} addressSpace
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number}
 */
function writeIo(interfaceType , busNumber , addressSpace , offset , buffer)
{
    let argOffset = 0;

    // offset
    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    return binding.dbgeng.writeIo(
        interfaceType,
        busNumber,
        addressSpace,
        argOffset,
        buffer
    );
}
exports.writeIo = writeIo;


/**
 * writes a value to the specified Model-Specific Register (MSR)
 * @param {Number} address
 * @param {Number , String , Uint64} value
 * @returns {Boolean}
 */
function writeMsr(address , value)
{
     let argValue = 0;

    // value
    if ( typing.isNumber(value) )
    {
        argValue = value;
    }
    else if ( typing.isString(value) )
    {
        argValue = value;
    }
    else
    {
        assert( Uint64.isUint64(value) );

        argValue = '0x' + value.toString(16);
    }

    return binding.dbgeng.writeMsr( address , argValue);
}
exports.writeMsr = writeMsr;

/**
 *
 * @param {Number , String , Uint64} offset
 * @param {ArrayBuffer} buffer
 * @returns {Number}
 */
function writeVirtual(offset , buffer)
{
    let argOffset = 0;

    // offset
    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    return binding.dbgeng.writeVirtual( argOffset , buffer);
}
exports.writeVirtual = writeVirtual;



//------------------------IDebugRegisters--------------------------------------------

/**
 *
 * @param {Number} index
 * @returns {Object}
 */
function getRegisterDescription(index)
{
    let info = binding.dbgeng.getRegisterDescription(index);

    info.subregMask = new Uint64(info.subregMask);

    return info;
}
exports.getRegisterDescription = getRegisterDescription;

/**
 * returns the location of the stack frame for the current function
 * @returns {Uint64}
 */
function getFrameOffset()
{
    let offset = binding.dbgeng.getFrameOffset();

    return new Uint64(offset);
}
exports.getFrameOffset = getFrameOffset;

/**
 * returns the index of the named register
 * @param {String} name
 * @returns {Number}
 */
function getRegisterIndex(name)
{
    return binding.dbgeng.getRegisterIndex(name);
}
exports.getRegisterIndex = getRegisterIndex;

/**
 * returns the location of the current thread's current instruction
 * @returns {Uint64}
 */
function getInstructionOffset()
{
    let offset = binding.dbgeng.getInstructionOffset();

    return new Uint64(offset);
}
exports.getInstructionOffset = getInstructionOffset;

/**
 *  returns the number of registers on the target computer
 * @returns {Number}
 */
function getNumberRegisters()
{
    return binding.dbgeng.getNumberRegisters();
}
exports.getNumberRegisters = getNumberRegisters;

/**
 * returns the current thread's current stack location.
 * @returns {Uint64}
 */
function getStackOffset()
{
    let offset = binding.dbgeng.getStackOffset();

    return new Uint64(offset);
}
exports.getStackOffset = getStackOffset;

/**
 * gets the value of one of the target's registers
 * @param  {Number} index
 * @returns {Object}
 */
function getRegisterValue(index)
{
    let info = binding.dbgeng.getRegisterValue(index);

    let value = 0;

    if ( exports.DEBUG_VALUE_INT8 === info.type )
    {
        assert( typing.isNumber(info.value) );

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_INT16 === info.type )
    {
        assert( typing.isNumber(info.value) );

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_INT32 === info.type )
    {
        assert( typing.isNumber(info.value) );

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_INT64 === info.type )
    {
        assert( typing.isString(info.value)  );

        value = new Uint64( info.value);
    }
    else if ( exports.DEBUG_VALUE_FLOAT32 === info.type )
    {
        assert( typing.isNumber(info.value) );

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_FLOAT64 === info.type )
    {
        assert( typing.isUint8Array(info.value) );

        assert( 8 === info.value.length);

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_FLOAT80 === info.type )
    {
        assert( typing.isUint8Array(info.value) );

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_FLOAT128 === info.type )
    {
        assert( typing.isUint8Array(info.value) );

        assert( 16 === info.value.length);

        value = info.value;
    }
    else if ( exports.DEBUG_VALUE_VECTOR64 === info.type )
    {
        assert( typing.isUint8Array(info.value) );

        assert( 8 === info.value.length);

        value = info.value;
    }
      else if ( exports.DEBUG_VALUE_VECTOR128 === info.type )
    {
        assert( typing.isUint8Array(info.value) );

        assert( 16 === info.value.length);

        value = info.value;
    }
    else
    {
        throw new Error(fmt.sprintf('not supported type %d' , info.type) );
    }

    return value;
}
exports.getRegisterValue = getRegisterValue;

/**
 *
 * @param {Number} index
 * @param {Number} type
 * @param {Number , String , Uint64} value
 * @returns {Boolean}
 */
function setRegisterValue(index , type ,  value)
{
    let argValue = 0;


    if ( exports.DEBUG_VALUE_INT8 === type )
    {
        assert( typing.isNumber(value) );

        argValue = value;
    }
    else if ( exports.DEBUG_VALUE_INT16 === type )
    {
        assert( typing.isNumber(value) );

        argValue = value;
    }
    else if ( exports.DEBUG_VALUE_INT32 === type )
    {
        assert( typing.isNumber(value) );

        argValue = value;
    }
    else if ( exports.DEBUG_VALUE_INT64 === type )
    {
        if ( typing.isNumber(value) )
        {
            argValue = value;
        }
        else if ( typing.isString(value) )
        {
            argValue = value;
        }
        else
        {
            assert( Uint64.isUint64(value)  );

            argValue = '0x' + value.toString(16);
        }
    }
    else if ( exports.DEBUG_VALUE_FLOAT32 === type )
    {
        assert( typing.isNumber(value) );

        argValue = value;
    }
    else if ( exports.DEBUG_VALUE_FLOAT64 === type )
    {
        if ( typing.isNumber(value) )
        {
            argValue = value;
        }
        else
        {
            assert( typing.isUint8Array(value) );

            assert( 64 === value.length);

            argValue = value;
        }
    }
    else if ( exports.DEBUG_VALUE_FLOAT80 === type )
    {
        assert( typing.isUint8Array(value) );

        assert( 80 === value.length);

        argValue = value;
    }
    else if ( exports.DEBUG_VALUE_FLOAT128 === type )
    {
        assert( typing.isUint8Array(value) );

        argValue = value;
    }
    else
    {
        throw new Error(fmt.sprintf('not supported type %d' , type) );
    }

    return binding.dbgeng.setRegisterValue(index , type , argValue);
}
exports.setRegisterValue = setRegisterValue;


//------------------------IDebugSymbols--------------------------------------------

/**
 * returns the offset of a field from the base address of an instance of a type.
 * @param {Number , String , Uint64} imageBase
 * @param {Number} typeId
 * @param {String} field
 * @returns {Number}
 */
function getFieldOffset(imageBase , typeId , field ,)
{
    let argModuleBase = 0;

    if ( typing.isNumber(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else if ( typing.isString(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else
    {
        assert( Uint64.isUint64(imageBase) );

        argModuleBase = '0x' + imageBase.toString(16);
    }

    return binding.dbgeng.getFieldOffset( argModuleBase , typeId , field);
}
exports.getFieldOffset = getFieldOffset;

/**
 * returns the location of the module with the specified index.
 * @param {Number} index
 * @returns {Uint64}
 */
function getModuleByIndex(index)
{
    assert( typing.isNumber(index) );

    let value = binding.dbgeng.getModuleByIndex(index);

    return new Uint64(value);
}
exports.getModuleByIndex = getModuleByIndex;

/**
 * searches through the target's modules for one with the specified name.
 * @param {String} name
 * @param {Number} [startIndex]
 * @returns {{index: Number , base: Uint64}}
 */
function getModuleByName(name , startIndex= 0)
{
    let argStartIndex = 0;

    if ( arguments.length >= 2)
    {
        assert( typing.isNumber(startIndex)  );

        argStartIndex = startIndex;
    }

    let info = binding.dbgeng.getModuleByName( name , argStartIndex);

    info.imageBase = new Uint64(info.imageBase);

    return info;
}
exports.getModuleByName = getModuleByName;

/**
 * searches through the target's modules for one whose memory allocation includes the specified location.
 * @param offset
 * @param startIndex
 * @returns {{index: Number , base: Uint64}}
 */
function getModuleByOffset(offset , startIndex)
{
    let argOffset = 0;

    let argStartIndex = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    if ( arguments.length >= 2)
    {
        assert( typing.isNumber(startIndex)  );

        argStartIndex = startIndex;
    }

    let info =  binding.dbgeng.getModuleByOffset( argOffset , argStartIndex );

    info.imageBase = new Uint64(info.imageBase);

    return info;
}
exports.getModuleByOffset = getModuleByOffset;

/**
 * returns the names of the specified module.
 * @param {Number} index
 * @param {Number , String , Uint64} base
 * @returns {{imageName:String , moduleName:String , loadedImageName:String}}
 */
function getModuleNames(index , base)
{
    let argBase = 0;

    if ( typing.isNumber(base) )
    {
        argBase = base;
    }
    else if ( typing.isString(base) )
    {
        argBase = base;
    }
    else
    {
        assert( Uint64.isUint64(base) );

        argBase = '0x' + base.toString(16);
    }

    return binding.dbgeng.getModuleNames(index , argBase);
}
exports.getModuleNames = getModuleNames;

/**
 * returns parameters for modules in the target.
 * @param {Number} index
 * @returns {Object}
 */
function getModuleParameters(index)
{
    assert( typing.isNumber(index) );

    let info = binding.dbgeng.getModuleParameters(index);

    info.imageBase = new Uint64(info.imageBase);

    return info;
}
exports.getModuleParameters = getModuleParameters;

/**
 * returns the name of the symbol at the specified location in the target's virtual address space.
 * @param {Number , String , Uint64} offset
 * @returns {{name:String , displacement: Uint64}}
 */
function getNameByOffset(offset)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    let info = binding.dbgeng.getNameByOffset(argOffset);

    info.displacement = new Uint64( info.displacement );

    if ( info.displacement.isZero() )
    {
        return info.name;
    }

    return fmt.sprintf('%s+%X' , info.name , info.displacement);
}
exports.getNameByOffset = getNameByOffset;

/**
 * returns the name of a symbol that is located near the specified location.
 * @param {Number , String , Uint64} offset
 * @param {Number} [delta]
 * @returns {{name:String , displacement: Uint64}}
 */
function getNearNameByOffset(offset , delta)
{
    let argOffset = 0;

    let argDelta = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    if ( arguments.length >= 2 )
    {
        assert( typing.isNumber(delta) );

        argDelta = delta;
    }

    let info = binding.dbgeng.getNearNameByOffset(argOffset , argDelta);

    info.displacement = new Uint64( info.displacement );

    return info;
}
exports.getNearNameByOffset = getNearNameByOffset;

/**
 * returns the number of modules in the current process's module list.
 * @returns {{loaded:Number , unloaded:Number}}
 */
function getNumberModules()
{
    return binding.dbgeng.getNumberModules();
}
exports.getNumberModules = getNumberModules;


/***
 * returns the location of a symbol identified by name.
 * @param {String} name
 * @returns {Uint64}
 */
function getOffsetByName(name)
{
    assert( typing.isString(name) );

    let offset = binding.dbgeng.getOffsetByName(name);

    return new Uint64(offset);
}
exports.getOffsetByName = getOffsetByName;

/**
 * returns the type ID of the symbol closest to the specified memory location.
 * @param {Number , String , Uint64} offset
 * @returns {{typeId : Number , moduleBae: Uint64} }
 */
function getOffsetTypeId(offset)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    let info = binding.dbgeng.getOffsetTypeId(argOffset);

    info.imageBase =  new Uint64(info.imageBase);

    return info;
}
exports.getOffsetTypeId = getOffsetTypeId;

/**
 * returns the base address of module which contains the specified symbol.
 * @param {String} name
 * @returns {Uint64}
 */
function getSymbolModule(name )
{
    assert( typing.isString(name) );

    let imageBase = binding.dbgeng.getSymbolModule(name);

    return new Uint64(imageBase);
}
exports.getSymbolModule = getSymbolModule;


/**
 * returns the symbol path
 * @returns {String}
 */
function getSymbolPath()
{
    return binding.dbgeng.getSymbolPath();
}
exports.getSymbolPath = getSymbolPath;


/**
 * returns the type ID and module of the specified symbol.
 * @param {String} name
 * @returns {{typeId: Number , imageBase: Uint64}}
 */
function getSymbolTypeId(name)
{
    assert( typing.isString(name) );

    let info = binding.dbgeng.getSymbolTypeId(name);

    info.imageBase = new Uint64( info.imageBase );

    return info;
}
exports.getSymbolTypeId = getSymbolTypeId;

/**
 *  looks up the specified type and return its type ID.
 * @param {Number , String , Uint64} imageBase
 * @param {String} name
 * @returns {Number}
 */
function getTypeId(imageBase , name)
{
    let argModuleBase = 0;

    if ( typing.isNumber(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else if ( typing.isString(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else
    {
        assert( Uint64.isUint64(imageBase) );

        argModuleBase = '0x' + imageBase.toString(16);
    }

    assert( typing.isString(name) );

    return binding.dbgeng.getTypeId(argModuleBase , name);
}
exports.getTypeId = getTypeId;


/**
 * returns the name of the type symbol specified by its type ID and module.
 * @param {Number , String , Uint64} imageBase
 * @param {Number} typeId
 * @returns {String}
 */
function getTypeName(imageBase , typeId )
{
    let argModuleBase = 0;

    if ( typing.isNumber(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else if ( typing.isString(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else
    {
        assert( Uint64.isUint64(imageBase) );

        argModuleBase = '0x' + imageBase.toString(16);
    }


    assert( typing.isNumber(typeId) );

    return binding.dbgeng.getTypeName(argModuleBase , typeId);
}
exports.getTypeName = getTypeName;

/**
 * returns the number of bytes of memory an instance of the specified type requires.
 * @param {Number , String , Uint64} imageBase
 * @param {Number} typeId
 * @returns {Number}
 */
function getTypeSize(imageBase , typeId)
{
    let argModuleBase = 0;

    if ( typing.isNumber(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else if ( typing.isString(imageBase) )
    {
        argModuleBase = imageBase;
    }
    else
    {
        assert( Uint64.isUint64(imageBase) );

        argModuleBase = '0x' + imageBase.toString(16);
    }

    assert( typing.isNumber(typeId) );

    return binding.dbgeng.getTypeSize(argModuleBase , typeId);
}
exports.getTypeSize = getTypeSize;

/**
 * deletes the engine's symbol information for the specified module and reload these symbols as needed.
 * @param {String} name
 * @returns {Boolean}
 */
function reload(name)
{
    assert( typing.isString(name) );

    return binding.dbgeng.reload(name);
}
exports.reload = reload;

/**
 * sets the symbol path.
 * @param {String} symbolPath
 * @returns {Boolean}
 */
function setSymbolPath(symbolPath)
{
    return binding.dbgeng.setSymbolPath(symbolPath);
}
exports.setSymbolPath = setSymbolPath;

//------------------------IDebugSystemObjects--------------------------------------------

/**
 * returns the location of the system data structure describing the current process.
 * @returns {Uint64}
 */
function getCurrentProcessDataOffset()
{
    let offset = binding.dbgeng.getCurrentProcessDataOffset();

    return new Uint64(Uint64);
}
exports.getCurrentProcessDataOffset = getCurrentProcessDataOffset;

/**
 * returns the engine process ID for the current process.
 * @returns {*}
 */
function getCurrentProcessId()
{
    return binding.dbgeng.getCurrentProcessId();
}
exports.getCurrentProcessId = getCurrentProcessId;

/**
 * returns the process environment block (PEB) of the current process.
 * @returns {Uint64}
 */
function getCurrentProcessPeb()
{
    let peb = binding.dbgeng.getCurrentProcessPeb();

    return new Uint64(peb);
}
exports.getCurrentProcessPeb = getCurrentProcessPeb;

/**
 * returns the system process ID of the current process.
 * @returns {Number}
 */
function getCurrentProcessSystemId()
{
    return binding.dbgeng.getCurrentProcessSystemId();
}
exports.getCurrentProcessSystemId = getCurrentProcessSystemId;

/**
 * returns the location of the system data structure for the current thread.
 * @returns {Uint64}
 */
function getCurrentThreadDataOffset()
{
    let offset = binding.dbgeng.getCurrentThreadDataOffset();

    return new Uint64(offset);
}
exports.getCurrentThreadDataOffset = getCurrentThreadDataOffset;

/**
 * returns the engine thread ID for the current thread.
 * @returns {Number}
 */
function getCurrentThreadId()
{
    return binding.dbgeng.getCurrentThreadId();
}
exports.getCurrentThreadId = getCurrentThreadId;

/**
 * returns the system thread ID of the current thread.
 * @returns {Number}
 */
function getCurrentThreadSystemId()
{
    return binding.dbgeng.getCurrentThreadSystemId();
}
exports.getCurrentThreadSystemId = getCurrentThreadSystemId;

/**
 * returns the location of the thread environment block (TEB) for the current thread.
 * @returns {Uint64}
 */
function getCurrentThreadTeb()
{
    let offset = binding.dbgeng.getCurrentThreadTeb();

    return new Uint64(offset);
}
exports.getCurrentThreadTeb = getCurrentThreadTeb;


/**
 *
 * @param {Number} id   processor id
 * @returns {Number}
 */
function getThreadIdByProcessor(id)
{
    return binding.dbgeng.getThreadIdByProcessor(id);
}
exports.getThreadIdByProcessor = getThreadIdByProcessor;


function setCurrentThreadId(id)
{
    return binding.dbgeng.setCurrentThreadId(id);
}
exports.setCurrentThreadId = setCurrentThreadId;

//------------------------ for IDebugSystemObject2--------------------------------------------


function getImplicitProcessDataOffset()
{
    let offset = binding.dbgeng.getImplicitProcessDataOffset();

    return new Uint64(offset);
}
exports.getImplicitProcessDataOffset = getImplicitProcessDataOffset;


function getImplicitThreadDataOffset()
{
    let offset = binding.dbgeng.getImplicitThreadDataOffset();

    return new Uint64(offset);
}
exports.getImplicitThreadDataOffset = getImplicitThreadDataOffset;


function setImplicitProcessDataOffset(offset)
{
    let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }


    return binding.dbgeng.setImplicitProcessDataOffset(argOffset);
}
exports.setImplicitProcessDataOffset = setImplicitProcessDataOffset;


function setImplicitThreadDataOffset()
{
     let argOffset = 0;

    if ( typing.isNumber(offset) )
    {
        argOffset = offset;
    }
    else if ( typing.isString(offset) )
    {
        argOffset = offset;
    }
    else
    {
        assert( Uint64.isUint64(offset) );

        argOffset = '0x' + offset.toString(16);
    }

    return  binding.dbgeng.setImplicitThreadDataOffset(argOffset);
}
exports.setImplicitThreadDataOffset = setImplicitThreadDataOffset;
