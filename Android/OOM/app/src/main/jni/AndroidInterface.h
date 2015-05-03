#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_Init(JNIEnv *, jobject);
	JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_Stop(JNIEnv *, jobject);
	JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_ConnectService(JNIEnv *, jobject, jint);
	JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_ReadMessage(JNIEnv *, jobject, jint, jbyteArray, jint);
	JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_GetNumMessages(JNIEnv *, jobject);
	JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_AddPerson(JNIEnv *, jobject, jint, jstring);
	JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_AddAccountToPerson(JNIEnv *, jobject, jint, jint, jint, jstring);
	JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_SendChatMessage(JNIEnv *, jobject, jint, jstring);
	JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_GetServiceType(JNIEnv *, jobject, jint accountId);
	
}