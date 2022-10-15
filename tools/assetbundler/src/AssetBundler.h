#pragma once

#include <memory>
#include <string>
#include <vector>
#include "common.h"
#include "processor/AssetFileProcessor.h"

class AssetBundler {
  public:
    void Setup();
    void Run();
    void Output();
    void SetDirectory(std::string dir) { m_directory = dir; };
    void SetOutputs(std::vector<std::string> includes) { m_includes = includes; };
  protected:
  void populate_bundle(TaggedBundleSegment* segment);
  std::string m_directory;
    bool m_isDryRun;
    bool m_isCompressed;
    PreBundle m_bundles;
    std::vector<std::shared_ptr<AssetFileProcessor>> m_agents;
    std::vector<std::string> m_includes;
};
