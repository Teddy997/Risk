// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//These two lines to fix an error with the input procedure
//" not enough actual parameters for macro 'min' " 
#define NOMINMAX
#include <windows.h>

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "Player.h"
#include "Country.h"
#include "Deck.h"
#include "CardCashing.h"
#include "Combat.h"
#include "InputProcedure.h"
#include "SaveLoadManager.h"
#include "MapTester.h"
#include "GameState.h"
#include "MapObserver.h"
#include "observer.h"
#include "subject.h"
#include "playerView.h"

#include <ctime>
#include <sstream>

// TODO: reference additional headers your program requires here
