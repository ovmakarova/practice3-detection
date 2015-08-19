# Create a python file with hard-coded paths to the OpenCV binaries location and root project dir.

set(deps_py_file ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/deps.py)
file(WRITE ${deps_py_file} "# Here the paths to OpenCV binaries and to the root project folder are defined.\n")
list(GET OpenCV_LIB_DIR 0 OpenCV_FIRST_LIB_DIR)
file(APPEND ${deps_py_file} "opencv_bin_dir = '${OpenCV_FIRST_LIB_DIR}/../bin'\n")
file(APPEND ${deps_py_file} "project_root_dir = '${CMAKE_SOURCE_DIR}'\n")

# Copy python script to build/bin directory.
file(COPY ${CMAKE_SOURCE_DIR}/scripts/train_cascade_detector.py DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
