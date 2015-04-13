#include "ManagedCode.h"
#include "Messenger.h"
#include <vector>
#include <map>

//#define NULL 0

using namespace std;

Messenger* g_theMessenger;

//
// CONSTRUCT AND DESTRUCT
//
JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_initiliaze
    (JNIEnv *env, jobject obj)
{
	g_theMessenger = new Messenger();
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_deleteMessenger
    (JNIEnv *env, jobject obj)
{
	delete g_theMessenger;
}

//
// Login
//
JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_login
    (JNIEnv *env, jobject obj, jobject loginData)
{

}

//
// Getting Messages
//
JNIEXPORT jboolean JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_hasMessage
    (JNIEnv *env, jobject obj, jint msgr)
{
	return g_theMessenger->HasMessage(msgr);
}

JNIEXPORT jobject JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_getMessage
    (JNIEnv *env, jobject obj, jint msgr)
{
	message msg = g_theMessenger->_GetMessage(msgr);
	
	jclass messageClass = env->FindClass("com/example/alexander/myapplication/Message");
    jmethodID midConstructor = env->GetMethodID(messageClass, "<init>", "()V");
    jobject messageObject = env->NewObject(messageClass, midConstructor);
	
	jmethodID midSetData = env->GetMethodID(messageClass, "setData", "([C)V");
	jmethodID midSetCid = env->GetMethodID(messageClass, "setCid", "([C)V");
		
	int data_size = msg.data_length;
	jcharArray data;
	data = env->NewCharArray(data_size);
	if (data == NULL) {
			 return NULL;  //out of memory error thrown 
	}	
	int cid_size = msg.cid_length;
	jcharArray cid;
	cid = env->NewCharArray(cid_size);
	if (cid == NULL) {
			 return NULL;  //out of memory error thrown 
	}
	// fill a temp structure to use to populate the java array
	jchar data_fill[data_size];
	for (int i = 0; i < data_size; i++) {
		data_fill[i] = msg.data[i]; 
	}
	jchar cid_fill[cid_size];
	for (int i = 0; i < cid_size; i++) {
		cid_fill[i] = msg.cid[i]; 
	}
	env->SetCharArrayRegion(data, 0, data_size, data_fill);
	env->SetCharArrayRegion(cid, 0, cid_size, cid_fill);
	
	env->CallVoidMethod(messageObject, midSetData, data);
	env->CallVoidMethod(messageObject, midSetCid, cid);
	
    return messageObject;
}

//
// Sending Messages
//
JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_sendMessage
	(JNIEnv *env, jobject obj, jint msgr, jobject messageObject) 
{
		jclass messageClass = env->GetObjectClass(messageObject);
		
		jmethodID midGetData = env->GetMethodID(messageClass, "getData", "()[C");
		jmethodID midGetCid = env->GetMethodID(messageClass, "getCid", "()[C");

		jobject data_object = env->CallObjectMethod(messageObject, midGetData);
		jobject cid_object = env->CallObjectMethod(messageObject, midGetCid);
		jcharArray data_array = (jcharArray) data_object;
		jcharArray cid_array = (jcharArray) cid_object;
		
		jsize data_length = env->GetArrayLength(data_array);
		jchar *data = env->GetCharArrayElements(data_array, 0);
		
		jsize cid_length = env->GetArrayLength(cid_array);
		jchar *cid = env->GetCharArrayElements(cid_array, 0);
		
		message msg;
		msg.data_length = data_length;
		msg.data = new wchar_t[data_length];
		for (int i = 0; i < data_length; i++)
		{	
			msg.data[i] = data[i];
		}
		msg.cid_length = cid_length;
		msg.cid = new wchar_t[cid_length];
		for (int i = 0; i < cid_length; i++)
		{	
			msg.cid[i] = cid[i];
		}
	
		env->ReleaseCharArrayElements(data_array, data, 0);
		env->ReleaseCharArrayElements(cid_array, cid, 0);
}

//
//	Contact functions
//
JNIEXPORT jobjectArray JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_getContacts
  (JNIEnv *env, jobject obj, jint msgr) {
	  
	jclass contactClass = env->FindClass("com/example/alexander/myapplication/Contact");
    jmethodID midConstructor = env->GetMethodID(contactClass, "<init>", "()V");
    jobject contactObject = env->NewObject(contactClass, midConstructor);
	
	jmethodID midSetId = env->GetMethodID(contactClass, "setId", "([C)V");
	jmethodID midSetName = env->GetMethodID(contactClass, "setName", "([C)V");
	
	vector<contact> contacts = g_theMessenger->GetContacts(msgr);
	
	jint size = contacts.size();
	jobjectArray array = env->NewObjectArray(size, contactClass, NULL);
	
	for(int i = 0; i < size; i++) 
	{
		contact temp = contacts[i];
		
		int id_size = temp.id_length;
		jcharArray id;
		id = env->NewCharArray(id_size);
		if (id == NULL) {
				 return NULL;  //out of memory error thrown 
		}
		
		int name_size = temp.name_length;
		jcharArray name;
		name = env->NewCharArray(name_size);
		if (name == NULL) {
				 return NULL;  //out of memory error thrown 
		}
		// fill a temp structure to use to populate the java array
		jchar id_fill[id_size];
		for (int j = 0; j < id_size; j++) {
			id_fill[j] = temp.id[j]; // put whatever logic you want to populate the values here.
		}
		
		// fill a temp structure to use to populate the java array
		jchar name_fill[name_size];
		for (int j = 0; j < name_size; j++) {
			name_fill[j] = temp.name[j]; // put whatever logic you want to populate the values here.
		}
		
		env->SetCharArrayRegion(id, 0, id_size, id_fill);
		env->SetCharArrayRegion(name, 0, name_size, name_fill);
		
		env->CallVoidMethod(contactObject, midSetId, id);
		env->CallVoidMethod(contactObject, midSetName, name);
		
		env->SetObjectArrayElement(array, i, contactObject);
		
	}

    return array;
}

//
// OTHER FUNCTIONS
//	
JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_intMethod
  (JNIEnv *env, jobject obj, jint num) {
   return num * num;
}

JNIEXPORT jboolean JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_booleanMethod
   (JNIEnv *env, jobject obj, jboolean boolean) {
    return !boolean;
}

JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_intArrayMethod
   (JNIEnv *env, jobject obj, jintArray array) {
     int i, sum = 0;
     
	jsize len = env->GetArrayLength(array);
    jint *body = env->GetIntArrayElements(array, 0);
	 
     for (i=0; i<len; i++)
     {	
		sum += body[i];
     }
	 
     env->ReleaseIntArrayElements(array, body, 0);
	 
     return sum;
}

JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_charArrayMethod
   (JNIEnv *env, jobject obj, jcharArray array) {
    int i, sum = 0;
     
	jsize len = env->GetArrayLength(array);
    jchar *body = env->GetCharArrayElements(array, 0);
	 
    for (i=0; i<len; i++)
    {	
		sum += body[i];
    }
	 
    env->ReleaseCharArrayElements(array, body, 0);
	 
    return sum;
}


// Detta sättet är likt C#

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_VoidIntArrayMethod
   (JNIEnv *env, jobject obj, jintArray array) {
	 
	jsize len = env->GetArrayLength(array);
    jint *body = env->GetIntArrayElements(array, 0);
	
	for (int i = 0; i<len; i++)
    {	
		body[i] = 7;
    }
	env->ReleaseIntArrayElements(array, body, 0);
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_VoidCharArrayMethod
   (JNIEnv *env, jobject obj, jcharArray array) {
    int i = 0;
	 
	jsize len = env->GetArrayLength(array);
    jchar *body = env->GetCharArrayElements(array, 0);
	
	for (i=0; i<len; i++)
    {	
		body[i] = 't';
    }
	env->ReleaseCharArrayElements(array, body, 0);
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_VoidByteArrayMethod
   (JNIEnv *env, jobject obj, jbyteArray array) {
    int i = 0;
	 
	jsize len = env->GetArrayLength(array);
    jbyte *body = env->GetByteArrayElements(array, 0);
	
	for (i=0; i<len; i++)
    {	
		body[i] = 2;
    }
	env->ReleaseByteArrayElements(array, body, 0);
}



// GETTERS


JNIEXPORT jintArray JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_GetIntArrayMethod
   (JNIEnv *env, jobject obj, jint size) {
		jintArray result;
		result = env->NewIntArray(size);
		if (result == NULL) {
			 return NULL;  //out of memory error thrown 
		}
		int i;
		// fill a temp structure to use to populate the java int array
		jint fill[256];
		for (i = 0; i < size; i++) {
			fill[i] = 5; // put whatever logic you want to populate the values here.
		}
		env->SetIntArrayRegion(result, 0, size, fill);
		return result;
}

JNIEXPORT jcharArray JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_GetCharArrayMethod
   (JNIEnv *env, jobject obj, jint size) {
		jcharArray result;
		result = env->NewCharArray(size);
		if (result == NULL) {
			 return NULL;  //out of memory error thrown 
		}
		int i;
		// fill a temp structure to use to populate the java int array
		jchar fill[256];
		for (i = 0; i < size; i++) {
			fill[i] = 'k'; // put whatever logic you want to populate the values here.
		}
		env->SetCharArrayRegion(result, 0, size, fill);
		return result;
}

JNIEXPORT jbyteArray JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_GetByteArrayMethod
   (JNIEnv *env, jobject obj, jint size) {
		jbyteArray result;
		result = env->NewByteArray(size);
		if (result == NULL) {
			 return NULL;  //out of memory error thrown 
		}
		int i;
		// fill a temp structure to use to populate the java int array
		jbyte fill[256];
		for (i = 0; i < size; i++) {
			fill[i] = 3; // put whatever logic you want to populate the values here.
		}
		env->SetByteArrayRegion(result, 0, size, fill);
		return result;
}


 // SETTERS

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_SetByteArrayMethod
   (JNIEnv *env, jobject obj, jbyteArray array) {
	 
	jsize len = env->GetArrayLength(array);
    jbyte *body = env->GetByteArrayElements(array, 0);
	
	jbyte message[len];
	for (int i = 0; i < len; i++)
    {	
		message[i] = body[i];
    }
	env->ReleaseByteArrayElements(array, body, 0);
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_SetCharArrayMethod
   (JNIEnv *env, jobject obj, jcharArray array) {
	 
	jsize len = env->GetArrayLength(array);
    jchar *body = env->GetCharArrayElements(array, 0);
	
	jchar message[len];
	for (int i = 0; i < len; i++)
    {	
		message[i] = body[i];
    }
	env->ReleaseCharArrayElements(array, body, 0);
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_SetIntArrayMethod
   (JNIEnv *env, jobject obj, jintArray array) {
	 
	jsize len = env->GetArrayLength(array);
    jint *body = env->GetIntArrayElements(array, 0);
	
	jint message[len];
	for (int i = 0; i < len; i++)
    {	
		message[i] = body[i];
    }
	env->ReleaseIntArrayElements(array, body, 0);
}

// GET OBJECT

JNIEXPORT jobject JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_getContact
  (JNIEnv *env, jobject obj) {
    jclass contactClass = env->FindClass("com/example/alexander/myapplication/Contact");
    jmethodID midConstructor = env->GetMethodID(contactClass, "<init>", "()V");
    jobject contactObject = env->NewObject(contactClass, midConstructor);
	
	jmethodID midSetName = env->GetMethodID(contactClass, "setName", "([C)V");
	jmethodID midSetId = env->GetMethodID(contactClass, "setId", "(I)V");
		
	int size = 5;
	jcharArray result;
	result = env->NewCharArray(size);
	if (result == NULL) {
			 return NULL;  //out of memory error thrown 
	}
	int i;
	// fill a temp structure to use to populate the java array
	jchar fill[size];
	for (int i = 0; i < size; i++) {
		fill[i] = 'h'; 
	}
	env->SetCharArrayRegion(result, 0, size, fill);
	
	env->CallVoidMethod(contactObject, midSetId, 7);
	env->CallVoidMethod(contactObject, midSetName, result);
	
    return contactObject;
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_setContact
	(JNIEnv *env, jobject obj, jobject contactObject) {
		jclass contactClass = env->GetObjectClass(contactObject);
		jmethodID midGetId = env->GetMethodID(contactClass, "getId", "()I");
		jmethodID midGetName = env->GetMethodID(contactClass, "getName", "()[C");
		int id =  env->CallIntMethod(contactObject, midGetId);
		jobject temp = env->CallObjectMethod(contactObject, midGetName);
		jcharArray array = (jcharArray) temp;
		
		jsize len = env->GetArrayLength(array);
		jchar *body = env->GetCharArrayElements(array, 0);
		
		jchar message[len];
		for (int i = 0; i < len; i++)
		{	
			message[i] = body[i];
		}
		
		env->ReleaseCharArrayElements(array, body, 0);
}

/*JNIEXPORT jobjectArray JNICALL Java_se_chalmers_oomproject_oom_ManagedCode_getContacts
  (JNIEnv *env, jobject obj) {
	  
	jclass contactClass = env->FindClass("com/example/alexander/myapplication/Contact");
    jmethodID midConstructor = env->GetMethodID(contactClass, "<init>", "()V");
    jobject contactObject = env->NewObject(contactClass, midConstructor);
	
	jmethodID midSetId = env->GetMethodID(contactClass, "setId", "(I)V");
	jmethodID midSetName = env->GetMethodID(contactClass, "setName", "([C)V");
	
	jobjectArray array = env->NewObjectArray(2, contactClass, NULL);
	
	int size = 5;
	jcharArray result;
	result = env->NewCharArray(size);
	if (result == NULL) {
			 return NULL;  //out of memory error thrown 
	}
	int i;
	// fill a temp structure to use to populate the java array
	jchar fill[size];
	for (int i = 0; i < size; i++) {
		fill[i] = 'e'; // put whatever logic you want to populate the values here.
	}
	env->SetCharArrayRegion(result, 0, size, fill);
	
	env->CallVoidMethod(contactObject, midSetId, 5);
	env->CallVoidMethod(contactObject, midSetName, result);
	
	env->SetObjectArrayElement(array, 0, contactObject);
	
    return array;
}*/
