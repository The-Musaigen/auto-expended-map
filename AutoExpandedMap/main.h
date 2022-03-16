#ifndef MAIN_H_
#define MAIN_H_

// winsdk
#include <process.h>

// local
#include "memwrapper/memwrapper.h"

namespace {
constexpr auto kSwitchToNewScreen = 0x577244;
constexpr auto kMapZoom           = 0xBA67AC;
constexpr auto kMovMinimalZoom    = 0x5779FA;
constexpr char kMapPage           = '\005';

using switch_to_new_screen_t = void(__thiscall*)(void*, char);

template<typename T>
using hook_t = memwrapper::memhook<T>;

template<typename T>
using hook_smart_t = std::unique_ptr<hook_t<T>>;
}   // namespace

#endif   // !MAIN_H_
