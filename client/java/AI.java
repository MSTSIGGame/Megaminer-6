import com.sun.jna.Pointer;
import java.util.Random;


///The class implementing gameplay logic.
class AI extends BaseAI
{
  private Random r;

  public String username()
  {
    return "Shell AI";
  }
  public String password()
  {
    return "password";
  }

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public boolean run()
  {
    String[] s = {"l", "r", "u", "d"};
    for(int i = 0; i < bots.length; i++)
    {
      if(bots[i].getOwner() == playerID())
      {
        bots[i].move(s[r.nextInt(4)]);
        if(bots[i].getBuildRate() != 0)
        {
          bots[i].build(types[r.nextInt(types.length)], bots[i].getX()+1, bots[i].getY(), 1);
        }
      }
    }
    return true;
  }


  //This function is called once, before your first turn
  public void init()
  {
    r = new Random();
  }

  //This function is called once, after your last turn
  public void end() {}
  
  
  public AI(Pointer c)
  {
    super(c);
  }
}
