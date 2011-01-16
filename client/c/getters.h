#ifndef GETTERS_H 
#define GETTERS_H
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

int mappableGetId(_Mappable* ptr);
int mappableGetX(_Mappable* ptr);
int mappableGetY(_Mappable* ptr);


int unitGetId(_Unit* ptr);
int unitGetX(_Unit* ptr);
int unitGetY(_Unit* ptr);
int unitGetOwner(_Unit* ptr);
int unitGetHealth(_Unit* ptr);
int unitGetMaxHealth(_Unit* ptr);
int unitGetSize(_Unit* ptr);


int botGetId(_Bot* ptr);
int botGetX(_Bot* ptr);
int botGetY(_Bot* ptr);
int botGetOwner(_Bot* ptr);
int botGetHealth(_Bot* ptr);
int botGetMaxHealth(_Bot* ptr);
int botGetSize(_Bot* ptr);
int botGetActions(_Bot* ptr);
int botGetSteps(_Bot* ptr);
int botGetDamage(_Bot* ptr);
int botGetRange(_Bot* ptr);
int botGetMovitude(_Bot* ptr);
int botGetActitude(_Bot* ptr);
int botGetBuildRate(_Bot* ptr);
int botGetPartOf(_Bot* ptr);
int botGetBuilding(_Bot* ptr);
int botGetType(_Bot* ptr);

int botGetMaxActions(_Bot* ptr);
int botGetMaxSteps(_Bot* ptr);

int frameGetId(_Frame* ptr);
int frameGetX(_Frame* ptr);
int frameGetY(_Frame* ptr);
int frameGetOwner(_Frame* ptr);
int frameGetHealth(_Frame* ptr);
int frameGetMaxHealth(_Frame* ptr);
int frameGetSize(_Frame* ptr);
_Type* frameGetType(_Frame* ptr);
int frameGetCompletionTime(_Frame* ptr);


int wallGetId(_Wall* ptr);
int wallGetX(_Wall* ptr);
int wallGetY(_Wall* ptr);
int wallGetOwner(_Wall* ptr);
int wallGetHealth(_Wall* ptr);
int wallGetMaxHealth(_Wall* ptr);
int wallGetSize(_Wall* ptr);


int typeGetId(_Type* ptr);
char* typeGetName(_Type* ptr);
int typeGetMaxHealth(_Type* ptr);
int typeGetDamage(_Type* ptr);
int typeGetRange(_Type* ptr);
int typeGetMovitude(_Type* ptr);
int typeGetActitude(_Type* ptr);
int typeGetBuildRate(_Type* ptr);



#ifdef __cplusplus
}
#endif

#endif
