# Get all .cpp and .h files in the project directory
$files = Get-ChildItem -Path . -Include "*.cpp", "*.h" -Recurse

# Apply clang-format to each file
foreach ($file in $files) {
    $filePath = $file.FullName

    # Run clang-format on the file
    & clang-format -i $filePath

    Write-Host "Formatted file: $filePath"
}

Write-Host "Clang-format applied to all files."