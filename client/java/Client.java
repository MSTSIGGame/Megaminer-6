import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.Native;

public interface Client extends Library {
  Client INSTANCE = (Client)Native.loadLibrary("client", Client.class);
  Pointer createConnection();
  boolean serverConnect(Pointer connection, String host, String port);

  boolean serverLogin(Pointer connection, String username, String password);
  int createGame(Pointer connection);
  int joinGame(Pointer connection, int id);

  void endTurn(Pointer connection);
  void getStatus(Pointer connection);

  int networkLoop(Pointer connection);


    //commands
  int unitTalk(Pointer object, String message);
  int botTalk(Pointer object, String message);
  int botMove(Pointer object, String direction);
  int botAttack(Pointer object, Pointer target);
  int botHeal(Pointer object, Pointer target);
  int botBuild(Pointer object, Pointer type, int x, int y, int size);
  int botCombine(Pointer object, Pointer bot2, Pointer bot3, Pointer bot4);
  int botSplit(Pointer object);
  int frameTalk(Pointer object, String message);
  int wallTalk(Pointer object, String message);

    //accessors
  int getTurnNumber(Pointer connection);
  int getPlayerID(Pointer connection);
  int getBoardX(Pointer connection);
  int getBoardY(Pointer connection);
  int getGameNumber(Pointer connection);
  int getPlayer0Time(Pointer connection);
  int getPlayer1Time(Pointer connection);

  Pointer getBot(Pointer connection, int num);
  int getBotCount(Pointer connection);
  Pointer getFrame(Pointer connection, int num);
  int getFrameCount(Pointer connection);
  Pointer getWall(Pointer connection, int num);
  int getWallCount(Pointer connection);
  Pointer getType(Pointer connection, int num);
  int getTypeCount(Pointer connection);


    //getters
  int mappableGetId(Pointer ptr);
  int mappableGetX(Pointer ptr);
  int mappableGetY(Pointer ptr);

  int unitGetId(Pointer ptr);
  int unitGetX(Pointer ptr);
  int unitGetY(Pointer ptr);
  int unitGetOwner(Pointer ptr);
  int unitGetHealth(Pointer ptr);
  int unitGetMaxHealth(Pointer ptr);
  int unitGetSize(Pointer ptr);

  int botGetId(Pointer ptr);
  int botGetX(Pointer ptr);
  int botGetY(Pointer ptr);
  int botGetOwner(Pointer ptr);
  int botGetHealth(Pointer ptr);
  int botGetMaxHealth(Pointer ptr);
  int botGetSize(Pointer ptr);
  int botGetActions(Pointer ptr);
  int botGetSteps(Pointer ptr);
  int botGetDamage(Pointer ptr);
  int botGetRange(Pointer ptr);
  int botGetMovitude(Pointer ptr);
  int botGetActitude(Pointer ptr);
  int botGetBuildRate(Pointer ptr);
  int botGetPartOf(Pointer ptr);
  int botGetBuilding(Pointer ptr);
  int botGetType(Pointer ptr);

  int frameGetId(Pointer ptr);
  int frameGetX(Pointer ptr);
  int frameGetY(Pointer ptr);
  int frameGetOwner(Pointer ptr);
  int frameGetHealth(Pointer ptr);
  int frameGetMaxHealth(Pointer ptr);
  int frameGetSize(Pointer ptr);
  Pointer frameGetType(Pointer ptr);
  int frameGetCompletionTime(Pointer ptr);

  int wallGetId(Pointer ptr);
  int wallGetX(Pointer ptr);
  int wallGetY(Pointer ptr);
  int wallGetOwner(Pointer ptr);
  int wallGetHealth(Pointer ptr);
  int wallGetMaxHealth(Pointer ptr);
  int wallGetSize(Pointer ptr);

  int typeGetId(Pointer ptr);
  String typeGetName(Pointer ptr);
  int typeGetMaxHealth(Pointer ptr);
  int typeGetDamage(Pointer ptr);
  int typeGetRange(Pointer ptr);
  int typeGetMovitude(Pointer ptr);
  int typeGetActitude(Pointer ptr);
  int typeGetBuildRate(Pointer ptr);


    //properties
  int botMaxActions(Pointer object);
  int botMaxSteps(Pointer object);

    //utils
  int distance(int fromX, int fromY, int fromSize, int toX, int toY, int toSize);

}
