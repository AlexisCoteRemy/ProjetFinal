#pragma once

#include "button.h"

class SaveLoad
{
public:
	SaveLoad();
	~SaveLoad();

private:
	Button _backButton;
	Button _quitter;
	Button _save;
	Button _load;
};