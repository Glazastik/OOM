package com.example.alexander.myapplication;
/**
 * Created by Alexander on 2015-04-10.
 */
public class ManagedCode {

	/* Importing DLL functions*/
	public native int intMethod(int n);
	public native boolean booleanMethod(boolean bool);
	public native int intArrayMethod(int[] intArray);
	public native int charArrayMethod(char[] charArray);
	
	// C# alike
	public native void VoidIntArrayMethod(int[] intArray); // 32-bitar	
	public native void VoidCharArrayMethod(char[] charArray); // 16-bitar
	public native void VoidByteArrayMethod(byte[] byteArray); // 8-bitar

	// GETTERS
	public native int[] GetIntArrayMethod(int size);
	public native char[] GetCharArrayMethod(int size);
	public native byte[] GetByteArrayMethod(int size);
	
	// SETTERS
	public native void SetIntArrayMethod(int[] intArray);
	public native void SetCharArrayMethod(char[] charArray);
	public native void SetByteArrayMethod(byte[] byteArray);	
	
	// object methods
	public native Contact getContact();
	public native void setContact(Contact contact);
	public native Contact[] getContacts();
	
	// C# functions
	public native void initiliaze();
	public native void deleteMessenger();
	public native boolean hasMessage(int msgr);
	public native Message getMessage(int msgr);
	public native void sendMessage(int msgr, Message msg);	
	public native Contact[] getContacts(int msgr);
	
	public ManagedCode() {
		
	}
	
	public int test(int n) {
		return intMethod(n);
	}
	
	static {
		System.loadLibrary("ManagedCode");
	}
}

