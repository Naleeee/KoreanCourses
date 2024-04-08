clang-tidy `find . -type f -iname *.cpp -not -path "./build/*" -not -path "./CMakeFiles/*"` --config-file=.clang-tidy -p build
