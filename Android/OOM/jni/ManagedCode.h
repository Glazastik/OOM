/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ManagedCode */

#ifndef _Included_ManagedCode
#define _Included_ManagedCode
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ManagedCode
 * Method:    intMethod
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_example_alexander_myapplication_ManagedCode_intMethod
  (JNIEnv *, jobject, jint);

/*
 * Class:     ManagedCode
 * Method:    booleanMethod
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_example_alexander_myapplication_ManagedCode_booleanMethod
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     ManagedCode
 * Method:    intArrayMethod
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_com_example_alexander_myapplication_ManagedCode_intArrayMethod
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     ManagedCode
 * Method:    charArrayMethod
 * Signature: ([C)I
 */
JNIEXPORT jint JNICALL Java_com_example_alexander_myapplication_ManagedCode_charArrayMethod
  (JNIEnv *, jobject, jcharArray);

/*
 * Class:     ManagedCode
 * Method:    VoidIntArrayMethod
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_VoidIntArrayMethod
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     ManagedCode
 * Method:    VoidCharArrayMethod
 * Signature: ([C)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_VoidCharArrayMethod
  (JNIEnv *, jobject, jcharArray);

/*
 * Class:     ManagedCode
 * Method:    VoidByteArrayMethod
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_VoidByteArrayMethod
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     ManagedCode
 * Method:    GetIntArrayMethod
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_example_alexander_myapplication_ManagedCode_GetIntArrayMethod
  (JNIEnv *, jobject, jint);

/*
 * Class:     ManagedCode
 * Method:    GetCharArrayMethod
 * Signature: (I)[C
 */
JNIEXPORT jcharArray JNICALL Java_com_example_alexander_myapplication_ManagedCode_GetCharArrayMethod
  (JNIEnv *, jobject, jint);

/*
 * Class:     ManagedCode
 * Method:    GetByteArrayMethod
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_example_alexander_myapplication_ManagedCode_GetByteArrayMethod
  (JNIEnv *, jobject, jint);

/*
 * Class:     ManagedCode
 * Method:    SetIntArrayMethod
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_SetIntArrayMethod
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     ManagedCode
 * Method:    SetCharArrayMethod
 * Signature: ([C)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_SetCharArrayMethod
  (JNIEnv *, jobject, jcharArray);

/*
 * Class:     ManagedCode
 * Method:    SetByteArrayMethod
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_SetByteArrayMethod
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     ManagedCode
 * Method:    getContact
 * Signature: ()LContact;
 */
JNIEXPORT jobject JNICALL Java_com_example_alexander_myapplication_ManagedCode_getContact
  (JNIEnv *, jobject);

/*
 * Class:     ManagedCode
 * Method:    setContact
 * Signature: (LContact;)V
 */
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_setContact
  (JNIEnv *, jobject, jobject);

/*
 * Class:     ManagedCode
 * Method:    getContacts
 * Signature: ()[LContact;
 */
/*JNIEXPORT jobjectArray JNICALL Java_com_example_alexander_myapplication_ManagedCode_getContacts
  (JNIEnv *, jobject);*/
  
// ................

JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_initiliaze
    (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_deleteMessenger
    (JNIEnv *, jobject);
	
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_login
    (JNIEnv *, jobject, jobject);
	
JNIEXPORT jboolean JNICALL Java_com_example_alexander_myapplication_ManagedCode_hasMessage
    (JNIEnv *, jobject, jint);

JNIEXPORT jobject JNICALL Java_com_example_alexander_myapplication_ManagedCode_getMessage
    (JNIEnv *, jobject, jint);
	
JNIEXPORT void JNICALL Java_com_example_alexander_myapplication_ManagedCode_sendMessage
	(JNIEnv *, jobject, jint, jobject); 
 
JNIEXPORT jobjectArray JNICALL Java_com_example_alexander_myapplication_ManagedCode_getContacts
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
