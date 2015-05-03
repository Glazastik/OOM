#include "AndroidInterface.h"
#include "ChatInterface.h"
#include <string>

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_Init(JNIEnv *env, jobject obj)
{
	ChatInterface::Init();
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_Stop(JNIEnv *env, jobject obj)
{
	ChatInterface::Stop();
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_ConnectService(JNIEnv *env, jobject obj, jint serviceType)
{
	ChatInterface::ConnectService(serviceType);
}

// JBYTE = CHAR = 8BITAR ENCODING
JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_ReadMessage(JNIEnv *env, jobject obj, jint messageNum, jbyteArray messageBuffer, jint bufferCapacity) //jobject messageBuffer
{
	// BYTEBUFFER ? 
	//char *_messageBuffer = (char*) env->GetDirectBufferAddress(messageBuffer);
    jbyte *_messageBuffer = env->GetByteArrayElements(messageBuffer, 0);	
	jint temp = ChatInterface::ReadMessage(messageNum, (char*)_messageBuffer, bufferCapacity);	
	env->ReleaseByteArrayElements(messageBuffer, _messageBuffer, 0);
	return temp;
}

JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_GetNumMessages(JNIEnv *env, jobject obj)
{
	return ChatInterface::GetNumMessages();
}


JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_AddPerson(JNIEnv *env, jobject obj, jint id, jstring name)
{
	const char *_name = env->GetStringUTFChars(name, NULL);
	ChatInterface::AddPerson(id, _name);
	env->ReleaseStringUTFChars(name, _name);
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_AddAccountToPerson(JNIEnv *env, jobject obj, jint personId, jint accountId, jint serviceType, jstring address)
{
	const char *_address = env->GetStringUTFChars(address, NULL);
	ChatInterface::AddAccountToPerson(personId, accountId, serviceType, _address);
	env->ReleaseStringUTFChars(address, _address);
}

JNIEXPORT void JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_SendChatMessage(JNIEnv *env, jobject obj, jint accountId, jstring message)
{
	const char *_message = env->GetStringUTFChars(message, NULL);
	ChatInterface::SendChatMessage(accountId, _message);
	env->ReleaseStringUTFChars(message, _message);
}

JNIEXPORT jint JNICALL Java_se_chalmers_oomproject_oom_ChatWrapper_GetServiceType(JNIEnv *env, jobject obj, jint accountId)
{
	return ChatInterface::GetServiceType(accountId);
}