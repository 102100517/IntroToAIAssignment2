#pragma once
#include "InferenceEngine.h"

class truthtable : public InferenceEngine {
private:
		truthValue solve(argument* arg);
public:
	truthtable(string path);
	~truthtable();
	void execute();
};

