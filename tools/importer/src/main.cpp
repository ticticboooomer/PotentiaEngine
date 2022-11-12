#include "handler/mesh_handler.h"
#include "handler_manager.h"
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <memory>
#include <string>
#include <vector>

std::shared_ptr<handler_manager> get_handler_manager();

int main(int argc, char **argv) {
  CLI::App app{"Mesh file importer for Potentia Engine"};
  auto manager = get_handler_manager();

  auto all = manager->get_all();
  for (const auto &handler : all) {
    auto subcommand = handler->get_sub_command();
    CLI::App *subcommand_app = app.add_subcommand(
        subcommand, "Imports files of the " + subcommand + " type");
    std::string path;
    subcommand_app->add_option("-f", path, "Path of the file to import");
    subcommand_app->callback([&]() { handler->process("untitled.obj"); });
  }

  CLI11_PARSE(app, argc, argv);
}

std::shared_ptr<handler_manager> get_handler_manager() {
  auto manager = std::make_shared<handler_manager>();
  manager->register_handler(std::make_shared<mesh_handler>());
  return manager;
}
