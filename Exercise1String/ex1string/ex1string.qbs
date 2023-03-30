import qbs

CppApplication {
    consoleApplication: true
    install: true
    files: [
        "main.cpp",
        "methods.cpp",
        "methods.h",
    ]
}
