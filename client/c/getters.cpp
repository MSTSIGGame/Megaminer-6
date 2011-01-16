#include "getters.h"

int mappableGetId(_Mappable* ptr)
{
  return ptr->id;
}
int mappableGetX(_Mappable* ptr)
{
  return ptr->x;
}
int mappableGetY(_Mappable* ptr)
{
  return ptr->y;
}
int unitGetId(_Unit* ptr)
{
  return ptr->id;
}
int unitGetX(_Unit* ptr)
{
  return ptr->x;
}
int unitGetY(_Unit* ptr)
{
  return ptr->y;
}
int unitGetOwner(_Unit* ptr)
{
  return ptr->owner;
}
int unitGetHealth(_Unit* ptr)
{
  return ptr->health;
}
int unitGetMaxHealth(_Unit* ptr)
{
  return ptr->maxHealth;
}
int unitGetSize(_Unit* ptr)
{
  return ptr->size;
}
int botGetId(_Bot* ptr)
{
  return ptr->id;
}
int botGetX(_Bot* ptr)
{
  return ptr->x;
}
int botGetY(_Bot* ptr)
{
  return ptr->y;
}
int botGetOwner(_Bot* ptr)
{
  return ptr->owner;
}
int botGetHealth(_Bot* ptr)
{
  return ptr->health;
}
int botGetMaxHealth(_Bot* ptr)
{
  return ptr->maxHealth;
}
int botGetSize(_Bot* ptr)
{
  return ptr->size;
}
int botGetActions(_Bot* ptr)
{
  return ptr->actions;
}
int botGetSteps(_Bot* ptr)
{
  return ptr->steps;
}
int botGetDamage(_Bot* ptr)
{
  return ptr->damage;
}
int botGetRange(_Bot* ptr)
{
  return ptr->range;
}
int botGetMovitude(_Bot* ptr)
{
  return ptr->movitude;
}
int botGetActitude(_Bot* ptr)
{
  return ptr->actitude;
}
int botGetBuildRate(_Bot* ptr)
{
  return ptr->buildRate;
}
int botGetPartOf(_Bot* ptr)
{
  return ptr->partOf;
}
int botGetBuilding(_Bot* ptr)
{
  return ptr->building;
}
int botGetType(_Bot* ptr)
{
  return ptr->type;
}
int botGetMaxActions(_Bot* ptr)
{
  
}
int botGetMaxSteps(_Bot* ptr)
{
  
}
int frameGetId(_Frame* ptr)
{
  return ptr->id;
}
int frameGetX(_Frame* ptr)
{
  return ptr->x;
}
int frameGetY(_Frame* ptr)
{
  return ptr->y;
}
int frameGetOwner(_Frame* ptr)
{
  return ptr->owner;
}
int frameGetHealth(_Frame* ptr)
{
  return ptr->health;
}
int frameGetMaxHealth(_Frame* ptr)
{
  return ptr->maxHealth;
}
int frameGetSize(_Frame* ptr)
{
  return ptr->size;
}
_Type* frameGetType(_Frame* ptr)
{
  return ptr->type;
}
int frameGetCompletionTime(_Frame* ptr)
{
  return ptr->completionTime;
}
int wallGetId(_Wall* ptr)
{
  return ptr->id;
}
int wallGetX(_Wall* ptr)
{
  return ptr->x;
}
int wallGetY(_Wall* ptr)
{
  return ptr->y;
}
int wallGetOwner(_Wall* ptr)
{
  return ptr->owner;
}
int wallGetHealth(_Wall* ptr)
{
  return ptr->health;
}
int wallGetMaxHealth(_Wall* ptr)
{
  return ptr->maxHealth;
}
int wallGetSize(_Wall* ptr)
{
  return ptr->size;
}
int typeGetId(_Type* ptr)
{
  return ptr->id;
}
char* typeGetName(_Type* ptr)
{
  return ptr->name;
}
int typeGetMaxHealth(_Type* ptr)
{
  return ptr->maxHealth;
}
int typeGetDamage(_Type* ptr)
{
  return ptr->damage;
}
int typeGetRange(_Type* ptr)
{
  return ptr->range;
}
int typeGetMovitude(_Type* ptr)
{
  return ptr->movitude;
}
int typeGetActitude(_Type* ptr)
{
  return ptr->actitude;
}
int typeGetBuildRate(_Type* ptr)
{
  return ptr->buildRate;
}

