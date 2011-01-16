import com.sun.jna.Pointer;

///A pile of hard stuff that is in the way.
class Wall
{
  Pointer ptr;
  int ID;
  int iteration;
  public Wall(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.wallGetId(ptr);
    iteration = BaseAI.iteration;
  }

  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.walls.length; i++)
    {
      if(BaseAI.walls[i].ID == ID)
      {
        ptr = BaseAI.walls[i].ptr;
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
    return Client.INSTANCE.wallTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.wallGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.wallGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.wallGetY(ptr);
  }
  ///The owning player
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.wallGetOwner(ptr);
  }
  ///How much health this unit currently has
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.wallGetHealth(ptr);
  }
  ///The maximum amount of health this unit can ever have
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.wallGetMaxHealth(ptr);
  }
  ///The length of one side of this Unit
  public int getSize()
  {
    validify();
    return Client.INSTANCE.wallGetSize(ptr);
  }

}
