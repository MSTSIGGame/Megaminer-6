import com.sun.jna.Pointer;

///An object that exists on the grid
abstract class Unit
{
  Pointer ptr;
  int ID;
  int iteration;
  public Unit(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.unitGetId(ptr);
    iteration = BaseAI.iteration;
  }

  abstract boolean validify();
    
    //commands
    
  ///Sends a message to be visualized when this unit is selected
  int talk(String message)
  {
    validify();
    return Client.INSTANCE.unitTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.unitGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.unitGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.unitGetY(ptr);
  }
  ///The owning player
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.unitGetOwner(ptr);
  }
  ///How much health this unit currently has
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.unitGetHealth(ptr);
  }
  ///The maximum amount of health this unit can ever have
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.unitGetMaxHealth(ptr);
  }
  ///The length of one side of this Unit
  public int getSize()
  {
    validify();
    return Client.INSTANCE.unitGetSize(ptr);
  }

}
