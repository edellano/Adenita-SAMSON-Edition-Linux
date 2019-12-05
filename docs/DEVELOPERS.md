# CMake

## Requirements:

- Qt 5.9.3
- CMake
- Boost library
- Rapidjson
- SAMSON SDK 0.8.5

# CMake Command

To create the developing environment use CMake:

```
mkdir build
cd build
cmake -DSAMSON_SDK_PATH="path/to/SAMSON/SDK/0.8.5" -DQT5_CMAKE_INCLUDE_DIR="path/to/Qt/5.9.3/msvc2017_64/lib" -DBOOST_PATH="path/to/boost_1_69_0" -DRAPIDJSON_PATH="path/to/rapidjson" ..
```
For debugging it is necessary to add: `-DDEBUG="ON"`.

Build command, i.e:

```
cmake --build /path/to/build --config [Debug|Release] --target install -- -j 10
```
