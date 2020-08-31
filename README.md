# Fall 2020 PA 01 - Sentiment Analysis

## Important Information

Project handout:  [Click Here](https://smucse2341.github.io/cs2341-f2020/projects/pa01/)

## Input and Output Files

As you begin using input files and output files with this project, 
you'll need to modify the `CMakeLists.txt` file and the `.github/workflows/build.yaml`
files.  

Place any input files in the folder that contains your source code.  When your project is built, it will be copied into the build directory by CMake. 

- `CMakeLists.txt`
    - Open it and look for the commented section (with `#` signs).  Edit the `set(input01 "")` etc.
    based upon how many files you need.
    - there should be one `set(...)` statement per input file
    - you DO NOT need to list output files in `CmakeLists.txt`.
    
- `.github/workflows/build.yaml`
    - Open this file and look for the `INPUT_FILES:` command near the top.
    - List the input file names in the order they should be sent to argv of main. 
    - OUTPUT file need to be listed here as well in the `OUTPUT_FILES:` section. 
    - For example:
        ```yaml
        INPUT_FILES: IMDB.csv
        OUTPUT_FILES: output.txt
        ```
      would be equivalent to the following execution command:
      ```yaml
      ./executableName IMDB.csv output.txt
      ```   
    
