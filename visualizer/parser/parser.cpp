#include "parser.h"
#include "sexp/sexp.h"
#include "sexp/parser.h"
#include "sexp/sfcompat.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;


static bool parseMappable(Mappable& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseUnit(Unit& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.health = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.maxHealth = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.size = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseUnit.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseBot(Bot& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.health = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.maxHealth = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.size = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.actions = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.steps = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.damage = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.range = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.movitude = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.actitude = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.buildRate = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.partOf = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.building = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.type = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseBot.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseFrame(Frame& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.health = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.maxHealth = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.size = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.completionTime = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseFrame.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseWall(Wall& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.health = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.maxHealth = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.size = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseWall.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseType(Type& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.name = new char[strlen(sub->val)+1];
  strncpy(object.name, sub->val, strlen(sub->val));
  object.name[strlen(sub->val)] = 0;
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.maxHealth = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.damage = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.range = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.movitude = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.actitude = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.buildRate = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseType.\n Parsing: " << *expression << endl;
  return false;
}

static bool parseAdd(Add& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = ADD;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.robot = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseAdd.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseAttack(Attack& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = ATTACK;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.attacker = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.victim = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseAttack.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseBuild(Build& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = BUILD;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.builder = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.frame = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseBuild.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseCollide(Collide& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = COLLIDE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.attacker = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.victim = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.direction = new char[strlen(sub->val)+1];
  strncpy(object.direction, sub->val, strlen(sub->val));
  object.direction[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseCollide.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseCombine(Combine& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = COMBINE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.bot1 = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.bot2 = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.bot3 = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.bot4 = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseCombine.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseHeal(Heal& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = HEAL;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.healer = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.victim = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseHeal.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseMove(Move& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = MOVE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.robot = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.direction = new char[strlen(sub->val)+1];
  strncpy(object.direction, sub->val, strlen(sub->val));
  object.direction[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseMove.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseRemove(Remove& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = REMOVE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.robot = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseRemove.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseSplit(Split& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = SPLIT;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.robot = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseSplit.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseTalk(Talk& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = TALK;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.speaker = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseTalk.\n Parsing: " << *expression << endl;
  return false;
}

static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  if( !expression ) return false;
  expression = expression->list;
  if( !expression ) return false;
  if(expression->val != NULL && strcmp(expression->val, "status") == 0)
  {
    GameState gs;
    while(expression->next != NULL)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(sub->val) == "game")
      {
          sub = sub->next;
          if ( !sub ) return false;
          gs.turnNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.playerID = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.boardX = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.boardY = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.gameNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.player0Time = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.player1Time = atoi(sub->val);
          sub = sub->next;
      }
      else if(string(sub->val) == "Mappable")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Mappable object;
          flag = parseMappable(object, sub);
          gs.mappables[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Unit")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Unit object;
          flag = parseUnit(object, sub);
          gs.units[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Bot")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Bot object;
          flag = parseBot(object, sub);
          gs.bots[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Frame")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Frame object;
          flag = parseFrame(object, sub);
          gs.frames[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Wall")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Wall object;
          flag = parseWall(object, sub);
          gs.walls[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Type")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Type object;
          flag = parseType(object, sub);
          gs.types[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
    }
    game.states.push_back(gs);
  }
  else if(string(expression->val) == "animations")
  {
    std::vector<Animation*> animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(sub->val) == "add")
      {
        Add* animation = new Add;
        if ( !parseAdd(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "attack")
      {
        Attack* animation = new Attack;
        if ( !parseAttack(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "build")
      {
        Build* animation = new Build;
        if ( !parseBuild(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "collide")
      {
        Collide* animation = new Collide;
        if ( !parseCollide(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "combine")
      {
        Combine* animation = new Combine;
        if ( !parseCombine(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "heal")
      {
        Heal* animation = new Heal;
        if ( !parseHeal(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "move")
      {
        Move* animation = new Move;
        if ( !parseMove(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "remove")
      {
        Remove* animation = new Remove;
        if ( !parseRemove(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "split")
      {
        Split* animation = new Split;
        if ( !parseSplit(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "talk")
      {
        Talk* animation = new Talk;
        if ( !parseTalk(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
    }
    game.states[game.states.size()-1].animations = animations;
  }
  else if(string(expression->val) == "ident")
  {
    expression = expression->next;
    if ( !expression ) return false;
    sub = expression->list;
    while(sub)
    {
      subsub = sub->list;
      if ( !subsub ) return false;
      int number = atoi(subsub->val);
      if(number >= 0)
      {
        subsub = subsub->next;
        if ( !subsub ) return false;
        subsub = subsub->next;
        if ( !subsub ) return false;
        game.players[number] = subsub->val;
      }
      sub = sub->next;
    }
  }
  else if(string(expression->val) == "game-winner")
  {
    expression = expression->next;
    if ( !expression ) return false;
    expression = expression->next;
    if ( !expression ) return false;
    expression = expression->next;
    if ( !expression ) return false;
    game.winner = atoi(expression->val);
		expression = expression->next;
		if( !expression ) return false;
		game.winReason = expression->val;
  }

  return true;
}


bool parseFile(Game& game, const char* filename)
{
  bool value;
  FILE* in = fopen(filename, "r");
  int size;
  if(!in)
    return false;

  parseFile(in);

  sexp_t* st = NULL;

  while(st = parse())
  {
    if( !parseSexp(game, st) )
    {
      while(parse()); //empty the file, keep Lex happy.
      fclose(in);
      return false;
    }
    destroy_sexp(st);
  }

  fclose(in);

  return true;
}


bool parseString(Game& game, const char* string)
{
  sexp_t* st = NULL;

  st = extract_sexpr(string);
  bool flag = true;
  while(st && flag)
  {
    flag = parseSexp(game, st);
    destroy_sexp(st);
    st = parse();
  }

  return flag;
}
