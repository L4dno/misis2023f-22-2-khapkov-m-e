:: вставьте путь до файла vcpkg.cmake после знака '='
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=
cmake --build build --config release

:: вставьте относительный путь до желаемой директории для установки приложения вместо ./CW
cmake --install ./build --prefix ./CW