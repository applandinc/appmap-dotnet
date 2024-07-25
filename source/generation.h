#pragma once

#include "metadata.h"
#include "recorder.h"

namespace appmap {
    std::string generate(const recording& events, const metadata& metadata = {});
}
