import qbs

CppApplication {
    consoleApplication: true
    install: true
    files: [
        "encryption.cpp",
        "encryption.h",
        "main.cpp",
        "menu.cpp",
        "menu.h",
        "user.cpp",
        "user.h",
        "utils.cpp",
        "utils.h",
    ]
}
