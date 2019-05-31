#pragma once
#include "InferenceEngine.h"

class truthtable : public InferenceEngine {
public:
	truthtable(string path);
	~truthtable();
};

