#include "AssetBundler.h"
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>

#include <CLI/Option.hpp>
#include <memory>
#include <vector>
#include <string>

void sc_bundle(CLI::App *sc_app);
void sc_codegen(CLI::App *sc_app);

int main(int argc, char **argv) {
  CLI::App app{"Asset Bundling utility for the Potentia Game Engine"};
  app.require_subcommand(1);

  auto bundle_command = app.add_subcommand(
      "bundle", "Create directory of bundles ready to loaded into the engine.");
  auto codegen_command =
      app.add_subcommand("codegen", "Generates header files containing "
                                    "resource key macros for accessing assets");

  if (app.got_subcommand(bundle_command)) {
    sc_bundle(bundle_command);
  } else if (app.got_subcommand(codegen_command)) {
    sc_codegen(codegen_command);
  }

  CLI11_PARSE(app, argc, argv);
  return 0;
}

void sc_bundle(CLI::App *sc_app) {
  CLI::Option *f_dryRun = sc_app->add_flag(
      "-d,--dry-run",
      "Performs a validation dry run to make sure things work.");
  CLI::Option *o_bundleTypes =
      sc_app
          ->add_option("-T,--types",
                       "the different types of assets that need to bundled.")
          ->multi_option_policy(CLI::MultiOptionPolicy::TakeAll);
  
  std::string directory;
  CLI::Option *o_directory =
      sc_app->add_option("directory", "The directory containing all assets");
  
  sc_app->callback([&]() {
    auto bundler = std::make_shared<AssetBundler>();
    bundler->SetDirectory(directory);
    bundler->Setup();
    bundler->Run();
    bundler->Output(); 
  });
}

void sc_codegen(CLI::App *sc_app) {}
