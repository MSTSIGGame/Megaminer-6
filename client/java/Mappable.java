import com.sun.jna.Pointer;

///An object that exists on the grid
abstract class Mappable
{
  Pointer ptr;
  int ID;
  int iteration;
  public Mappable(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.mappableGetId(ptr);
    iteration = BaseAI.iteration;
  }

  abstract boolean validify();
    
    //commands
    
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.mappableGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.mappableGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.mappableGetY(ptr);
  }

}
