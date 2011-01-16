# -*- coding: iso-8859-1 -*-
# -*-python-*-

import os

from ctypes import *

try:
  if os.name == 'posix':
    library = CDLL("./libclient.so")
  elif os.name == 'nt':
    library = CDLL("./client.dll")
  else:
    raise Exception("Unrecognized OS: "+os.name)
except OSError:
  raise Exception("It looks like you didn't build libclient. Run 'make' and try again.")

# commands

library.createConnection.restype = c_void_p
library.createConnection.argtypes = []

library.serverLogin.restype = c_int
library.serverLogin.argtypes = [c_void_p, c_char_p, c_char_p]

library.createGame.restype = c_int
library.createGame.argtypes = [c_void_p]

library.joinGame.restype = c_int
library.joinGame.argtypes = [c_void_p, c_int]

library.endTurn.restype = None
library.endTurn.argtypes = [c_void_p]

library.getStatus.restype = None
library.getStatus.argtypes = [c_void_p]

library.networkLoop.restype = c_int
library.networkLoop.argtypes = [c_void_p]

#Functions
library.unitTalk.restype = c_int
library.unitTalk.argtypes = [c_void_p, c_char_p]

library.botTalk.restype = c_int
library.botTalk.argtypes = [c_void_p, c_char_p]

library.botMove.restype = c_int
library.botMove.argtypes = [c_void_p, c_char_p]

library.botAttack.restype = c_int
library.botAttack.argtypes = [c_void_p, c_void_p]

library.botHeal.restype = c_int
library.botHeal.argtypes = [c_void_p, c_void_p]

library.botBuild.restype = c_int
library.botBuild.argtypes = [c_void_p, c_void_p, c_int, c_int, c_int]

library.botCombine.restype = c_int
library.botCombine.argtypes = [c_void_p, c_void_p, c_void_p, c_void_p]

library.botSplit.restype = c_int
library.botSplit.argtypes = [c_void_p]

library.frameTalk.restype = c_int
library.frameTalk.argtypes = [c_void_p, c_char_p]

library.wallTalk.restype = c_int
library.wallTalk.argtypes = [c_void_p, c_char_p]

# accessors

#Globals 
library.getTurnNumber.restype = c_int
library.getTurnNumber.argtypes = [c_void_p]

library.getPlayerID.restype = c_int
library.getPlayerID.argtypes = [c_void_p]

library.getBoardX.restype = c_int
library.getBoardX.argtypes = [c_void_p]

library.getBoardY.restype = c_int
library.getBoardY.argtypes = [c_void_p]

library.getGameNumber.restype = c_int
library.getGameNumber.argtypes = [c_void_p]

library.getPlayer0Time.restype = c_int
library.getPlayer0Time.argtypes = [c_void_p]

library.getPlayer1Time.restype = c_int
library.getPlayer1Time.argtypes = [c_void_p]

library.getBot.restype = c_void_p
library.getBot.argtypes = [c_void_p, c_int]

library.getBotCount.restype = c_int
library.getBotCount.argtypes = [c_void_p]

library.getFrame.restype = c_void_p
library.getFrame.argtypes = [c_void_p, c_int]

library.getFrameCount.restype = c_int
library.getFrameCount.argtypes = [c_void_p]

library.getWall.restype = c_void_p
library.getWall.argtypes = [c_void_p, c_int]

library.getWallCount.restype = c_int
library.getWallCount.argtypes = [c_void_p]

library.getType.restype = c_void_p
library.getType.argtypes = [c_void_p, c_int]

library.getTypeCount.restype = c_int
library.getTypeCount.argtypes = [c_void_p]

# getters

#Data
library.mappableGetId.restype = c_int
library.mappableGetId.argtypes = [c_void_p]

library.mappableGetX.restype = c_int
library.mappableGetX.argtypes = [c_void_p]

library.mappableGetY.restype = c_int
library.mappableGetY.argtypes = [c_void_p]

library.unitGetId.restype = c_int
library.unitGetId.argtypes = [c_void_p]

library.unitGetX.restype = c_int
library.unitGetX.argtypes = [c_void_p]

library.unitGetY.restype = c_int
library.unitGetY.argtypes = [c_void_p]

library.unitGetOwner.restype = c_int
library.unitGetOwner.argtypes = [c_void_p]

library.unitGetHealth.restype = c_int
library.unitGetHealth.argtypes = [c_void_p]

library.unitGetMaxHealth.restype = c_int
library.unitGetMaxHealth.argtypes = [c_void_p]

library.unitGetSize.restype = c_int
library.unitGetSize.argtypes = [c_void_p]

library.botGetId.restype = c_int
library.botGetId.argtypes = [c_void_p]

library.botGetX.restype = c_int
library.botGetX.argtypes = [c_void_p]

library.botGetY.restype = c_int
library.botGetY.argtypes = [c_void_p]

library.botGetOwner.restype = c_int
library.botGetOwner.argtypes = [c_void_p]

library.botGetHealth.restype = c_int
library.botGetHealth.argtypes = [c_void_p]

library.botGetMaxHealth.restype = c_int
library.botGetMaxHealth.argtypes = [c_void_p]

library.botGetSize.restype = c_int
library.botGetSize.argtypes = [c_void_p]

library.botGetActions.restype = c_int
library.botGetActions.argtypes = [c_void_p]

library.botGetSteps.restype = c_int
library.botGetSteps.argtypes = [c_void_p]

library.botGetDamage.restype = c_int
library.botGetDamage.argtypes = [c_void_p]

library.botGetRange.restype = c_int
library.botGetRange.argtypes = [c_void_p]

library.botGetMovitude.restype = c_int
library.botGetMovitude.argtypes = [c_void_p]

library.botGetActitude.restype = c_int
library.botGetActitude.argtypes = [c_void_p]

library.botGetBuildRate.restype = c_int
library.botGetBuildRate.argtypes = [c_void_p]

library.botGetPartOf.restype = c_int
library.botGetPartOf.argtypes = [c_void_p]

library.botGetBuilding.restype = c_int
library.botGetBuilding.argtypes = [c_void_p]

library.botGetType.restype = c_int
library.botGetType.argtypes = [c_void_p]

library.frameGetId.restype = c_int
library.frameGetId.argtypes = [c_void_p]

library.frameGetX.restype = c_int
library.frameGetX.argtypes = [c_void_p]

library.frameGetY.restype = c_int
library.frameGetY.argtypes = [c_void_p]

library.frameGetOwner.restype = c_int
library.frameGetOwner.argtypes = [c_void_p]

library.frameGetHealth.restype = c_int
library.frameGetHealth.argtypes = [c_void_p]

library.frameGetMaxHealth.restype = c_int
library.frameGetMaxHealth.argtypes = [c_void_p]

library.frameGetSize.restype = c_int
library.frameGetSize.argtypes = [c_void_p]

library.frameGetType.restype = c_int
library.frameGetType.argtypes = [c_void_p]

library.frameGetCompletionTime.restype = c_int
library.frameGetCompletionTime.argtypes = [c_void_p]

library.wallGetId.restype = c_int
library.wallGetId.argtypes = [c_void_p]

library.wallGetX.restype = c_int
library.wallGetX.argtypes = [c_void_p]

library.wallGetY.restype = c_int
library.wallGetY.argtypes = [c_void_p]

library.wallGetOwner.restype = c_int
library.wallGetOwner.argtypes = [c_void_p]

library.wallGetHealth.restype = c_int
library.wallGetHealth.argtypes = [c_void_p]

library.wallGetMaxHealth.restype = c_int
library.wallGetMaxHealth.argtypes = [c_void_p]

library.wallGetSize.restype = c_int
library.wallGetSize.argtypes = [c_void_p]

library.typeGetId.restype = c_int
library.typeGetId.argtypes = [c_void_p]

library.typeGetName.restype = c_char_p
library.typeGetName.argtypes = [c_void_p]

library.typeGetMaxHealth.restype = c_int
library.typeGetMaxHealth.argtypes = [c_void_p]

library.typeGetDamage.restype = c_int
library.typeGetDamage.argtypes = [c_void_p]

library.typeGetRange.restype = c_int
library.typeGetRange.argtypes = [c_void_p]

library.typeGetMovitude.restype = c_int
library.typeGetMovitude.argtypes = [c_void_p]

library.typeGetActitude.restype = c_int
library.typeGetActitude.argtypes = [c_void_p]

library.typeGetBuildRate.restype = c_int
library.typeGetBuildRate.argtypes = [c_void_p]


#Properties
library.botMaxActions.restype = c_int
library.botMaxActions.argtypes = [c_void_p]

library.botMaxSteps.restype = c_int
library.botMaxSteps.argtypes = [c_void_p]


#Utils
library.distance.restype = c_int
library.distance.argtypes = [c_int, c_int, c_int, c_int, c_int, c_int]
