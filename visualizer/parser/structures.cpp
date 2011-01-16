// -*-c++-*-

#include "structures.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, Mappable ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Unit ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "maxHealth: " << ob.maxHealth  <<'\n';
  stream << "size: " << ob.size  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Bot ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "maxHealth: " << ob.maxHealth  <<'\n';
  stream << "size: " << ob.size  <<'\n';
  stream << "actions: " << ob.actions  <<'\n';
  stream << "steps: " << ob.steps  <<'\n';
  stream << "damage: " << ob.damage  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "movitude: " << ob.movitude  <<'\n';
  stream << "actitude: " << ob.actitude  <<'\n';
  stream << "buildRate: " << ob.buildRate  <<'\n';
  stream << "partOf: " << ob.partOf  <<'\n';
  stream << "building: " << ob.building  <<'\n';
  stream << "type: " << ob.type  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Frame ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "maxHealth: " << ob.maxHealth  <<'\n';
  stream << "size: " << ob.size  <<'\n';
  stream << "type: " << ob.type  <<'\n';
  stream << "completionTime: " << ob.completionTime  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Wall ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "maxHealth: " << ob.maxHealth  <<'\n';
  stream << "size: " << ob.size  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Type ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "name: " << ob.name  <<'\n';
  stream << "maxHealth: " << ob.maxHealth  <<'\n';
  stream << "damage: " << ob.damage  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "movitude: " << ob.movitude  <<'\n';
  stream << "actitude: " << ob.actitude  <<'\n';
  stream << "buildRate: " << ob.buildRate  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, Add ob)
{
  stream << "Add" << "\n";
  stream << "robot: " << ob.robot  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Attack ob)
{
  stream << "Attack" << "\n";
  stream << "attacker: " << ob.attacker  <<'\n';
  stream << "victim: " << ob.victim  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Build ob)
{
  stream << "Build" << "\n";
  stream << "builder: " << ob.builder  <<'\n';
  stream << "frame: " << ob.frame  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Collide ob)
{
  stream << "Collide" << "\n";
  stream << "attacker: " << ob.attacker  <<'\n';
  stream << "victim: " << ob.victim  <<'\n';
  stream << "direction: " << ob.direction  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Combine ob)
{
  stream << "Combine" << "\n";
  stream << "bot1: " << ob.bot1  <<'\n';
  stream << "bot2: " << ob.bot2  <<'\n';
  stream << "bot3: " << ob.bot3  <<'\n';
  stream << "bot4: " << ob.bot4  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Heal ob)
{
  stream << "Heal" << "\n";
  stream << "healer: " << ob.healer  <<'\n';
  stream << "victim: " << ob.victim  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Move ob)
{
  stream << "Move" << "\n";
  stream << "robot: " << ob.robot  <<'\n';
  stream << "direction: " << ob.direction  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Remove ob)
{
  stream << "Remove" << "\n";
  stream << "robot: " << ob.robot  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Split ob)
{
  stream << "Split" << "\n";
  stream << "robot: " << ob.robot  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Talk ob)
{
  stream << "Talk" << "\n";
  stream << "speaker: " << ob.speaker  <<'\n';
  stream << "message: " << ob.message  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "boardX: " << ob.boardX  <<'\n';
  stream << "boardY: " << ob.boardY  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';
  stream << "player0Time: " << ob.player0Time  <<'\n';
  stream << "player1Time: " << ob.player1Time  <<'\n';

  stream << "\n\nMappables:\n";
  for(std::map<int,Mappable>::iterator i = ob.mappables.begin(); i != ob.mappables.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nUnits:\n";
  for(std::map<int,Unit>::iterator i = ob.units.begin(); i != ob.units.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nBots:\n";
  for(std::map<int,Bot>::iterator i = ob.bots.begin(); i != ob.bots.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nFrames:\n";
  for(std::map<int,Frame>::iterator i = ob.frames.begin(); i != ob.frames.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nWalls:\n";
  for(std::map<int,Wall>::iterator i = ob.walls.begin(); i != ob.walls.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nTypes:\n";
  for(std::map<int,Type>::iterator i = ob.types.begin(); i != ob.types.end(); i++)
    stream << i->second << '\n';
  stream << "\nAnimation\n";
  for(std::vector<Animation*>::iterator i = ob.animations.begin(); i != ob.animations.end(); i++)
  {
    if((**i).type == ADD)
      stream << *((Add*)*i) << "\n";
    if((**i).type == ATTACK)
      stream << *((Attack*)*i) << "\n";
    if((**i).type == BUILD)
      stream << *((Build*)*i) << "\n";
    if((**i).type == COLLIDE)
      stream << *((Collide*)*i) << "\n";
    if((**i).type == COMBINE)
      stream << *((Combine*)*i) << "\n";
    if((**i).type == HEAL)
      stream << *((Heal*)*i) << "\n";
    if((**i).type == MOVE)
      stream << *((Move*)*i) << "\n";
    if((**i).type == REMOVE)
      stream << *((Remove*)*i) << "\n";
    if((**i).type == SPLIT)
      stream << *((Split*)*i) << "\n";
    if((**i).type == TALK)
      stream << *((Talk*)*i) << "\n";
  }
}

Game::Game()
{
  winner = -1;
}
