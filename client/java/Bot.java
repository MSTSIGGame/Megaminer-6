import com.sun.jna.Pointer;

///The bot class.
class Bot
{
  Pointer ptr;
  int ID;
  int iteration;
  public Bot(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.botGetId(ptr);
    iteration = BaseAI.iteration;
  }

  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.bots.length; i++)
    {
      if(BaseAI.bots[i].ID == ID)
      {
        ptr = BaseAI.bots[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
  ///Sends a message to be visualized when this unit is selected
  int talk(String message)
  {
    validify();
    return Client.INSTANCE.botTalk(ptr, message);
  }
  ///Move in the indicated direction (U, D, L, or R).  U is y=y-1, L=x=x-1, such that the top left corner is (0,0). Requires the calling robot to have a step.
  int move(String direction)
  {
    validify();
    return Client.INSTANCE.botMove(ptr, direction);
  }
  ///Attack the specified unit.  Requires the calling robot to have an action and for the target to be in range
  int attack(Unit target)
  {
    validify();
    target.validify();
    return Client.INSTANCE.botAttack(ptr, target.ptr);
  }
  ///Heals the indicated bot.  Requires the calling robot to have an action and for the target to be in range.  Heals for target.maxHealth * self.buildRate / (4 * target.size^2)
  int heal(Bot target)
  {
    validify();
    target.validify();
    return Client.INSTANCE.botHeal(ptr, target.ptr);
  }
  ///Begins building a new robot.  While building, the new robot will be a frame.  Requires the calling robot to have an action. X and Y must cause the new robot to be adjacent.  Size must be less than or equal to the calling robots size.  Completes in 8 * size^2 / self.buildRate turns
  int build(Type type, int x, int y, int size)
  {
    validify();
    type.validify();
    return Client.INSTANCE.botBuild(ptr, type.ptr, x, y, size);
  }
  ///Combines four robots into one.  Requires all robots to have an action, be of the same size, and be arranged in a square
  int combine(Bot bot2, Bot bot3, Bot bot4)
  {
    validify();
    bot2.validify();
    bot3.validify();
    bot4.validify();
    return Client.INSTANCE.botCombine(ptr, bot2.ptr, bot3.ptr, bot4.ptr);
  }
  ///Splits a compound bot into the 4 robots that combined to make it.  Requires the calling robot to have an action.
  int split()
  {
    validify();
    return Client.INSTANCE.botSplit(ptr);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.botGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.botGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.botGetY(ptr);
  }
  ///The owning player
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.botGetOwner(ptr);
  }
  ///How much health this unit currently has
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.botGetHealth(ptr);
  }
  ///The maximum amount of health this unit can ever have
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.botGetMaxHealth(ptr);
  }
  ///How many actions this bot can still perform
  public int getActions()
  {
    validify();
    return Client.INSTANCE.botGetActions(ptr);
  }
  ///How many steps this bot can still take
  public int getSteps()
  {
    validify();
    return Client.INSTANCE.botGetSteps(ptr);
  }
  ///The length of one side of this robot, such that size^2 = number of bots combined into this bot
  public int getSize()
  {
    validify();
    return Client.INSTANCE.botGetSize(ptr);
  }
  ///The amount of damage this robot does when attacking
  public int getDamage()
  {
    validify();
    return Client.INSTANCE.botGetDamage(ptr);
  }
  ///How far this robot can attack or heal from its edge
  public int getRange()
  {
    validify();
    return Client.INSTANCE.botGetRange(ptr);
  }
  ///This value divided by the number of bots = maxSteps for this robot
  public int getMovitude()
  {
    validify();
    return Client.INSTANCE.botGetMovitude(ptr);
  }
  ///This value divided by the number of bots = maxActions for this robot
  public int getActitude()
  {
    validify();
    return Client.INSTANCE.botGetActitude(ptr);
  }
  ///This value is used to determine how many turns it takes to build a robot and how much this robot heals for
  public int getBuildRate()
  {
    validify();
    return Client.INSTANCE.botGetBuildRate(ptr);
  }
  ///ID of the robot this robot is apart of, 0 if not in a robot
  public int getPartOf()
  {
    validify();
    return Client.INSTANCE.botGetPartOf(ptr);
  }
  ///ID of the robot this robot is building, 0 if not building
  public int getBuilding()
  {
    validify();
    return Client.INSTANCE.botGetBuilding(ptr);
  }
  ///ID of the type this robot is, 0 if a combination
  public int getType()
  {
    validify();
    return Client.INSTANCE.botGetType(ptr);
  }

   ///Returns the maximum number of actions this robot can take per turn.
  int getMaxActions()
  {
    validify();
    return Client.INSTANCE.botMaxActions(ptr);
  }

   ///Returns the maximum number of steps this robot can take per turn.
  int getMaxSteps()
  {
    validify();
    return Client.INSTANCE.botMaxSteps(ptr);
  }

}
