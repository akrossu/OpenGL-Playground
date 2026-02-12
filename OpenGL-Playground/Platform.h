#pragma once

struct WindowHints {
	int majorVersion = 3;
	int minorVersion = 3;
	bool coreProfile = true;
	bool forwardCompatible = false; // MacOS compat
};