#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
    CLI::App app{"Mesh file importer for Potentia Engine"};


    CLI11_PARSE(app, argc, argv);
}