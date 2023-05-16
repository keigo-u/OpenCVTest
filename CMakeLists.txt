cmake_minimum_required(VERSION 2.8.3)
project(step1)
# set(SOURCE_FILE ./src/matching.cpp)

# OpenCVのビルド環境の設定ファイルを読み込む
find_package(OpenCV REQUIRED)

# OpenCV関係のインクルードディレクトリのパスを設定
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

# 実行ファイル名を設定
# add_executable(main
#     ${SOURCE_FILE}
# )

# リンクするライブラリを読み込む
# target_link_libraries(main
#     ${OpenCV_LIBRARIES}
# )

# makeテンプレート
# add_executable(実行ファイル名 ./src/ファイル名.cpp)
# target_link_libraries(実行ファイル名 ${OpenCV_LIBRARIES})

# matching
add_executable(match ./src/matching.cpp)
target_link_libraries(match ${OpenCV_LIBRARIES})