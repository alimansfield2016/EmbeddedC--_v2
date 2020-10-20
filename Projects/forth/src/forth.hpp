#pragma once

#include <stdint.h>
#include "include.hpp"

namespace Forth
{
	extern int32_t stack[256];
	extern int8_t sp;

	void parse(const char *buf);

	inline void CR() { Serial.PrintLn(); }

} // namespace Forth
