#ifndef PCSLOGS_H
#define PCSLOGS_H

#include "pcs_pc_lib_global.h"
#include <string.h>
#include <stdio.h>
#include <QString.h>


//����־�ļ�
class PCS_PC_LIB_EXPORT pcsLogs
{
public:
	virtual~pcsLogs(){};

	static pcsLogs* TheInstance(); //���ڷ��ؾ�̬ʵ��
	static void RegisterInstance(pcsLogs* LogInstance); //��¼��ʵ��
	static bool Print(const char *format, ...); //�����ʽ����Ϣ
	static bool Print(const QString& messge); //�ַ������
	static bool PrintDebug(const char *format, ...); //����ģʽ���
	static bool PrintDebug(const QString& message);
	static bool Warning(const char *format, ...); //�����ʽ������ģʽ
	static bool Warning(const QString& message);
	static bool WarningDebug(const char *format, ...); //����ģʽ������Ϣ
	static bool WarningDebug(const QString& message);
	static bool Error(const char *format, ...);  //�����ʽ������ģʽ
	static bool Error(const QString& message);
	static bool ErrorDebug(const char *format, ...);
	static bool ErrorDebug(const QString& message);

protected:
	//��Ϣ��ʾ����
	enum MessageLevel
	{
		LOG_Standard = 0, /**< Standard message (Print) **/
		LOG_Standard_Debug = 1, /**< Standard message - debug only (PrintDebug) **/
		LOG_Warning = 2, /**< Warning message (Warning) **/
		LOG_Warning_Debug = 3, /**< Warning message - debug only (WarningDebug) **/
		LOG_Error = 4, /**< Error message (Error) **/
		LOG_Error_Debug = 5, /**< Error message - debug only (ErrorDebug) **/
	};
	//ͨ����Ϣ��ʾ���� 
	void virtual DisplayMessage(const QString& message, MessageLevel level) = 0;
};

#endif // PCSLOGS_H
