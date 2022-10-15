#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Option.hpp>

void sub_generate(CLI::App *subcmd) {
  CLI::Option *output = subcmd->add_option(
      "-o,--output", "Directory to output the generated code.");
  CLI::Option *input = subcmd->add_option(
      "-i,--input",
      "Directory containing source code to run the generator against");
  CLI::Option *entrypoint = subcmd->add_option(
      "-E,--entrypoint",
      "name of your 'init' function wshich defines the intitial scene used.");
}

int main(int argc, char **argv) {
  CLI::App app{"Code Gen Tool for Potentia Engine"};
  app.require_subcommand(1);

  sub_generate(app.add_subcommand("gen", "Generates the code."));

  CLI11_PARSE(app, argc, argv);
}
