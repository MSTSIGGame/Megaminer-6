import com.sun.jna.Pointer;

///A kind of robot.
class Type
{
  Pointer ptr;
  int ID;
  int iteration;
  public Type(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.typeGetId(ptr);
    iteration = BaseAI.iteration;
  }

  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.types.length; i++)
    {
      if(BaseAI.types[i].ID == ID)
      {
        ptr = BaseAI.types[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.typeGetId(ptr);
  }
  ///The name of this type of robot
  public String getName()
  {
    validify();
    return Client.INSTANCE.typeGetName(ptr);
  }
  ///The maximum amount of health for this type of robot
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.typeGetMaxHealth(ptr);
  }
  ///The amount of damage this type of robot does when attacking
  public int getDamage()
  {
    validify();
    return Client.INSTANCE.typeGetDamage(ptr);
  }
  ///How far this type of robot can attack or heal from its edge
  public int getRange()
  {
    validify();
    return Client.INSTANCE.typeGetRange(ptr);
  }
  ///This value divided by the number of bots = maxSteps for this type of robot
  public int getMovitude()
  {
    validify();
    return Client.INSTANCE.typeGetMovitude(ptr);
  }
  ///This value divided by the number of bots = maxActions for this type of robot
  public int getActitude()
  {
    validify();
    return Client.INSTANCE.typeGetActitude(ptr);
  }
  ///This value is used to determine how many turns it takes to build a robot and how much this type of robot heals for
  public int getBuildRate()
  {
    validify();
    return Client.INSTANCE.typeGetBuildRate(ptr);
  }

}
