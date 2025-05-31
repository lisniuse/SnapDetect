# build.ps1
$vsDevCmdPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

if (-Not (Test-Path $vsDevCmdPath)) {
    Write-Error "VS Developer Command Prompt not found: $vsDevCmdPath"
    exit 1
}

# Source code file
$srcFile = "src\main.cpp"

# Include paths
$include1 = "vector\opencv\build\include"
$include2 = "vector\opencv\build\include\opencv2"

# Output executable path
$outputExe = "bin\SnapDetect.exe"

# Clean and create bin directory
$binDir = Split-Path $outputExe -Parent
if (Test-Path $binDir) {
    # Clean files in bin directory instead of removing the directory
    Get-ChildItem $binDir -File | Remove-Item -Force -ErrorAction SilentlyContinue
    Write-Host "Cleaned files in bin directory"
} else {
    New-Item -ItemType Directory -Path $binDir -Force | Out-Null
    Write-Host "Created bin directory: $binDir"
}

# OpenCV library file path
$opencvLib = "vector\opencv\build\x64\vc16\lib\opencv_world4110.lib"

# OpenCV DLL path
$opencvDll = "vector\opencv\build\x64\vc16\bin\opencv_world4110.dll"

# Build complete command - add Windows system libraries and intermediate file output directory
$compileCmd = "cl.exe `"$srcFile`" /I `"$include1`" /I `"$include2`" /EHsc /MD /Zi /Od /Fe`"$outputExe`" /Fo`"$binDir\main.obj`" /Fd`"$binDir\vc140.pdb`" /link `"$opencvLib`" gdi32.lib user32.lib"

# Call VS Developer Command Prompt and execute compilation
$result = cmd.exe /c "`"$vsDevCmdPath`" -arch=x64 && $compileCmd"
Write-Host $result

# After successful compilation, copy OpenCV DLL file
if ($LASTEXITCODE -eq 0) {
    if (Test-Path $opencvDll) {
        Copy-Item $opencvDll $binDir -Force
        Write-Host "OpenCV DLL copied to output directory"
    } else {
        Write-Warning "OpenCV DLL file not found: $opencvDll"
    }
} else {
    Write-Error "Compilation failed"
}
