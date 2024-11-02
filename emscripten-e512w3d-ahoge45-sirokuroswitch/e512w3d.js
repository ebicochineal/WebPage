var Module=typeof Module!="undefined"?Module:{};var moduleOverrides=Object.assign({},Module);var arguments_=[];var thisProgram="./this.program";var quit_=(status,toThrow)=>{throw toThrow};var ENVIRONMENT_IS_WEB=typeof window=="object";var ENVIRONMENT_IS_WORKER=typeof importScripts=="function";var ENVIRONMENT_IS_NODE=typeof process=="object"&&typeof process.versions=="object"&&typeof process.versions.node=="string";var scriptDirectory="";function locateFile(path){if(Module["locateFile"]){return Module["locateFile"](path,scriptDirectory)}return scriptDirectory+path}var read_,readAsync,readBinary,setWindowTitle;function logExceptionOnExit(e){if(e instanceof ExitStatus)return;let toLog=e;err("exiting due to exception: "+toLog)}if(ENVIRONMENT_IS_NODE){if(ENVIRONMENT_IS_WORKER){scriptDirectory=require("path").dirname(scriptDirectory)+"/"}else{scriptDirectory=__dirname+"/"}var fs,nodePath;if(typeof require==="function"){fs=require("fs");nodePath=require("path")}read_=(filename,binary)=>{filename=nodePath["normalize"](filename);return fs.readFileSync(filename,binary?undefined:"utf8")};readBinary=filename=>{var ret=read_(filename,true);if(!ret.buffer){ret=new Uint8Array(ret)}return ret};readAsync=(filename,onload,onerror)=>{filename=nodePath["normalize"](filename);fs.readFile(filename,function(err,data){if(err)onerror(err);else onload(data.buffer)})};if(process["argv"].length>1){thisProgram=process["argv"][1].replace(/\\/g,"/")}arguments_=process["argv"].slice(2);if(typeof module!="undefined"){module["exports"]=Module}process["on"]("uncaughtException",function(ex){if(!(ex instanceof ExitStatus)){throw ex}});process["on"]("unhandledRejection",function(reason){throw reason});quit_=(status,toThrow)=>{if(keepRuntimeAlive()){process["exitCode"]=status;throw toThrow}logExceptionOnExit(toThrow);process["exit"](status)};Module["inspect"]=function(){return"[Emscripten Module object]"}}else if(ENVIRONMENT_IS_WEB||ENVIRONMENT_IS_WORKER){if(ENVIRONMENT_IS_WORKER){scriptDirectory=self.location.href}else if(typeof document!="undefined"&&document.currentScript){scriptDirectory=document.currentScript.src}if(scriptDirectory.indexOf("blob:")!==0){scriptDirectory=scriptDirectory.substr(0,scriptDirectory.replace(/[?#].*/,"").lastIndexOf("/")+1)}else{scriptDirectory=""}{read_=url=>{var xhr=new XMLHttpRequest;xhr.open("GET",url,false);xhr.send(null);return xhr.responseText};if(ENVIRONMENT_IS_WORKER){readBinary=url=>{var xhr=new XMLHttpRequest;xhr.open("GET",url,false);xhr.responseType="arraybuffer";xhr.send(null);return new Uint8Array(xhr.response)}}readAsync=(url,onload,onerror)=>{var xhr=new XMLHttpRequest;xhr.open("GET",url,true);xhr.responseType="arraybuffer";xhr.onload=()=>{if(xhr.status==200||xhr.status==0&&xhr.response){onload(xhr.response);return}onerror()};xhr.onerror=onerror;xhr.send(null)}}setWindowTitle=title=>document.title=title}else{}var out=Module["print"]||console.log.bind(console);var err=Module["printErr"]||console.warn.bind(console);Object.assign(Module,moduleOverrides);moduleOverrides=null;if(Module["arguments"])arguments_=Module["arguments"];if(Module["thisProgram"])thisProgram=Module["thisProgram"];if(Module["quit"])quit_=Module["quit"];var POINTER_SIZE=4;var wasmBinary;if(Module["wasmBinary"])wasmBinary=Module["wasmBinary"];var noExitRuntime=Module["noExitRuntime"]||true;if(typeof WebAssembly!="object"){abort("no native wasm support detected")}var wasmMemory;var ABORT=false;var EXITSTATUS;function assert(condition,text){if(!condition){abort(text)}}var UTF8Decoder=typeof TextDecoder!="undefined"?new TextDecoder("utf8"):undefined;function UTF8ArrayToString(heapOrArray,idx,maxBytesToRead){var endIdx=idx+maxBytesToRead;var endPtr=idx;while(heapOrArray[endPtr]&&!(endPtr>=endIdx))++endPtr;if(endPtr-idx>16&&heapOrArray.buffer&&UTF8Decoder){return UTF8Decoder.decode(heapOrArray.subarray(idx,endPtr))}var str="";while(idx<endPtr){var u0=heapOrArray[idx++];if(!(u0&128)){str+=String.fromCharCode(u0);continue}var u1=heapOrArray[idx++]&63;if((u0&224)==192){str+=String.fromCharCode((u0&31)<<6|u1);continue}var u2=heapOrArray[idx++]&63;if((u0&240)==224){u0=(u0&15)<<12|u1<<6|u2}else{u0=(u0&7)<<18|u1<<12|u2<<6|heapOrArray[idx++]&63}if(u0<65536){str+=String.fromCharCode(u0)}else{var ch=u0-65536;str+=String.fromCharCode(55296|ch>>10,56320|ch&1023)}}return str}function UTF8ToString(ptr,maxBytesToRead){return ptr?UTF8ArrayToString(HEAPU8,ptr,maxBytesToRead):""}function stringToUTF8Array(str,heap,outIdx,maxBytesToWrite){if(!(maxBytesToWrite>0))return 0;var startIdx=outIdx;var endIdx=outIdx+maxBytesToWrite-1;for(var i=0;i<str.length;++i){var u=str.charCodeAt(i);if(u>=55296&&u<=57343){var u1=str.charCodeAt(++i);u=65536+((u&1023)<<10)|u1&1023}if(u<=127){if(outIdx>=endIdx)break;heap[outIdx++]=u}else if(u<=2047){if(outIdx+1>=endIdx)break;heap[outIdx++]=192|u>>6;heap[outIdx++]=128|u&63}else if(u<=65535){if(outIdx+2>=endIdx)break;heap[outIdx++]=224|u>>12;heap[outIdx++]=128|u>>6&63;heap[outIdx++]=128|u&63}else{if(outIdx+3>=endIdx)break;heap[outIdx++]=240|u>>18;heap[outIdx++]=128|u>>12&63;heap[outIdx++]=128|u>>6&63;heap[outIdx++]=128|u&63}}heap[outIdx]=0;return outIdx-startIdx}function stringToUTF8(str,outPtr,maxBytesToWrite){return stringToUTF8Array(str,HEAPU8,outPtr,maxBytesToWrite)}var buffer,HEAP8,HEAPU8,HEAP16,HEAPU16,HEAP32,HEAPU32,HEAPF32,HEAPF64;function updateGlobalBufferAndViews(buf){buffer=buf;Module["HEAP8"]=HEAP8=new Int8Array(buf);Module["HEAP16"]=HEAP16=new Int16Array(buf);Module["HEAP32"]=HEAP32=new Int32Array(buf);Module["HEAPU8"]=HEAPU8=new Uint8Array(buf);Module["HEAPU16"]=HEAPU16=new Uint16Array(buf);Module["HEAPU32"]=HEAPU32=new Uint32Array(buf);Module["HEAPF32"]=HEAPF32=new Float32Array(buf);Module["HEAPF64"]=HEAPF64=new Float64Array(buf)}var INITIAL_MEMORY=Module["INITIAL_MEMORY"]||16777216;var wasmTable;var __ATPRERUN__=[];var __ATINIT__=[];var __ATMAIN__=[];var __ATPOSTRUN__=[];var runtimeInitialized=false;function keepRuntimeAlive(){return noExitRuntime}function preRun(){if(Module["preRun"]){if(typeof Module["preRun"]=="function")Module["preRun"]=[Module["preRun"]];while(Module["preRun"].length){addOnPreRun(Module["preRun"].shift())}}callRuntimeCallbacks(__ATPRERUN__)}function initRuntime(){runtimeInitialized=true;callRuntimeCallbacks(__ATINIT__)}function preMain(){callRuntimeCallbacks(__ATMAIN__)}function postRun(){if(Module["postRun"]){if(typeof Module["postRun"]=="function")Module["postRun"]=[Module["postRun"]];while(Module["postRun"].length){addOnPostRun(Module["postRun"].shift())}}callRuntimeCallbacks(__ATPOSTRUN__)}function addOnPreRun(cb){__ATPRERUN__.unshift(cb)}function addOnInit(cb){__ATINIT__.unshift(cb)}function addOnPostRun(cb){__ATPOSTRUN__.unshift(cb)}var runDependencies=0;var runDependencyWatcher=null;var dependenciesFulfilled=null;function addRunDependency(id){runDependencies++;if(Module["monitorRunDependencies"]){Module["monitorRunDependencies"](runDependencies)}}function removeRunDependency(id){runDependencies--;if(Module["monitorRunDependencies"]){Module["monitorRunDependencies"](runDependencies)}if(runDependencies==0){if(runDependencyWatcher!==null){clearInterval(runDependencyWatcher);runDependencyWatcher=null}if(dependenciesFulfilled){var callback=dependenciesFulfilled;dependenciesFulfilled=null;callback()}}}function abort(what){if(Module["onAbort"]){Module["onAbort"](what)}what="Aborted("+what+")";err(what);ABORT=true;EXITSTATUS=1;what+=". Build with -sASSERTIONS for more info.";var e=new WebAssembly.RuntimeError(what);throw e}var dataURIPrefix="data:application/octet-stream;base64,";function isDataURI(filename){return filename.startsWith(dataURIPrefix)}function isFileURI(filename){return filename.startsWith("file://")}var wasmBinaryFile;wasmBinaryFile="e512w3d.wasm";if(!isDataURI(wasmBinaryFile)){wasmBinaryFile=locateFile(wasmBinaryFile)}function getBinary(file){try{if(file==wasmBinaryFile&&wasmBinary){return new Uint8Array(wasmBinary)}if(readBinary){return readBinary(file)}throw"both async and sync fetching of the wasm failed"}catch(err){abort(err)}}function getBinaryPromise(){if(!wasmBinary&&(ENVIRONMENT_IS_WEB||ENVIRONMENT_IS_WORKER)){if(typeof fetch=="function"&&!isFileURI(wasmBinaryFile)){return fetch(wasmBinaryFile,{credentials:"same-origin"}).then(function(response){if(!response["ok"]){throw"failed to load wasm binary file at '"+wasmBinaryFile+"'"}return response["arrayBuffer"]()}).catch(function(){return getBinary(wasmBinaryFile)})}else{if(readAsync){return new Promise(function(resolve,reject){readAsync(wasmBinaryFile,function(response){resolve(new Uint8Array(response))},reject)})}}}return Promise.resolve().then(function(){return getBinary(wasmBinaryFile)})}function createWasm(){var info={"env":asmLibraryArg,"wasi_snapshot_preview1":asmLibraryArg};function receiveInstance(instance,module){var exports=instance.exports;exports=Asyncify.instrumentWasmExports(exports);Module["asm"]=exports;wasmMemory=Module["asm"]["memory"];updateGlobalBufferAndViews(wasmMemory.buffer);wasmTable=Module["asm"]["__indirect_function_table"];addOnInit(Module["asm"]["__wasm_call_ctors"]);removeRunDependency("wasm-instantiate")}addRunDependency("wasm-instantiate");function receiveInstantiationResult(result){receiveInstance(result["instance"])}function instantiateArrayBuffer(receiver){return getBinaryPromise().then(function(binary){return WebAssembly.instantiate(binary,info)}).then(function(instance){return instance}).then(receiver,function(reason){err("failed to asynchronously prepare wasm: "+reason);abort(reason)})}function instantiateAsync(){if(!wasmBinary&&typeof WebAssembly.instantiateStreaming=="function"&&!isDataURI(wasmBinaryFile)&&!isFileURI(wasmBinaryFile)&&!ENVIRONMENT_IS_NODE&&typeof fetch=="function"){return fetch(wasmBinaryFile,{credentials:"same-origin"}).then(function(response){var result=WebAssembly.instantiateStreaming(response,info);return result.then(receiveInstantiationResult,function(reason){err("wasm streaming compile failed: "+reason);err("falling back to ArrayBuffer instantiation");return instantiateArrayBuffer(receiveInstantiationResult)})})}else{return instantiateArrayBuffer(receiveInstantiationResult)}}if(Module["instantiateWasm"]){try{var exports=Module["instantiateWasm"](info,receiveInstance);exports=Asyncify.instrumentWasmExports(exports);return exports}catch(e){err("Module.instantiateWasm callback failed with error: "+e);return false}}instantiateAsync();return{}}var tempDouble;var tempI64;var ASM_CONSTS={42815:()=>{e512w3d_mouse_l=false;e512w3d_mouse_m=false;e512w3d_mouse_r=false;e512w3d_mouse_position_x=0;e512w3d_mouse_position_y=0;e512w3d_buff=null;e512w3d_canvas=null;e512w3d_ctx=null;e512w3d_keys=Array(128);window.addEventListener("mousemove",e=>{var rect=e512w3d_canvas.getBoundingClientRect();e512w3d_mouse_position_x=(e.clientX-rect.left)/parseFloat(e512w3d_canvas.style.width)*e512w3d_canvas.width;e512w3d_mouse_position_y=(e.clientY-rect.top)/parseFloat(e512w3d_canvas.style.height)*e512w3d_canvas.height});window.addEventListener("mousedown",e=>{if(e.button==0){e512w3d_mouse_l=true}if(e.button==1){e512w3d_mouse_m=true}if(e.button==2){e512w3d_mouse_r=true}});window.addEventListener("mouseup",e=>{if(e.button==0){e512w3d_mouse_l=false}if(e.button==1){e512w3d_mouse_m=false}if(e.button==2){e512w3d_mouse_r=false}});window.addEventListener("mouseleave",e=>{if(e.button==0){e512w3d_mouse_l=false}if(e.button==1){e512w3d_mouse_m=false}if(e.button==2){e512w3d_mouse_r=false}});window.addEventListener("touchstart",e=>{e512w3d_mouse_l=true;var x=0;var y=0;if(e.touches&&e.touches[0]){x=e.touches[0].clientX;y=e.touches[0].clientY}else if(e.clientX&&e.clientY){x=e.clientX;y=e.clientY}else{return}var rect=e512w3d_canvas.getBoundingClientRect();e512w3d_mouse_position_x=(x-rect.left)/parseFloat(e512w3d_canvas.style.width)*e512w3d_canvas.width;e512w3d_mouse_position_y=(y-rect.top)/parseFloat(e512w3d_canvas.style.height)*e512w3d_canvas.height});window.addEventListener("touchmove",e=>{e512w3d_mouse_l=true;var x=0;var y=0;if(e.touches&&e.touches[0]){x=e.touches[0].clientX;y=e.touches[0].clientY}else if(e.clientX&&e.clientY){x=e.clientX;y=e.clientY}else{return}var rect=e512w3d_canvas.getBoundingClientRect();e512w3d_mouse_position_x=(x-rect.left)/parseFloat(e512w3d_canvas.style.width)*e512w3d_canvas.width;e512w3d_mouse_position_y=(y-rect.top)/parseFloat(e512w3d_canvas.style.height)*e512w3d_canvas.height});window.addEventListener("touchend",e=>{e512w3d_mouse_l=false});window.addEventListener("keydown",e=>{if(e.isComposing||e.keyCode>=128){return}e512w3d_keys[e.keyCode]=true});window.addEventListener("keyup",e=>{if(e.isComposing||e.keyCode>=128){return}e512w3d_keys[e.keyCode]=false})},45371:()=>{return e512w3d_mouse_position_x},45403:()=>{return e512w3d_mouse_position_y},45435:()=>{return e512w3d_mouse_l},45458:()=>{return e512w3d_mouse_m},45481:()=>{return e512w3d_mouse_r}};function CanvasSetup(width,height){e512w3d_canvas=document.getElementById("e512w3d-canvas");e512w3d_ctx=e512w3d_canvas.getContext("2d");e512w3d_buff=e512w3d_ctx.createImageData(width,height);e512w3d_canvas.width=width;e512w3d_canvas.height=height;e512w3d_canvas.addEventListener("mousemove",e=>{var rect=e.target.getBoundingClientRect();e512w3d_mouse_position_x=(e.clientX-rect.left)/parseFloat(e512w3d_canvas.style.width)*e512w3d_canvas.width;e512w3d_mouse_position_y=(e.clientY-rect.top)/parseFloat(e512w3d_canvas.style.height)*e512w3d_canvas.height})}function CanvasPut(x,y,r,g,b){var p=(y*e512w3d_canvas.width+x)*4;e512w3d_buff.data[p]=r;e512w3d_buff.data[p+1]=g;e512w3d_buff.data[p+2]=b;e512w3d_buff.data[p+3]=255}function CanvasPush(){e512w3d_ctx.putImageData(e512w3d_buff,0,0)}function GetKey(n){return e512w3d_keys[n]}function readHTMLTextAreaJS(textareaid,text){var d=document.getElementById(UTF8ToString(textareaid));if(d===null){return}var e512w3d_textarea_value=d.value.replace("\r","");var l=Math.min(e512w3d_textarea_value.length+1,4194304);stringToUTF8(e512w3d_textarea_value,text,l)}function writeHTMLTextAreaJS(textareaid,text){var d=document.getElementById(UTF8ToString(textareaid));if(d===null){return}d.value=UTF8ToString(text)}function ExitStatus(status){this.name="ExitStatus";this.message="Program terminated with exit("+status+")";this.status=status}function callRuntimeCallbacks(callbacks){while(callbacks.length>0){callbacks.shift()(Module)}}var nowIsMonotonic=true;function __emscripten_get_now_is_monotonic(){return nowIsMonotonic}function _abort(){abort("")}var readAsmConstArgsArray=[];function readAsmConstArgs(sigPtr,buf){readAsmConstArgsArray.length=0;var ch;buf>>=2;while(ch=HEAPU8[sigPtr++]){buf+=ch!=105&buf;readAsmConstArgsArray.push(ch==105?HEAP32[buf]:HEAPF64[buf++>>1]);++buf}return readAsmConstArgsArray}function _emscripten_asm_const_int(code,sigPtr,argbuf){var args=readAsmConstArgs(sigPtr,argbuf);return ASM_CONSTS[code].apply(null,args)}function _emscripten_date_now(){return Date.now()}var _emscripten_get_now;if(ENVIRONMENT_IS_NODE){_emscripten_get_now=()=>{var t=process["hrtime"]();return t[0]*1e3+t[1]/1e6}}else _emscripten_get_now=()=>performance.now();function _emscripten_memcpy_big(dest,src,num){HEAPU8.copyWithin(dest,src,src+num)}function abortOnCannotGrowMemory(requestedSize){abort("OOM")}function _emscripten_resize_heap(requestedSize){var oldSize=HEAPU8.length;requestedSize=requestedSize>>>0;abortOnCannotGrowMemory(requestedSize)}function handleException(e){if(e instanceof ExitStatus||e=="unwind"){return EXITSTATUS}quit_(1,e)}function callUserCallback(func){if(ABORT){return}try{func()}catch(e){handleException(e)}}function safeSetTimeout(func,timeout){return setTimeout(function(){callUserCallback(func)},timeout)}function _emscripten_sleep(ms){return Asyncify.handleSleep(wakeUp=>safeSetTimeout(wakeUp,ms))}var SYSCALLS={varargs:undefined,get:function(){SYSCALLS.varargs+=4;var ret=HEAP32[SYSCALLS.varargs-4>>2];return ret},getStr:function(ptr){var ret=UTF8ToString(ptr);return ret}};function _proc_exit(code){EXITSTATUS=code;if(!keepRuntimeAlive()){if(Module["onExit"])Module["onExit"](code);ABORT=true}quit_(code,new ExitStatus(code))}function exitJS(status,implicit){EXITSTATUS=status;_proc_exit(status)}function runAndAbortIfError(func){try{return func()}catch(e){abort(e)}}var Asyncify={instrumentWasmImports:function(imports){var ASYNCIFY_IMPORTS=["env.invoke_*","env.emscripten_sleep","env.emscripten_wget","env.emscripten_wget_data","env.emscripten_idb_load","env.emscripten_idb_store","env.emscripten_idb_delete","env.emscripten_idb_exists","env.emscripten_idb_load_blob","env.emscripten_idb_store_blob","env.SDL_Delay","env.emscripten_scan_registers","env.emscripten_lazy_load_code","env.emscripten_fiber_swap","wasi_snapshot_preview1.fd_sync","env.__wasi_fd_sync","env._emval_await","env._dlopen_js","env.__asyncjs__*"].map(x=>x.split(".")[1]);for(var x in imports){(function(x){var original=imports[x];var sig=original.sig;if(typeof original=="function"){var isAsyncifyImport=ASYNCIFY_IMPORTS.indexOf(x)>=0||x.startsWith("__asyncjs__")}})(x)}},instrumentWasmExports:function(exports){var ret={};for(var x in exports){(function(x){var original=exports[x];if(typeof original=="function"){ret[x]=function(){Asyncify.exportCallStack.push(x);try{return original.apply(null,arguments)}finally{if(!ABORT){var y=Asyncify.exportCallStack.pop();assert(y===x);Asyncify.maybeStopUnwind()}}}}else{ret[x]=original}})(x)}return ret},State:{Normal:0,Unwinding:1,Rewinding:2,Disabled:3},state:0,StackSize:4096,currData:null,handleSleepReturnValue:0,exportCallStack:[],callStackNameToId:{},callStackIdToName:{},callStackId:0,asyncPromiseHandlers:null,sleepCallbacks:[],getCallStackId:function(funcName){var id=Asyncify.callStackNameToId[funcName];if(id===undefined){id=Asyncify.callStackId++;Asyncify.callStackNameToId[funcName]=id;Asyncify.callStackIdToName[id]=funcName}return id},maybeStopUnwind:function(){if(Asyncify.currData&&Asyncify.state===Asyncify.State.Unwinding&&Asyncify.exportCallStack.length===0){Asyncify.state=Asyncify.State.Normal;runAndAbortIfError(_asyncify_stop_unwind);if(typeof Fibers!="undefined"){Fibers.trampoline()}}},whenDone:function(){return new Promise((resolve,reject)=>{Asyncify.asyncPromiseHandlers={resolve:resolve,reject:reject}})},allocateData:function(){var ptr=_malloc(12+Asyncify.StackSize);Asyncify.setDataHeader(ptr,ptr+12,Asyncify.StackSize);Asyncify.setDataRewindFunc(ptr);return ptr},setDataHeader:function(ptr,stack,stackSize){HEAP32[ptr>>2]=stack;HEAP32[ptr+4>>2]=stack+stackSize},setDataRewindFunc:function(ptr){var bottomOfCallStack=Asyncify.exportCallStack[0];var rewindId=Asyncify.getCallStackId(bottomOfCallStack);HEAP32[ptr+8>>2]=rewindId},getDataRewindFunc:function(ptr){var id=HEAP32[ptr+8>>2];var name=Asyncify.callStackIdToName[id];var func=Module["asm"][name];return func},doRewind:function(ptr){var start=Asyncify.getDataRewindFunc(ptr);return start()},handleSleep:function(startAsync){if(ABORT)return;if(Asyncify.state===Asyncify.State.Normal){var reachedCallback=false;var reachedAfterCallback=false;startAsync(handleSleepReturnValue=>{if(ABORT)return;Asyncify.handleSleepReturnValue=handleSleepReturnValue||0;reachedCallback=true;if(!reachedAfterCallback){return}Asyncify.state=Asyncify.State.Rewinding;runAndAbortIfError(()=>_asyncify_start_rewind(Asyncify.currData));if(typeof Browser!="undefined"&&Browser.mainLoop.func){Browser.mainLoop.resume()}var asyncWasmReturnValue,isError=false;try{asyncWasmReturnValue=Asyncify.doRewind(Asyncify.currData)}catch(err){asyncWasmReturnValue=err;isError=true}var handled=false;if(!Asyncify.currData){var asyncPromiseHandlers=Asyncify.asyncPromiseHandlers;if(asyncPromiseHandlers){Asyncify.asyncPromiseHandlers=null;(isError?asyncPromiseHandlers.reject:asyncPromiseHandlers.resolve)(asyncWasmReturnValue);handled=true}}if(isError&&!handled){throw asyncWasmReturnValue}});reachedAfterCallback=true;if(!reachedCallback){Asyncify.state=Asyncify.State.Unwinding;Asyncify.currData=Asyncify.allocateData();if(typeof Browser!="undefined"&&Browser.mainLoop.func){Browser.mainLoop.pause()}runAndAbortIfError(()=>_asyncify_start_unwind(Asyncify.currData))}}else if(Asyncify.state===Asyncify.State.Rewinding){Asyncify.state=Asyncify.State.Normal;runAndAbortIfError(_asyncify_stop_rewind);_free(Asyncify.currData);Asyncify.currData=null;Asyncify.sleepCallbacks.forEach(func=>callUserCallback(func))}else{abort("invalid state: "+Asyncify.state)}return Asyncify.handleSleepReturnValue},handleAsync:function(startAsync){return Asyncify.handleSleep(wakeUp=>{startAsync().then(wakeUp)})}};var asmLibraryArg={"CanvasPush":CanvasPush,"CanvasPut":CanvasPut,"CanvasSetup":CanvasSetup,"GetKey":GetKey,"_emscripten_get_now_is_monotonic":__emscripten_get_now_is_monotonic,"abort":_abort,"emscripten_asm_const_int":_emscripten_asm_const_int,"emscripten_date_now":_emscripten_date_now,"emscripten_get_now":_emscripten_get_now,"emscripten_memcpy_big":_emscripten_memcpy_big,"emscripten_resize_heap":_emscripten_resize_heap,"emscripten_sleep":_emscripten_sleep,"readHTMLTextAreaJS":readHTMLTextAreaJS,"writeHTMLTextAreaJS":writeHTMLTextAreaJS};var asm=createWasm();var ___wasm_call_ctors=Module["___wasm_call_ctors"]=function(){return(___wasm_call_ctors=Module["___wasm_call_ctors"]=Module["asm"]["__wasm_call_ctors"]).apply(null,arguments)};var _main=Module["_main"]=function(){return(_main=Module["_main"]=Module["asm"]["main"]).apply(null,arguments)};var ___errno_location=Module["___errno_location"]=function(){return(___errno_location=Module["___errno_location"]=Module["asm"]["__errno_location"]).apply(null,arguments)};var _malloc=Module["_malloc"]=function(){return(_malloc=Module["_malloc"]=Module["asm"]["malloc"]).apply(null,arguments)};var _free=Module["_free"]=function(){return(_free=Module["_free"]=Module["asm"]["free"]).apply(null,arguments)};var _emscripten_stack_set_limits=Module["_emscripten_stack_set_limits"]=function(){return(_emscripten_stack_set_limits=Module["_emscripten_stack_set_limits"]=Module["asm"]["emscripten_stack_set_limits"]).apply(null,arguments)};var _emscripten_stack_get_base=Module["_emscripten_stack_get_base"]=function(){return(_emscripten_stack_get_base=Module["_emscripten_stack_get_base"]=Module["asm"]["emscripten_stack_get_base"]).apply(null,arguments)};var _emscripten_stack_get_end=Module["_emscripten_stack_get_end"]=function(){return(_emscripten_stack_get_end=Module["_emscripten_stack_get_end"]=Module["asm"]["emscripten_stack_get_end"]).apply(null,arguments)};var stackSave=Module["stackSave"]=function(){return(stackSave=Module["stackSave"]=Module["asm"]["stackSave"]).apply(null,arguments)};var stackRestore=Module["stackRestore"]=function(){return(stackRestore=Module["stackRestore"]=Module["asm"]["stackRestore"]).apply(null,arguments)};var stackAlloc=Module["stackAlloc"]=function(){return(stackAlloc=Module["stackAlloc"]=Module["asm"]["stackAlloc"]).apply(null,arguments)};var dynCall_vi=Module["dynCall_vi"]=function(){return(dynCall_vi=Module["dynCall_vi"]=Module["asm"]["dynCall_vi"]).apply(null,arguments)};var dynCall_iii=Module["dynCall_iii"]=function(){return(dynCall_iii=Module["dynCall_iii"]=Module["asm"]["dynCall_iii"]).apply(null,arguments)};var dynCall_iiiii=Module["dynCall_iiiii"]=function(){return(dynCall_iiiii=Module["dynCall_iiiii"]=Module["asm"]["dynCall_iiiii"]).apply(null,arguments)};var dynCall_iiii=Module["dynCall_iiii"]=function(){return(dynCall_iiii=Module["dynCall_iiii"]=Module["asm"]["dynCall_iiii"]).apply(null,arguments)};var dynCall_ii=Module["dynCall_ii"]=function(){return(dynCall_ii=Module["dynCall_ii"]=Module["asm"]["dynCall_ii"]).apply(null,arguments)};var dynCall_viiiiii=Module["dynCall_viiiiii"]=function(){return(dynCall_viiiiii=Module["dynCall_viiiiii"]=Module["asm"]["dynCall_viiiiii"]).apply(null,arguments)};var dynCall_viiiii=Module["dynCall_viiiii"]=function(){return(dynCall_viiiii=Module["dynCall_viiiii"]=Module["asm"]["dynCall_viiiii"]).apply(null,arguments)};var dynCall_viiii=Module["dynCall_viiii"]=function(){return(dynCall_viiii=Module["dynCall_viiii"]=Module["asm"]["dynCall_viiii"]).apply(null,arguments)};var _asyncify_start_unwind=Module["_asyncify_start_unwind"]=function(){return(_asyncify_start_unwind=Module["_asyncify_start_unwind"]=Module["asm"]["asyncify_start_unwind"]).apply(null,arguments)};var _asyncify_stop_unwind=Module["_asyncify_stop_unwind"]=function(){return(_asyncify_stop_unwind=Module["_asyncify_stop_unwind"]=Module["asm"]["asyncify_stop_unwind"]).apply(null,arguments)};var _asyncify_start_rewind=Module["_asyncify_start_rewind"]=function(){return(_asyncify_start_rewind=Module["_asyncify_start_rewind"]=Module["asm"]["asyncify_start_rewind"]).apply(null,arguments)};var _asyncify_stop_rewind=Module["_asyncify_stop_rewind"]=function(){return(_asyncify_stop_rewind=Module["_asyncify_stop_rewind"]=Module["asm"]["asyncify_stop_rewind"]).apply(null,arguments)};var ___start_em_js=Module["___start_em_js"]=41468;var ___stop_em_js=Module["___stop_em_js"]=42815;var calledRun;dependenciesFulfilled=function runCaller(){if(!calledRun)run();if(!calledRun)dependenciesFulfilled=runCaller};function callMain(args){var entryFunction=Module["_main"];var argc=0;var argv=0;try{var ret=entryFunction(argc,argv);exitJS(ret,true);return ret}catch(e){return handleException(e)}}function run(args){args=args||arguments_;if(runDependencies>0){return}preRun();if(runDependencies>0){return}function doRun(){if(calledRun)return;calledRun=true;Module["calledRun"]=true;if(ABORT)return;initRuntime();preMain();if(Module["onRuntimeInitialized"])Module["onRuntimeInitialized"]();if(shouldRunNow)callMain(args);postRun()}if(Module["setStatus"]){Module["setStatus"]("Running...");setTimeout(function(){setTimeout(function(){Module["setStatus"]("")},1);doRun()},1)}else{doRun()}}if(Module["preInit"]){if(typeof Module["preInit"]=="function")Module["preInit"]=[Module["preInit"]];while(Module["preInit"].length>0){Module["preInit"].pop()()}}var shouldRunNow=true;if(Module["noInitialRun"])shouldRunNow=false;run();
