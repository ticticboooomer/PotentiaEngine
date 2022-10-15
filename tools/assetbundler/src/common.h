#pragma once
#include <map>
#include <string>
#include <utility>
#include <vector>

enum BundleType {
  Animation,
  Mesh,
  Audio,
  Materials,
  Textures
};

typedef std::pair<std::string, std::string> BundleRecord;
typedef std::vector<BundleRecord> PreBundle;
typedef std::vector<std::pair<BundleType, BundleRecord>> TaggedBundleSegment;


std::string MakeResourceKey(std::string path);
void Log(const std::string& log);
