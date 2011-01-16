import com.sun.jna.Pointer;

///A baby robot.
class Frame
{
  Pointer ptr;
  int ID;
  int iteration;
  public Frame(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.frameGetId(ptr);
    iteration = BaseAI.iteration;
  }

  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.frames.length; i++)
    {
      if(BaseAI.frames[i].ID == ID)
      {
        ptr = BaseAI.frames[i].ptr;
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
    return Client.INSTANCE.frameTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.frameGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.frameGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.frameGetY(ptr);
  }
  ///The owning player
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.frameGetOwner(ptr);
  }
  ///How much health this unit currently has
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.frameGetHealth(ptr);
  }
  ///The maximum amount of health this unit can ever have
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.frameGetMaxHealth(ptr);
  }
  ///What type this robot will be
  public Pointer getType()
  {
    validify();
    return Client.INSTANCE.frameGetType(ptr);
  }
  ///The length of one side of this robot, such that size^2 = number of bots combined into this bot
  public int getSize()
  {
    validify();
    return Client.INSTANCE.frameGetSize(ptr);
  }
  ///How many of your turns until this frame becomes a robot
  public int getCompletionTime()
  {
    validify();
    return Client.INSTANCE.frameGetCompletionTime(ptr);
  }

}
