package se.chalmers.oomproject.oom;

public class ChatWrapper {

    public ChatWrapper() {

    }

    private native void Init();

    public void init() {
        Init();
    }

    private native void Stop();

    public void stop() {
        Stop();
    }

    private native int ConnectService(int serviceType);

    public int connectService(int serviceType) {
        return ConnectService(serviceType);
    }

    private native int ReadMessage(int messageNum, byte[] messageBuffer, int bufferCapacity);

    public int readMessage(int messageNum, byte[] messageBuffer) {
        return ReadMessage(messageNum, messageBuffer, messageBuffer.length);
    }

    private native int GetNumMessages();

    public int getNumMessages() {
        return GetNumMessages();
    }

    private native void AddPerson(int id, String name);

    public void addPerson(int id, String name) {
        AddPerson(id, name);
    }

    private native void AddAccountToPerson(int personId, int accountId, int serviceType, String address);

    public void addAccountToPerson(int personId, int accountId, int serviceType, String address) {
        AddAccountToPerson(personId, accountId, serviceType, address);
    }

    private native void SendChatMessage(int accountId, String message);

    public void sendChatMessage(int accountId, String message) {
        SendChatMessage(accountId, message);
    }

    private native int GetServiceType(int accountId);

    public int getServiceType(int accountId) {
        return GetServiceType(accountId);
    }

    private static String NetworkCode = "NetworkCode";

    static {
        System.loadLibrary("icudata");
        System.loadLibrary(NetworkCode);
    }
}
