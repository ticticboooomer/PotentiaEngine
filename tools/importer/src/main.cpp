#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
    CLI::App app{"Mesh file importer for Potentia Engine"};

    CLI::App* sub = app.add_subcommand("mesh", "Imports a 3D mesh file into the engine format(s).");

    CLI11_PARSE(app, argc, argv);
}