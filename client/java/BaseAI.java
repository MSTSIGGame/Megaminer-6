import com.sun.jna.Pointer;

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
  static Bot[] bots;
  static Frame[] frames;
  static Wall[] walls;
  static Type[] types;
  Pointer connection;
  static int iteration;
  boolean initialized;

  public BaseAI(Pointer c)
  {
    connection = c;
  }
    
  ///
  ///Make this your username, which should be provided.
  public abstract String username();
  ///
  ///Make this your password, which should be provided.
  public abstract String password();
  ///
  ///This is run on turn 1 before run
  public abstract void init();
  ///
  ///This is run every turn . Return true to end the turn, return false
  ///to request a status update from the server and then immediately rerun this function with the
  ///latest game status.
  public abstract boolean run();

  ///
  ///This is run on after your last turn.
  public abstract void end();


  public boolean startTurn()
  {
    iteration++;
    int count = 0;
    count = Client.INSTANCE.getBotCount(connection);
    bots = new Bot[count];
    for(int i = 0; i < count; i++)
    {
      bots[i] = new Bot(Client.INSTANCE.getBot(connection, i));
    }
    count = Client.INSTANCE.getFrameCount(connection);
    frames = new Frame[count];
    for(int i = 0; i < count; i++)
    {
      frames[i] = new Frame(Client.INSTANCE.getFrame(connection, i));
    }
    count = Client.INSTANCE.getWallCount(connection);
    walls = new Wall[count];
    for(int i = 0; i < count; i++)
    {
      walls[i] = new Wall(Client.INSTANCE.getWall(connection, i));
    }
    count = Client.INSTANCE.getTypeCount(connection);
    types = new Type[count];
    for(int i = 0; i < count; i++)
    {
      types[i] = new Type(Client.INSTANCE.getType(connection, i));
    }

    if(!initialized)
    {
      initialized = true;
      init();
    }
    return run();
  }


  ///How many turns it has been since the beginning of the game
  int turnNumber()
  {
    return Client.INSTANCE.getTurnNumber(connection);
  }
  ///Player Number; either 0 or 1
  int playerID()
  {
    return Client.INSTANCE.getPlayerID(connection);
  }
  ///Maximum valid position in the X (right) direction.  (0,0) is top left
  int boardX()
  {
    return Client.INSTANCE.getBoardX(connection);
  }
  ///Maximum valid position in the Y (down) direction.  (0,0) is top left
  int boardY()
  {
    return Client.INSTANCE.getBoardY(connection);
  }
  ///What number game this is for the server
  int gameNumber()
  {
    return Client.INSTANCE.getGameNumber(connection);
  }
  ///Player 0's time remaining
  int player0Time()
  {
    return Client.INSTANCE.getPlayer0Time(connection);
  }
  ///Player 1's time remaining
  int player1Time()
  {
    return Client.INSTANCE.getPlayer1Time(connection);
  }
}
